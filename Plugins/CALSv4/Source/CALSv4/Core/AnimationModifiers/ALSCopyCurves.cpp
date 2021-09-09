#include "ALSCopyCurves.h"
#include "UObject/NameTypes.h"
#include "Animation/AnimSequence.h"

UALSCopyCurves::UALSCopyCurves() {
	FName curves[] = {
			TEXT("BasePose_CLF") ,TEXT("BasePose_N") ,TEXT("Enable_AimOffset") ,TEXT("Enable_FootIK_L") ,TEXT("Enable_FootIK_R") ,TEXT("Enable_HandIK_L") ,
			TEXT("Enable_HandIK_R") ,TEXT("Enable_SpineRotation") ,TEXT("Enable_Transition") ,TEXT("Feet_Crossing") ,TEXT("FootLock_L") ,TEXT("FootLock_R") ,
			TEXT("HipOrientation_Bias") ,TEXT("Layering_Arm_L") ,TEXT("Layering_Arm_L_Add") ,TEXT("Layering_Arm_L_LS") ,TEXT("Layering_Arm_R") ,TEXT("Layering_Arm_R_Add") ,
			TEXT("Layering_Arm_R_LS") ,TEXT("Layering_Hand_L") ,TEXT("Layering_Hand_R") ,TEXT("Layering_Head") ,TEXT("Layering_Head_Add") ,TEXT("Layering_Legs") ,
			TEXT("Layering_Pelvis") ,TEXT("Layering_Spine") ,TEXT("Layering_Spine_Add") ,TEXT("Mask_AimOffset") ,TEXT("Mask_FootstepSound") ,TEXT("Mask_LandPrediction") ,
			TEXT("Mask_Lean") ,TEXT("RotationAmount") ,TEXT("Feet_Position") ,TEXT("Weight_Falling") ,TEXT("Weight_Gait"),TEXT("YawOffset") };
	AllCurves.Append(curves, ARRAY_COUNT(curves));
}

void UALSCopyCurves::OnApply_Implementation(UAnimSequence* AnimationSequence) {
	AnimSequence = AnimationSequence;

	TArray<float> times;
	TArray<float> values;
	TArray<FName> selectedCurves = CopyAllCurves ? AllCurves : CurvesToCopy;

	for (FName curve : selectedCurves) {
		bool bCurveExists = UAnimationBlueprintLibrary::DoesCurveExist(AnimToCopyFrom, curve, ERawCurveTrackTypes::RCT_Float);
		if (bCurveExists) {
			UAnimationBlueprintLibrary::RemoveCurve(AnimSequence, curve, false);
		}

		UAnimationBlueprintLibrary::AddCurve(AnimSequence, curve, ERawCurveTrackTypes::RCT_Float, false);
		UAnimationBlueprintLibrary::GetFloatKeys(AnimToCopyFrom, curve, times, values);
		UAnimationBlueprintLibrary::AddFloatCurveKeys(AnimSequence, curve, times, values);
	}
}