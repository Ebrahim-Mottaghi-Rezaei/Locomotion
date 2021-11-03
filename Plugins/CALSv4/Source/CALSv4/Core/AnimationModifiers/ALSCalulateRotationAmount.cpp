#include "ALSCalulateRotationAmount.h"
#include "AnimationModifiers/Public/AnimationBlueprintLibrary.h"
#include "Animation/AnimCurveTypes.h"
#include "Animation/AnimSequence.h"

UALSCalulateRotationAmount::UALSCalulateRotationAmount() {
	CurveName = FName(TEXT("RotationAmount"));
	RootBoneName = FName(TEXT("root"));
}

/// <summary>
/// This Anim Modifier calculates the change in root rotation and is used to create the "RotationAmount" curves for the turn in place animations.
/// Each curve value represents the change in rotation from the current and next frame, so it can be applied to the actors rotation to mimic root motion.
/// </summary>
/// <param name="AnimationSequence"></param>
void UALSCalulateRotationAmount::OnApply_Implementation(UAnimSequence* AnimationSequence) {
	AnimSequence = AnimationSequence;
	const bool curveExists = UAnimationBlueprintLibrary::DoesCurveExist(this->AnimSequence, CurveName, ERawCurveTrackTypes::RCT_Float);

	if (curveExists) {
		UAnimationBlueprintLibrary::RemoveCurve(AnimSequence, CurveName, false);
	}

	UAnimationBlueprintLibrary::AddCurve(AnimSequence, CurveName, ERawCurveTrackTypes::RCT_Float, false);

	int totalFrames = 0;
	UAnimationBlueprintLibrary::GetNumFrames(AnimSequence, totalFrames);

	for (int currentFrame = 0; currentFrame < totalFrames; currentFrame++) {

		int nextFrame = 0;
		float timeAtFrame = 0;
		float curveValue = 0;
		float rateScale = 0;
		FTransform thisFramePoseTransform;
		FTransform nextFramePoseTransform;

		UAnimationBlueprintLibrary::GetTimeAtFrame(AnimSequence, currentFrame, timeAtFrame);

		nextFrame = currentFrame + this->AnimSequence->RateScale < 0 ? -1 : 1;

		UAnimationBlueprintLibrary::GetBonePoseForFrame(AnimSequence, RootBoneName, nextFrame, false, nextFramePoseTransform);
		UAnimationBlueprintLibrary::GetBonePoseForFrame(AnimSequence, RootBoneName, currentFrame, false, thisFramePoseTransform);

		UAnimationBlueprintLibrary::GetRateScale(this->AnimSequence, rateScale);
		rateScale = FMath::Abs(rateScale);

		curveValue = (nextFramePoseTransform.Rotator().Yaw - thisFramePoseTransform.Rotator().Yaw) * rateScale;

		UAnimationBlueprintLibrary::AddFloatCurveKey(AnimSequence, CurveName, timeAtFrame, curveValue);
	}

	UAnimationBlueprintLibrary::FinalizeBoneAnimation(AnimSequence);
}