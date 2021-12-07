#include "ALSCreateLayeringCurves.h"

UALSCreateLayeringCurves::UALSCreateLayeringCurves() {
	FName curves[] = {
		TEXT("Enable_SpineRotation"),TEXT("Enable_HandIK_L"),TEXT("Enable_HandIK_R"),TEXT("HipOrientation_Bias") ,
		TEXT("Layering_Arm_L") ,TEXT("Layering_Arm_L_Add") ,TEXT("Layering_Arm_L_LS") ,TEXT("Layering_Arm_R") ,
		TEXT("Layering_Arm_R_Add") ,TEXT("Layering_Arm_R_LS") ,TEXT("Layering_Hand_L") ,TEXT("Layering_Hand_R") ,
		TEXT("Layering_Head") ,TEXT("Layering_Head_Add") ,TEXT("Layering_Legs") ,TEXT("Layering_Pelvis") ,TEXT("Layering_Spine") ,TEXT("Layering_Spine_Add") };
	CurvesToCreate.Append(curves, UE_ARRAY_COUNT(curves));
	DefaultValue = 1.0f;
	KeyEachFrame = true;
}

void UALSCreateLayeringCurves::OnApply_Implementation(UAnimSequence* AnimationSequence) {
	for (const auto curve : CurvesToCreate) {
		const bool bCurveExists = UAnimationBlueprintLibrary::DoesCurveExist(AnimationSequence, curve, ERawCurveTrackTypes::RCT_Float);
		if (bCurveExists) {
			UAnimationBlueprintLibrary::RemoveCurve(AnimationSequence, curve, false);
		}

		UAnimationBlueprintLibrary::AddCurve(AnimationSequence, curve, ERawCurveTrackTypes::RCT_Float);

		if (KeyEachFrame) {
			int totalFrames = 0;
			UAnimationBlueprintLibrary::GetNumFrames(AnimationSequence, totalFrames);

			for (int frame = 0; frame < totalFrames - 2; frame++) {
				float frameTime = 0;
				UAnimationBlueprintLibrary::GetTimeAtFrame(AnimationSequence, frame, frameTime);
				UAnimationBlueprintLibrary::AddFloatCurveKey(AnimationSequence, curve, frameTime, DefaultValue);
			}
		} else {
			float frameTime = 0.0f;
			UAnimationBlueprintLibrary::GetTimeAtFrame(AnimationSequence, 0, frameTime);
			UAnimationBlueprintLibrary::AddFloatCurveKey(AnimationSequence, curve, frameTime, DefaultValue);
		}
	}
}
