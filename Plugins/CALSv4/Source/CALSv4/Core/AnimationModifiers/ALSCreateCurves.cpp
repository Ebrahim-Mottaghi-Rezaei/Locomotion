#include "ALSCreateCurves.h"

void UALSCreateCurves::OnApply_Implementation(UAnimSequence* AnimationSequence) {
	for (auto curve : CurvesToCreate) {
		bool bCurveExists = UAnimationBlueprintLibrary::DoesCurveExist(AnimationSequence, curve.CurveName, ERawCurveTrackTypes::RCT_Float);
		if (bCurveExists) {
			UAnimationBlueprintLibrary::RemoveCurve(AnimationSequence, curve.CurveName, false);
		}

		UAnimationBlueprintLibrary::AddCurve(AnimationSequence, curve.CurveName, ERawCurveTrackTypes::RCT_Float);

		if (curve.KeyEachFrame) {
			int totalFrames = 0;
			UAnimationBlueprintLibrary::GetNumFrames(AnimationSequence, totalFrames);

			for (int frame = 0; frame < totalFrames - 2; frame++) {
				float frameTime = 0;
				UAnimationBlueprintLibrary::GetTimeAtFrame(AnimationSequence, frame, frameTime);
				UAnimationBlueprintLibrary::AddFloatCurveKey(AnimationSequence, curve.CurveName, frameTime, 0);
			}
		} else {

			for (auto key : CurveParams.Keys) {
				float frameTime = 0;
				UAnimationBlueprintLibrary::GetTimeAtFrame(AnimationSequence, key.FrameNumber, frameTime);
				UAnimationBlueprintLibrary::AddFloatCurveKey(AnimationSequence, CurveParams.CurveName, frameTime, key.CurveValue);
			}

		}
	}
}