#include "LmCharacterAnimInstance.h"
#include <Curves/CurveVector.h>
#include "../LmStructs.h"
#include "../LmHelpers.h"
#include "../LmLogger.h"
#include "../Gameplay/LmControllerInterface.h"
#include "../Gameplay/LmPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include <Animation/AnimSequence.h>
#include <UObject/ConstructorHelpers.h>
#include <TimerManager.h>

ULmCharacterAnimInstance::ULmCharacterAnimInstance() {
	RootMotionMode = ERootMotionMode::RootMotionFromMontagesOnly;

#pragma region Setting up the Turn In place assets
	N_TurnIP_L90 = FLmTurnInPlaceAsset();
	N_TurnIP_L90.AnimatedAngle = -90.0f;
	N_TurnIP_L90.SlotName = TEXT("(N) Turn/Rotate");
	N_TurnIP_L90.PlayRate = 1.2f;
	N_TurnIP_L90.ScaleTurnAngle = true;

	const ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_N_TurnIP_L90(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/TurnInPlace/ALS_N_TurnIP_L90.ALS_N_TurnIP_L90'"));
	if (IsValid(ALS_N_TurnIP_L90.Object) && ALS_N_TurnIP_L90.Succeeded())
		N_TurnIP_L90.Animation = ALS_N_TurnIP_L90.Object;
	else
		ULmLogger::LogError(TEXT("Animation not found: ALS_N_TurnIP_L90"));

	N_TurnIP_R90 = FLmTurnInPlaceAsset();
	N_TurnIP_R90.AnimatedAngle = 90.0f;
	N_TurnIP_R90.SlotName = TEXT("(N) Turn/Rotate");
	N_TurnIP_R90.PlayRate = 1.2f;
	N_TurnIP_R90.ScaleTurnAngle = true;
	const ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_N_TurnIP_R90(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/TurnInPlace/ALS_N_TurnIP_R90.ALS_N_TurnIP_R90'"));
	if (IsValid(ALS_N_TurnIP_R90.Object) && ALS_N_TurnIP_R90.Succeeded())
		N_TurnIP_R90.Animation = ALS_N_TurnIP_R90.Object;
	else
		ULmLogger::LogError(TEXT("Animation not found: ALS_N_TurnIP_R90"));

	N_TurnIP_L180 = FLmTurnInPlaceAsset();
	N_TurnIP_L180.AnimatedAngle = -180.0f;
	N_TurnIP_L180.SlotName = TEXT("(N) Turn/Rotate");
	N_TurnIP_L180.PlayRate = 1.2f;
	N_TurnIP_L180.ScaleTurnAngle = true;
	const ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_N_TurnIP_L180(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/TurnInPlace/ALS_N_TurnIP_L180.ALS_N_TurnIP_L180'"));
	if (IsValid(ALS_N_TurnIP_L180.Object) && ALS_N_TurnIP_L180.Succeeded())
		N_TurnIP_L180.Animation = ALS_N_TurnIP_L180.Object;
	else
		ULmLogger::LogError(TEXT("Animation not found: ALS_N_TurnIP_L180"));

	N_TurnIP_R180 = FLmTurnInPlaceAsset();
	N_TurnIP_R180.AnimatedAngle = 180.0f;
	N_TurnIP_R180.SlotName = TEXT("(N) Turn/Rotate");
	N_TurnIP_R180.PlayRate = 1.2f;
	N_TurnIP_R180.ScaleTurnAngle = true;
	const ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_N_TurnIP_R180(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/TurnInPlace/ALS_N_TurnIP_R180.ALS_N_TurnIP_R180'"));
	if (IsValid(ALS_N_TurnIP_R180.Object) && ALS_N_TurnIP_R180.Succeeded())
		N_TurnIP_R180.Animation = ALS_N_TurnIP_R180.Object;
	else
		ULmLogger::LogError(TEXT("Animation not found: ALS_N_TurnIP_R180"));

	CLF_TurnIP_L90 = FLmTurnInPlaceAsset();
	CLF_TurnIP_L90.AnimatedAngle = -90.0f;
	CLF_TurnIP_L90.SlotName = TEXT("(CLF) Turn/Rotate");
	CLF_TurnIP_L90.PlayRate = 1.2f;
	CLF_TurnIP_L90.ScaleTurnAngle = false;
	const ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_CLF_TurnIP_L90(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/TurnInPlace/ALS_CLF_TurnIP_L90.ALS_CLF_TurnIP_L90'"));
	if (IsValid(ALS_CLF_TurnIP_L90.Object) && ALS_CLF_TurnIP_L90.Succeeded())
		CLF_TurnIP_L90.Animation = ALS_CLF_TurnIP_L90.Object;
	else
		ULmLogger::LogError(TEXT("Animation not found: ALS_CLF_TurnIP_L90"));

	CLF_TurnIP_R90 = FLmTurnInPlaceAsset();
	CLF_TurnIP_R90.AnimatedAngle = 90.0f;
	CLF_TurnIP_R90.SlotName = TEXT("(CLF) Turn/Rotate");
	CLF_TurnIP_R90.PlayRate = 1.2f;
	CLF_TurnIP_R90.ScaleTurnAngle = false;
	const ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_CLF_TurnIP_R90(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/TurnInPlace/ALS_CLF_TurnIP_R90.ALS_CLF_TurnIP_R90'"));
	if (IsValid(ALS_CLF_TurnIP_R90.Object) && ALS_CLF_TurnIP_R90.Succeeded())
		CLF_TurnIP_R90.Animation = ALS_CLF_TurnIP_R90.Object;
	else
		ULmLogger::LogError(TEXT("Animation not found: ALS_CLF_TurnIP_R90"));

	CLF_TurnIP_L180 = FLmTurnInPlaceAsset();
	CLF_TurnIP_L180.AnimatedAngle = -180.0f;
	CLF_TurnIP_L180.SlotName = TEXT("(CLF) Turn/Rotate");
	CLF_TurnIP_L180.PlayRate = 1.2f;
	CLF_TurnIP_L180.ScaleTurnAngle = false;
	const ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_CLF_TurnIP_L180(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/TurnInPlace/ALS_CLF_TurnIP_L180.ALS_CLF_TurnIP_L180'"));
	if (IsValid(ALS_CLF_TurnIP_L180.Object) && ALS_CLF_TurnIP_L180.Succeeded())
		CLF_TurnIP_L180.Animation = ALS_CLF_TurnIP_L180.Object;
	else
		ULmLogger::LogError(TEXT("Animation not found: ALS_CLF_TurnIP_L180"));

	CLF_TurnIP_R180 = FLmTurnInPlaceAsset();
	CLF_TurnIP_R180.AnimatedAngle = 180.0f;
	CLF_TurnIP_R180.SlotName = TEXT("(CLF) Turn/Rotate");
	CLF_TurnIP_R180.PlayRate = 1.2f;
	CLF_TurnIP_R180.ScaleTurnAngle = false;
	const ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_CLF_TurnIP_R180(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/TurnInPlace/ALS_CLF_TurnIP_R180.ALS_CLF_TurnIP_R180'"));
	if (IsValid(ALS_CLF_TurnIP_R180.Object) && ALS_CLF_TurnIP_R180.Succeeded())
		CLF_TurnIP_R180.Animation = ALS_CLF_TurnIP_R180.Object;
	else
		ULmLogger::LogError(TEXT("Animation not found: ALS_CLF_TurnIP_R180"));
#pragma endregion

#pragma region Setting Up Blend Curves
	const ConstructorHelpers::FObjectFinder<UCurveFloat> _DiagonalScaleAmountCurve(TEXT("CurveFloat'/Game/AdvancedLocomotionV4/Data/Curves/AnimationBlendCurves/DiagonalScaleAmount.DiagonalScaleAmount'"));
	if (IsValid(_DiagonalScaleAmountCurve.Object) && _DiagonalScaleAmountCurve.Succeeded())
		DiagonalScaleAmountCurve = _DiagonalScaleAmountCurve.Object;
	else
		ULmLogger::LogError(TEXT("Curve not found: DiagonalScaleAmount"));

	const ConstructorHelpers::FObjectFinder<UCurveFloat> _StrideBlend_N_Walk(TEXT("CurveFloat'/Game/AdvancedLocomotionV4/Data/Curves/AnimationBlendCurves/StrideBlend_N_Walk.StrideBlend_N_Walk'"));
	if (IsValid(_StrideBlend_N_Walk.Object) && _StrideBlend_N_Walk.Succeeded())
		StrideBlend_N_Walk = _StrideBlend_N_Walk.Object;
	else
		ULmLogger::LogError(TEXT("Curve not found: StrideBlend_N_Walk"));

	const ConstructorHelpers::FObjectFinder<UCurveFloat> _StrideBlend_N_Run(TEXT("CurveFloat'/Game/AdvancedLocomotionV4/Data/Curves/AnimationBlendCurves/StrideBlend_N_Run.StrideBlend_N_Run'"));
	if (IsValid(_StrideBlend_N_Run.Object) && _StrideBlend_N_Run.Succeeded())
		StrideBlend_N_Run = _StrideBlend_N_Run.Object;
	else
		ULmLogger::LogError(TEXT("Curve not found: StrideBlend_N_Run"));

	const ConstructorHelpers::FObjectFinder<UCurveFloat> _StrideBlend_C_Walk(TEXT("CurveFloat'/Game/AdvancedLocomotionV4/Data/Curves/AnimationBlendCurves/StrideBlend_N_Walk.StrideBlend_N_Walk'"));
	if (IsValid(_StrideBlend_C_Walk.Object) && _StrideBlend_C_Walk.Succeeded())
		StrideBlend_C_Walk = _StrideBlend_C_Walk.Object;
	else
		ULmLogger::LogError(TEXT("Curve not found: StrideBlend_C_Walk"));

	const ConstructorHelpers::FObjectFinder<UCurveFloat> _LandPredictionCurve(TEXT("CurveFloat'/Game/AdvancedLocomotionV4/Data/Curves/AnimationBlendCurves/LandPredictionBlend.LandPredictionBlend'"));
	if (IsValid(_LandPredictionCurve.Object) && _LandPredictionCurve.Succeeded())
		LandPredictionCurve = _LandPredictionCurve.Object;
	else
		ULmLogger::LogError(TEXT("Curve not found: LandPredictionCurve"));

	const ConstructorHelpers::FObjectFinder<UCurveFloat> _LeanInAirAmount(TEXT("CurveFloat'/Game/AdvancedLocomotionV4/Data/Curves/AnimationBlendCurves/LeanInAirAmount.LeanInAirAmount'"));
	if (IsValid(_LeanInAirAmount.Object) && _LeanInAirAmount.Succeeded())
		LeanInAirCurve = _LeanInAirAmount.Object;
	else
		ULmLogger::LogError(TEXT("Curve not found: LeanInAirCurve"));

	const ConstructorHelpers::FObjectFinder<UCurveVector> _YawOffset_FB(TEXT("CurveVector'/Game/AdvancedLocomotionV4/Data/Curves/AnimationBlendCurves/YawOffset_FB.YawOffset_FB'"));
	if (IsValid(_YawOffset_FB.Object) && _YawOffset_FB.Succeeded())
		YawOffset_FB = _YawOffset_FB.Object;
	else
		ULmLogger::LogError(TEXT("Curve not found: YawOffset_FB"));

	const ConstructorHelpers::FObjectFinder<UCurveVector> _YawOffset_LR(TEXT("CurveVector'/Game/AdvancedLocomotionV4/Data/Curves/AnimationBlendCurves/YawOffset_LR.YawOffset_LR'"));
	if (IsValid(_YawOffset_LR.Object) && _YawOffset_LR.Succeeded())
		YawOffset_LR = _YawOffset_LR.Object;
	else
		ULmLogger::LogError(TEXT("Curve not found: YawOffset_LR"));
#pragma endregion

#pragma region Setting Up Transitions
	static ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_N_Transition_R_Finder(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/Transitions/ALS_N_Transition_R.ALS_N_Transition_R'"));
	if (IsValid(ALS_N_Transition_R_Finder.Object) && ALS_N_Transition_R_Finder.Succeeded()) {
		ALS_N_Transition_R = ALS_N_Transition_R_Finder.Object;
	} else {
		ULmLogger::LogError(TEXT("Animation not found: ALS_N_Transition_R"));
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_N_Transition_L_Finder(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/Transitions/ALS_N_Transition_L.ALS_N_Transition_L'"));
	if (IsValid(ALS_N_Transition_L_Finder.Object) && ALS_N_Transition_L_Finder.Succeeded()) {
		ALS_N_Transition_L = ALS_N_Transition_L_Finder.Object;
	} else {
		ULmLogger::LogError(TEXT("Animation not found: ALS_N_Transition_R"));
	}
#pragma endregion

}

void ULmCharacterAnimInstance::NativeBeginPlay() {
	Super::NativeBeginPlay();

	//Initialize Anim Instance
	if (TryGetPawnOwner()) {
		Character = static_cast<ALmBaseCharacter*>(TryGetPawnOwner());
		bDynamicTransitionGate_IsOpen = true;
		if (GetWorld()->GetTimerManager().IsTimerPending(DynamicTransitionHandle)) {
			GetWorld()->GetTimerManager().ClearTimer(DynamicTransitionHandle);
		}
	}
}

void ULmCharacterAnimInstance::NativeUpdateAnimation(const float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	//Only update if character is valid
	if (DeltaSeconds == 0.f || !IsValid(Character))
		return;

	delta_time = DeltaSeconds;

	//Do Every Frame
	UpdateCharacterInfo();
	UpdateAimingValues();
	UpdateLayerValues();
	UpdateFootIK();

	/*Check Movement Mode*/
	switch (MovementState) {
		case ELmMovementState::Lm_Grounded:
			//Check If Moving Or Not
			bShouldMove = ShouldMoveCheck();

			switch (ULmHelpers::GetStateTracking(bShouldMove, bShouldMove_Last)) {
				case ELmStateTracking::Lm_WhileTrue:	/*Do While Moving*/
					UpdateMovementValues();
					UpdateRotationValues();
					break;
				case ELmStateTracking::Lm_WhileFalse:	/*Do While Not Moving*/
					if (CanRotateInPlace()) {
						RotateInPlaceCheck();
					} else {
						bRotateL = false;
						bRotateR = false;
					}

					if (CanTurnInPlace()) {
						TurnInPlaceCheck();
					} else {
						ElapsedDelayTime = 0.0f;
					}

					if (CanDynamicTransition()) {
						DynamicTransitionCheck();
					}
					break;
				case ELmStateTracking::Lm_ChangedToTrue:	/*Do When Starting To Move*/

					ElapsedDelayTime = 0.0f;
					bRotateL = false;
					bRotateR = false;
					break;
				case ELmStateTracking::Lm_ChangedToFalse:
				default:
					break;
			}

			bShouldMove_Last = bShouldMove;
			break;
		case ELmMovementState::Lm_InAir:
			//Do While InAir
			UpdateInAirValues();
			break;
		case ELmMovementState::Lm_Ragdoll:
			//Do While Rag-dolling
			UpdateRagdollValues();
			break;
		case ELmMovementState::Lm_None:
		case ELmMovementState::Lm_Mantling:
		default:
			break;
	}
}

float ULmCharacterAnimInstance::GetAnimCurveClamped(const FName Name, const float Bias, const float ClampMin, const float ClampMax) {
	return FMath::Clamp(GetCurveValue(Name) + Bias, ClampMin, ClampMax);
}

void ULmCharacterAnimInstance::ResetIKOffsets() {
	FootOffsets_L.LocationOffset = UKismetMathLibrary::VInterpTo(FootOffsets_L.LocationOffset, FVector::ZeroVector, delta_time, 15.0f);
	FootOffsets_R.LocationOffset = UKismetMathLibrary::VInterpTo(FootOffsets_R.LocationOffset, FVector::ZeroVector, delta_time, 15.0f);

	FootOffsets_L.RotationOffset = UKismetMathLibrary::RInterpTo(FootOffsets_L.RotationOffset, FRotator::ZeroRotator, delta_time, 15.0f);
	FootOffsets_R.RotationOffset = UKismetMathLibrary::RInterpTo(FootOffsets_R.RotationOffset, FRotator::ZeroRotator, delta_time, 15.0f);
}

void ULmCharacterAnimInstance::UpdateCharacterInfo() {
	if (Character && Character->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass())) {
		const auto values = ILmCharacterInterface::Execute_GetEssentialValues(Character);
		Velocity = values.Velocity;
		Acceleration = values.Acceleration;
		MovementInput = values.MovementInput;
		bIsMoving = values.bIsMoving;
		bHasMovementInput = values.bHasMovementInput;
		Speed = values.Speed;
		MovementInputAmount = values.MovementInputAmount;
		AimingRotation = values.AimingRotation;
		AimYawRate = values.AimYawRate;

		const auto states = ILmCharacterInterface::Execute_GetCurrentState(Character);
		MovementState = states.MovementState;
		PrevMovementState = states.PrevMovementState;
		MovementAction = states.MovementAction;
		RotationMode = states.RotationMode;
		Gait = states.ActualGait;
		Stance = states.ActualStance;
		ViewMode = states.ViewMode;
		OverlayState = states.OverlayState;
	}
}

void ULmCharacterAnimInstance::UpdateAimingValues() {
	//Interp the Aiming Rotation value to achieve smooth aiming rotation changes. Interpolating the rotation before calculating the angle ensures the value is not affected by changes in actor rotation, allowing slow aiming rotation changes with fast actor rotation changes.
	SmoothAimingRotation = UKismetMathLibrary::RInterpTo(SmoothAimingRotation, AimingRotation, delta_time, SmoothedAimingRotationInterpSpeed);

	//Calculate the Aiming angle and Smoothed Aiming Angle by getting the delta between the aiming rotation and the actor rotation.
	const FRotator actorRotation = Character->GetActorRotation();
	const FRotator delta1 = UKismetMathLibrary::NormalizedDeltaRotator(AimingRotation, actorRotation);
	AimingAngle = FVector2D(delta1.Yaw, delta1.Pitch);
	const FRotator delta2 = UKismetMathLibrary::NormalizedDeltaRotator(SmoothAimingRotation, actorRotation);
	SmoothedAimingAngle = FVector2D(delta2.Yaw, delta2.Pitch);

	//Clamp the Aiming Pitch Angle to a range of 1 to 0 for use in the vertical aim sweeps.
	if (RotationMode != ELmRotationMode::Lm_VelocityDirection) {
		AimSweepTime = UKismetMathLibrary::MapRangeClamped(AimingAngle.Y, -90.0f, 90.0f, 1.0f, 0.0f);
		//Use the Aiming Yaw Angle divided by the number of spine+pelvis bones to get the amount of spine rotation needed to remain facing the camera direction.
		SpineRotation = FRotator(0.0f, AimingAngle.X / 4.0f, 0.0);
	} else {
		//Get the delta between the Movement Input rotation and Actor rotation and map it to a range of 0-1. This value is used in the aim offset behavior to make the character look toward the Movement Input.
		if (bHasMovementInput) {
			const FRotator delta3 = UKismetMathLibrary::NormalizedDeltaRotator(MovementInput.ToOrientationRotator(), actorRotation);
			const float target = UKismetMathLibrary::MapRangeClamped(delta3.Yaw, -180.0f, 180.0f, 0.0f, 1.0f);
			InputYawOffsetTime = UKismetMathLibrary::FInterpTo(InputYawOffsetTime, target, delta_time, InputYawOffsetInterpSpeed);
		}
	}

	//Separate the Aiming Yaw Angle into 3 separate Yaw Times. These 3 values are used in the Aim Offset behavior to improve the blending of the aim offset when rotating completely around the character. This allows you to keep the aiming responsive but still smoothly blend from left to right or right to left.
	LeftYawTime = UKismetMathLibrary::MapRangeClamped(FMath::Abs(SmoothedAimingAngle.X), 0.0f, 180.0f, 0.5f, 0.0f);
	RightYawTime = UKismetMathLibrary::MapRangeClamped(FMath::Abs(SmoothedAimingAngle.X), 0.0f, 180.0f, 0.5f, 1.0f);
	ForwardYawTime = UKismetMathLibrary::MapRangeClamped(SmoothedAimingAngle.X, -180.0f, 180.0f, 0.0f, 1.0f);
}

void ULmCharacterAnimInstance::UpdateLayerValues() {
	//Get the Aim Offset weight by getting the opposite of the Aim Offset Mask.
	EnableAimOffset = UKismetMathLibrary::Lerp(1.0f, 0.0f, GetCurveValue(FName(TEXT("Mask_AimOffset"))));

	//Set the Base Pose weights
	BasePose_N = GetCurveValue(FName(TEXT("BasePose_N")));
	BasePose_CLF = GetCurveValue(FName(TEXT("BasePose_CLF")));

	//Set the Additive amount weights for each body part
	Spine_Add = GetCurveValue(FName(TEXT("Layering_Spine_Add")));
	Head_Add = GetCurveValue(FName(TEXT("Layering_Head_Add")));
	Arm_L_Add = GetCurveValue(FName(TEXT("Layering_Arm_L_Add")));
	Arm_R_Add = GetCurveValue(FName(TEXT("Layering_Arm_R_Add")));

	//Set the Hand Override weights
	Hand_R = GetCurveValue(FName(TEXT("Layering_Hand_R")));
	Hand_L = GetCurveValue(FName(TEXT("Layering_Hand_L")));

	//Blend and set the Hand IK weights to ensure they only are weighted if allowed by the Arm layers.
	EnableHandIK_L = UKismetMathLibrary::Lerp(0.0f, GetCurveValue(FName(TEXT("Enable_HandIK_L"))), GetCurveValue(FName(TEXT("Layering_Arm_L"))));
	EnableHandIK_R = UKismetMathLibrary::Lerp(0.0f, GetCurveValue(FName(TEXT("Enable_HandIK_R"))), GetCurveValue(FName(TEXT("Layering_Arm_R"))));

	//Set whether the arms should blend in mesh space or local space. The Mesh space weight will always be 1 unless the Local Space (LS) curve is fully weighted.
	Arm_L_LS = GetCurveValue(FName(TEXT("Layering_Arm_L_LS")));
	Arm_L_MS = static_cast<float>(1 - UKismetMathLibrary::FFloor(Arm_L_LS));
	Arm_R_LS = GetCurveValue(FName(TEXT("Layering_Arm_R_LS")));
	Arm_R_MS = static_cast<float>(1 - UKismetMathLibrary::FFloor(Arm_R_LS));
}

void ULmCharacterAnimInstance::UpdateFootIK() {
	//Update Foot Locking values.

	//Step 1	Updating FootLockings for L/R feet and cache the results
	FootLock_L = UpdateFootLock(FName(TEXT("Enable_FootIK_L")), FName(TEXT("FootLock_L")), FName(TEXT("ik_foot_l")), FootLock_L);
	FootLock_R = UpdateFootLock(FName(TEXT("Enable_FootIK_R")), FName(TEXT("FootLock_R")), FName(TEXT("ik_foot_r")), FootLock_R);

	switch (MovementState) {
		case ELmMovementState::Lm_None:
		case ELmMovementState::Lm_Grounded:
		case ELmMovementState::Lm_Mantling:
			//Step 2	Setting FootOffsets for L/R feet and cache the results
			FootOffsets_L = SetFootOffsets(FName(TEXT("Enable_FootIK_L")), FName(TEXT("ik_foot_l")), FName(TEXT("root")), FootOffsets_L);
			FootOffsets_R = SetFootOffsets(FName(TEXT("Enable_FootIK_R")), FName(TEXT("ik_foot_r")), FName(TEXT("root")), FootOffsets_R);

			//Step 3	Setting PelvisIKOffsets using previously cached results
			UpdatePelvisIKOffset(FootOffsets_L.LocationTarget, FootOffsets_R.LocationTarget);
			break;
		case ELmMovementState::Lm_InAir:
			UpdatePelvisIKOffset(FVector::ZeroVector, FVector::ZeroVector);
			ResetIKOffsets();
			break;
		case ELmMovementState::Lm_Ragdoll:
		default:
			break;
	}
}

void ULmCharacterAnimInstance::UpdateMovementValues() {
	//Interp and set the Velocity Blend.
	VelocityBlend = InterpVelocityBlend(VelocityBlend, CalculateVelocityBlend(), VelocityBlendInterpSpeed, delta_time);

	//Set the Diagonal Scale Amount.
	DiagonalScaleAmount = CalculateDiagonalScaleAmount();

	//Set the Relative Acceleration Amount and Interpolation the Lean Amount.
	RelativeAccelerationAmount = CalculateRelativeAccelerationAmount();
	auto leanAmountTarget = FLmLeanAmount(RelativeAccelerationAmount.X, RelativeAccelerationAmount.Y);
	LeanAmount = InterpLeanAmount(LeanAmount, leanAmountTarget, GroundedLeanInterpSpeed, delta_time);

	//Set the Walk Run Blend
	WalkRunBlend = CalculateWalkRunBlend();

	//Set the Stride Blend
	StrideBlend = CalculateStrideBlend();

	//Set the Standing and Crouching Play Rates
	StandingPlayRate = CalculateStandingPlayRate();
	CrouchingPlayRate = CalculateCrouchingPlayRate();
}

void ULmCharacterAnimInstance::UpdateRotationValues() {
	//Set the Movement Direction
	MovementDirection = CalculateMovementDirection();

	/*Set the Yaw Offsets. These values influence the "YawOffset" curve in the animgraph and are used to offset the characters rotation for more natural movement.
	The curves allow for fine control over how the offset behaves for each movement direction.*/
	const auto deltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(Velocity.ToOrientationRotator(), Character->GetControlRotation());

	const auto vectorValueFB = YawOffset_FB->GetVectorValue(deltaRotator.Yaw);
	FYaw = vectorValueFB.X;
	BYaw = vectorValueFB.Y;

	const auto vectorValueLR = YawOffset_LR->GetVectorValue(deltaRotator.Yaw);
	LYaw = vectorValueLR.X;
	RYaw = vectorValueLR.Y;
}

void ULmCharacterAnimInstance::UpdateInAirValues() {
	//Update the fall speed. Setting this value only while in the air allows you to use it within the AnimGraph for the landing strength. If not, the Z velocity would return to 0 on landing. 
	FallSpeed = Velocity.Z;

	//Set the Land Prediction weight.
	LandPrediction = CalculateLandPrediction();

	//Interp and set the In Air Lean Amount
	auto inAirLeanAmount = CalculateInAirLeanAmount();
	LeanAmount = InterpLeanAmount(LeanAmount, inAirLeanAmount, InAirLeanInterpSpeed, delta_time);
}

void ULmCharacterAnimInstance::UpdateRagdollValues() {
	const auto ragdollVelocitySize = GetOwningComponent()->GetPhysicsLinearVelocity().Size();
	FlailRate = UKismetMathLibrary::MapRangeClamped(ragdollVelocitySize, 0.0f, 1000.0f, 0.0f, 1.0f);
}

bool ULmCharacterAnimInstance::ShouldMoveCheck() {
	//Enable Movement Animations if IsMoving and HasMovementInput, or if the Speed is greater than 150. 
	return (bIsMoving && bHasMovementInput) || Speed > 150.0f;
}

bool ULmCharacterAnimInstance::CanTurnInPlace() {
	//Only perform a Turn In Place check if the character is looking toward the camera in Third Person, and if the "Enable Transition" curve is fully weighted. The Enable_Transition curve is modified within certain states of the AnimBP so that the character can only turn while in those states.
	return RotationMode == ELmRotationMode::Lm_LookingDirection && ViewMode == ELmViewMode::Lm_TPS && GetCurveValue(FName(TEXT("Enable_Transition"))) > 0.99f;
}

bool ULmCharacterAnimInstance::CanRotateInPlace() {
	//Only perform a Rotate In Place Check if the character is Aiming or in First Person.
	return RotationMode == ELmRotationMode::Lm_Aiming || ViewMode == ELmViewMode::Lm_FPS;
}

bool ULmCharacterAnimInstance::CanDynamicTransition() {
	/*Only perform a Dynamic Transition check if the "Enable Transition" curve is fully weighted.
	The Enable_Transition curve is modified within certain states of the AnimBP so that the character can only transition while in those states.*/
	return GetCurveValue(FName(TEXT("Enable_Transition"))) == 1.0f;
}

bool ULmCharacterAnimInstance::CanOverlayTransition() {
	return !bShouldMove && Stance == ELmStance::Lm_Standing;
}

void ULmCharacterAnimInstance::TurnInPlace(const FRotator TargetRotation, const float PlayRateScale, const float StartTime, const bool bOverrideCurrent) {
	//Step 1: Set Turn Angle
	const float TurnAngle = UKismetMathLibrary::NormalizedDeltaRotator(TargetRotation, Character->GetActorRotation()).Yaw;
	FLmTurnInPlaceAsset TargetTurnAsset;

	//Step 2: Choose Turn Asset based on the Turn Angle and Stance
	if (FMath::Abs(TurnAngle) < Turn180Threshold) {
		if (TurnAngle < 0.0f) {
			if (Stance == ELmStance::Lm_Standing) {
				TargetTurnAsset = N_TurnIP_L90;
			} else {
				TargetTurnAsset = CLF_TurnIP_L90;
			}
		} else {
			if (Stance == ELmStance::Lm_Standing) {
				TargetTurnAsset = N_TurnIP_R90;
			} else {
				TargetTurnAsset = CLF_TurnIP_R90;
			}
		}
	} else {
		if (TurnAngle < 0.0f) {
			if (Stance == ELmStance::Lm_Standing) {
				TargetTurnAsset = N_TurnIP_L180;
			} else {
				TargetTurnAsset = CLF_TurnIP_L180;
			}
		} else {
			if (Stance == ELmStance::Lm_Standing) {
				TargetTurnAsset = N_TurnIP_R180;
			} else {
				TargetTurnAsset = CLF_TurnIP_R180;
			}
		}
	}

	//Step 3: If the Target Turn Animation is not playing or set to be overriden, play the turn animation as a dynamic montage.
	if (bOverrideCurrent || !IsPlayingSlotAnimation(TargetTurnAsset.Animation, TargetTurnAsset.SlotName)) {
		PlaySlotAnimationAsDynamicMontage(TargetTurnAsset.Animation, TargetTurnAsset.SlotName, 0.2f, 0.2f, TargetTurnAsset.PlayRate * PlayRateScale, 1, 0.0f, StartTime);

		//Step 4: Scale the rotation amount (gets scaled in animgraph) to compensate for turn angle (If Allowed) and play rate.
		if (TargetTurnAsset.ScaleTurnAngle) {
			RotationScale = PlayRateScale * TargetTurnAsset.PlayRate * (TurnAngle / TargetTurnAsset.AnimatedAngle);
		} else {
			RotationScale = PlayRateScale * TargetTurnAsset.PlayRate;
		}
	}
}

void ULmCharacterAnimInstance::TurnInPlaceCheck() {
	/*Step 1: Check if Aiming angle is outside of the Turn Check Min Angle, and if the Aim Yaw Rate is below the Aim Yaw Rate Limit.
	If so, begin counting the Elapsed Delay Time. If not, reset the Elapsed Delay Time.
	This ensures the conditions remain true for a sustained peroid of time before turning in place.*/
	if (AimYawRate < AimYawRateLimit && FMath::Abs(AimingAngle.X)>TurnCheckMinAngle) {
		ElapsedDelayTime += delta_time;

		//Step 2: Check if the Elapsed Delay time exceeds the set delay (mapped to the turn angle range). If so, trigger a Turn In Place.
		const float tmp = UKismetMathLibrary::MapRangeClamped(FMath::Abs(AimingAngle.X), TurnCheckMinAngle, 180.0f, MinAngleDelay, MaxAngleDelay);
		if (ElapsedDelayTime > tmp) {
			TurnInPlace(FRotator(0.0f, AimingRotation.Yaw, 0.0f), 1.0f, 0.0f, false);
		}
	} else {
		ElapsedDelayTime = 0.0f;
	}
}

void ULmCharacterAnimInstance::RotateInPlaceCheck() {
	//Step 1: Check if the character should rotate left or right by checking if the Aiming Angle exceeds the threshold.
	bRotateL = AimingAngle.X < RotateMinThreshold;
	bRotateR = AimingAngle.X > RotateMaxThreshold;

	/*Step 2: If the character should be rotating, set the Rotate Rate to scale with the Aim Yaw Rate. This makes the character rotate faster when moving the camera faster.*/
	if (bRotateL || bRotateR) {
		RotateRate = UKismetMathLibrary::MapRangeClamped(AimYawRate, AimYawRateMinRange, AimYawRateMaxRange, MinPlayRate, MaxPlayRate);
	}
}

void ULmCharacterAnimInstance::DynamicTransitionCheck() {
	/*Check each foot to see if the location difference between the IK_Foot bone and its desired / target location (determined via a virtual bone) exceeds a threshold.
	If it does, play an additive transition animation on that foot. The currently set transition plays the second half of a 2 foot transition animation, so that only a single foot moves.
	Because only the IK_Foot bone can be locked, the separate virtual bone allows the system to know its desired location when locked.*/
	const float distanceL = ULmHelpers::GetDistanceBetweenTwoSocketsAndMapRange(GetOwningComponent(), FName(TEXT("ik_foot_l")), RTS_Component, FName(TEXT("VB foot_target_l")), RTS_Component, false, 0.0f, 0.0f, 0.0f, 0.0f);
	if (distanceL > 8.0f)
		PlayDynamicTransition(0.1f, FLmDynamicMontageParams(ALS_N_Transition_R, 0.2f, 0.2f, 1.5f, 0.8f));

	const float distanceR = ULmHelpers::GetDistanceBetweenTwoSocketsAndMapRange(GetOwningComponent(), FName(TEXT("ik_foot_r")), RTS_Component, FName(TEXT("VB foot_target_r")), RTS_Component, false, 0.0f, 0.0f, 0.0f, 0.0f);
	if (distanceR > 8.0f)
		PlayDynamicTransition(0.1f, FLmDynamicMontageParams(ALS_N_Transition_L, 0.2f, 0.2f, 1.5f, 0.8f));
}

FLmVelocityBlend ULmCharacterAnimInstance::CalculateVelocityBlend() {
	/*Calculate the Velocity Blend. This value represents the velocity amount of the actor in each direction (normalized so that diagonals equal .5 for each direction),
	 *and is used in a BlendMulti node to produce better directional blending than a standard blend space.*/
	const FVector LocRelativeVelocityDir = Character->GetActorRotation().UnrotateVector(Velocity.GetSafeNormal());
	const float Sum = FMath::Abs(LocRelativeVelocityDir.X) + FMath::Abs(LocRelativeVelocityDir.Y) + FMath::Abs(LocRelativeVelocityDir.Z);

	const FVector RelativeDirection = LocRelativeVelocityDir / Sum;

	return FLmVelocityBlend(FMath::Clamp(RelativeDirection.X, 0.0f, 1.0f), FMath::Abs(FMath::Clamp(RelativeDirection.X, -1.0f, 0.0f)), FMath::Abs(FMath::Clamp(RelativeDirection.Y, -1.0f, 0.0f)), FMath::Clamp(RelativeDirection.Y, 0.0f, 1.0f));
}

float ULmCharacterAnimInstance::CalculateDiagonalScaleAmount() {
	//Calculate the Diagonal Scale Amount. This value is used to scale the Foot IK Root bone to make the Foot IK bones cover more distance on the diagonal blends.
	//Without scaling, the feet would not move far enough on the diagonal direction due to the linear translational blending of the IK bones. The curve is used to easily map the value.
	return DiagonalScaleAmountCurve->GetFloatValue(FMath::Abs(VelocityBlend.F + VelocityBlend.B));
}

FVector ULmCharacterAnimInstance::CalculateRelativeAccelerationAmount() {
	//Calculate the Relative Acceleration Amount. This value represents the current amount of acceleration / deceleration relative to the actor rotation.
	//It is normalized to a range of -1 to 1 so that -1 equals the Max Braking Deceleration, and 1 equals the Max Acceleration of the Character Movement Component.
	const float max = FVector::DotProduct(Acceleration, Velocity) > 0 ?
		Character->GetCharacterMovement()->GetMaxAcceleration() :
		Character->GetCharacterMovement()->GetMaxBrakingDeceleration();

	return  Character->GetActorRotation().UnrotateVector(Acceleration.GetClampedToMaxSize(max) / max);
}

float ULmCharacterAnimInstance::CalculateWalkRunBlend() {
	//Calculate the Walk Run Blend. This value is used within the BlendSpaces to blend between walking and running.
	return Gait == ELmGait::Lm_Walking ? 0.0f : 1.0f;
}

float ULmCharacterAnimInstance::CalculateStrideBlend() {
	//Calculate the Stride Blend. This value is used within the blendSpaces to scale the stride (distance feet travel) so that the character can walk or run at different movement speeds.
	//It also allows the walk or run gait animations to blend independently while still matching the animation speed to the movement speed, preventing the character from needing to play a half walk+half run blend.
	//The curves are used to map the stride amount to the speed for maximum control.
	const float LerpedA = FMath::Lerp(StrideBlend_N_Walk->GetFloatValue(Speed), StrideBlend_N_Run->GetFloatValue(Speed), GetAnimCurveClamped(FName(TEXT("Weight_Gait")), -1.0f, 0.0f, 1.0f));
	return FMath::Lerp(LerpedA, StrideBlend_C_Walk->GetFloatValue(Speed), GetCurveValue(FName(TEXT("BasePose_CLF"))));
}

float ULmCharacterAnimInstance::CalculateStandingPlayRate() {
	/*Calculate the Play Rate by dividing the Character's speed by the Animated Speed for each gait. The lerps are determined by the "Weight_Gait" anim curve that exists on every locomotion cycle so that the play rate is always in sync with the currently blended animation. The value is also divided by the Stride Blend and the mesh scale so that the play rate increases as the stride or scale gets smaller.*/
	const float lerpedA = FMath::Lerp(Speed / AnimatedWalkSpeed, Speed / AnimatedRunSpeed, GetAnimCurveClamped(FName(TEXT("Weight_Gait")), -1.0f, 0.0f, 1.0f));
	const float SecondLerpedLevel = FMath::Lerp(lerpedA, Speed / AnimatedSprintSpeed, GetAnimCurveClamped(TEXT("Weight_Gait"), -2.0f, 0.0f, 1.0f));

	const float tmp = SecondLerpedLevel / StrideBlend;
	return FMath::Clamp(tmp / GetOwningComponent()->GetComponentScale().Z, 0.0f, 3.0f);
}

float ULmCharacterAnimInstance::CalculateCrouchingPlayRate() {
	//Calculate the Crouching Play Rate by dividing the Character's speed by the Animated Speed. This value needs to be separate from the standing play rate to improve the blend from crouch to stand while in motion.

	const float x = Speed / AnimatedCrouchSpeed;
	const float y = x / StrideBlend;
	const float z = y / GetOwningComponent()->GetComponentScale().Z;
	return FMath::Clamp(z, 0.0f, 2.0f);
}

float ULmCharacterAnimInstance::CalculateLandPrediction() {
	/*Calculate the land prediction weight by tracing in the velocity direction to find a walkable surface the character is falling toward, and getting the 'Time' (range of 0-1, 1 being maximum, 0 being about to land) till impact. The Land Prediction Curve is used to control how the time affects the final weight for a smooth blend*/

	if (FallSpeed < -200.0f)
		return 0.0f;

	const auto capsule = Character->GetCapsuleComponent();
	const auto start = capsule->GetComponentLocation();
	const auto end = start + FVector(Velocity.X, Velocity.Y, FMath::Clamp(Velocity.Z, -4000.0f, -200.0f)).GetUnsafeNormal() * UKismetMathLibrary::MapRangeClamped(Velocity.Z, 0.0f, -4000.0f, 50.0f, 2000.0f);

	FHitResult HitResult;
	const TArray<AActor*> toIgnore;

	UKismetSystemLibrary::CapsuleTraceSingleByProfile(this, start, end, capsule->GetUnscaledCapsuleRadius(), capsule->GetUnscaledCapsuleHalfHeight(), FName(TEXT("ALS_Character")), false, toIgnore, GetDebugTraceType(EDrawDebugTrace::ForOneFrame), HitResult, true);

	if (HitResult.bBlockingHit && Character->GetCharacterMovement()->IsWalkable(HitResult))
		return FMath::Lerp(LandPredictionCurve->GetFloatValue(HitResult.Time), 0.0f, GetCurveValue(FName(TEXT("Mask_LandPrediction"))));
	return 0.0f;
}

FLmLeanAmount ULmCharacterAnimInstance::CalculateInAirLeanAmount() {
	/*Use the relative Velocity direction and amount to determine how much the character should lean while in air.
	 The Lean In Air curve gets the Fall Speed and is used as a multiplier to smoothly reverse the leaning direction when transitioning from moving upwards to moving downwards.*/

	const auto tmp1 = Character->GetActorRotation().UnrotateVector(Velocity) / 350.0f;
	const auto tmp2 = FVector2D(tmp1.Y, tmp1.X) * LeanInAirCurve->GetFloatValue(FallSpeed);
	return FLmLeanAmount(tmp2.Y, tmp2.X);
}

FLmFootOffset ULmCharacterAnimInstance::SetFootOffsets(FName EnableFootIKCurve, FName IKFootBone, FName RootBone, FLmFootOffset params) {
	//Only update Foot IK offset values if the Foot IK curve has a weight. If it equals 0, clear the offset values.
	if (GetCurveValue(EnableFootIKCurve) > 0.0f) {

		//Step 1: Trace downward from the foot location to find the geometry. If the surface is walkable, save the Impact Location and Normal.
		FRotator TargetRotationOffset = FRotator(0.0f, 0.0f, 0.0f);

		const auto tmp = GetOwningComponent()->GetSocketLocation(IKFootBone);
		const auto IKFootFloorLocation = FVector(tmp.X, tmp.Y, GetOwningComponent()->GetSocketLocation(RootBone).Z);
		const auto channel = UEngineTypes::ConvertToTraceType(ECC_Visibility);

		FHitResult HitResult;
		const TArray<AActor*> toIgnore;

		UKismetSystemLibrary::LineTraceSingle(this, IKFootFloorLocation + FVector(0.0f, 0.0f, IK_TraceDistanceAboveFoot), IKFootFloorLocation - FVector(0.0f, 0.0f, IK_TraceDistanceBelowFoot), channel, false, toIgnore, GetDebugTraceType(EDrawDebugTrace::ForOneFrame), HitResult, true);

		if (Character->GetCharacterMovement()->IsWalkable(HitResult)) {
			//Step 1.1: Find the difference in location from the Impact point and the expected (flat) floor location. These values are offset by the normal multiplied by the foot height to get better behavior on angled surfaces.
			params.LocationTarget = HitResult.ImpactPoint + HitResult.ImpactNormal * FootHeight - (IKFootFloorLocation + FVector::UpVector * FootHeight);

			//Step 1.2: Calculate the Rotation offset by getting the Atan2 of the Impact Normal.
			TargetRotationOffset = FRotator(-UKismetMathLibrary::DegAtan2(HitResult.ImpactNormal.X, HitResult.ImpactNormal.Z), 0.0f, UKismetMathLibrary::DegAtan2(HitResult.ImpactNormal.Y, HitResult.ImpactNormal.Z));
		}

		//Step 2: Interp the Current Location Offset to the new target value. Interpolate at different speeds based on whether the new target is above or below the current one.
		params.LocationOffset = UKismetMathLibrary::VInterpTo(params.LocationOffset, params.LocationTarget, delta_time, params.LocationOffset.Z > params.LocationTarget.Z ? 30.0f : 15.0f);

		//Step 3: Interp the Current Rotation Offset to the new target value.
		params.RotationOffset = UKismetMathLibrary::RInterpTo(params.RotationOffset, TargetRotationOffset, delta_time, 30.0f);

	} else {
		params.LocationOffset = FVector::ZeroVector;
		params.RotationOffset = FRotator::ZeroRotator;
	}

	return params;
}

void ULmCharacterAnimInstance::UpdatePelvisIKOffset(FVector FootOffset_L_Target, FVector FootOffset_R_Target) {
	//Calculate the Pelvis Alpha by finding the average Foot IK weight. If the alpha is 0, clear the offset.
	PelvisAlpha = (GetCurveValue(FName(TEXT("Enable_FootIK_L"))) + GetCurveValue(FName(TEXT("Enable_FootIK_R")))) / 2.0f;

	if (PelvisAlpha > 0) {

		//Step 1: Set the new Pelvis Target to be the lowest Foot Offset
		const FVector PelvisTarget = FootOffset_L_Target.Z < FootOffset_R_Target.Z ? FootOffset_L_Target : FootOffset_R_Target;

		//Step 2: Interp the Current Pelvis Offset to the new target value. Interpolate at different speeds based on whether the new target is above or below the current one.
		PelvisOffset = UKismetMathLibrary::VInterpTo(PelvisOffset, PelvisTarget, delta_time, PelvisTarget.Z > PelvisOffset.Z ? 10.0f : 15.0f);

	} else {
		PelvisOffset = FVector::ZeroVector;
	}
}

FLmFootLock ULmCharacterAnimInstance::UpdateFootLock(FName Enable_FootIK_Curve, FName FootLockCurve, FName IKFootBone, FLmFootLock lastValue) {
	if (GetCurveValue(Enable_FootIK_Curve) > 0.f) {
		float FootLockCurveValue = GetCurveValue(FootLockCurve);

		if (FootLockCurveValue < lastValue.Alpha || FootLockCurveValue >= 0.99f)
			lastValue.Alpha = FootLockCurveValue;

		if (lastValue.Alpha >= 0.99f) {
			FTransform tmp = GetOwningComponent()->GetSocketTransform(IKFootBone, RTS_Component);
			lastValue.Location = tmp.GetLocation();
			lastValue.Rotation = tmp.Rotator();
		}

		if (lastValue.Alpha > 0) {

			FRotator rotation_diff = FRotator::ZeroRotator;
			FVector location_diff = FVector::Zero();

			if (Character->GetCharacterMovement()->IsMovingOnGround()) {
				rotation_diff = Character->GetActorRotation() - Character->GetCharacterMovement()->GetLastUpdateRotation();
				rotation_diff.Normalize();
			}

			location_diff = GetOwningComponent()->GetComponentRotation().UnrotateVector(Velocity * GetWorld()->GetDeltaSeconds());

			lastValue.Location = UKismetMathLibrary::RotateAngleAxis(lastValue.Location - location_diff, rotation_diff.Yaw, FVector::DownVector);
			lastValue.Rotation = lastValue.Rotation - rotation_diff;
			lastValue.Rotation.Normalize();
		}
	}
	return lastValue;
}

ELmMovementDirection ULmCharacterAnimInstance::CalculateMovementDirection() {
	if (Gait != ELmGait::Lm_Sprinting && RotationMode != ELmRotationMode::Lm_VelocityDirection)
		return CalculateQuadrant(MovementDirection, 70.0f, -70.0, 110.0f, -110.0f, 5.0f, UKismetMathLibrary::NormalizedDeltaRotator(Velocity.ToOrientationRotator(), AimingRotation).Yaw);

	return ELmMovementDirection::Lm_Forward;
}

ELmMovementDirection ULmCharacterAnimInstance::CalculateQuadrant(ELmMovementDirection Current, float FR_Threshold, float FL_Threshold, float BR_Threshold, float BL_Threshold, float buffer, float angle) {
	//Take the input angle and determine its quadrant (direction). Use the current Movement Direction to increase or decrease the buffers on the angle ranges for each quadrant.
	if (AngleInRange(angle, FL_Threshold, FR_Threshold, buffer, Current != ELmMovementDirection::Lm_Forward || Current != ELmMovementDirection::Lm_Backward))
		return ELmMovementDirection::Lm_Forward;

	if (AngleInRange(angle, FR_Threshold, BR_Threshold, buffer, Current != ELmMovementDirection::Lm_Right || Current != ELmMovementDirection::Lm_Left))
		return ELmMovementDirection::Lm_Right;

	if (AngleInRange(angle, BL_Threshold, FL_Threshold, buffer, Current != ELmMovementDirection::Lm_Right || Current != ELmMovementDirection::Lm_Left))
		return ELmMovementDirection::Lm_Left;

	return ELmMovementDirection::Lm_Backward;
}

bool ULmCharacterAnimInstance::AngleInRange(float angle, float minAngle, float maxAngle, float buffer, bool IncreaseBuffer) {
	if (IncreaseBuffer)
		return UKismetMathLibrary::InRange_FloatFloat(angle, minAngle - buffer, maxAngle + buffer, true, true);

	return UKismetMathLibrary::InRange_FloatFloat(angle, minAngle + buffer, maxAngle - buffer, true, true);
}

FLmVelocityBlend ULmCharacterAnimInstance::InterpVelocityBlend(const FLmVelocityBlend current, const FLmVelocityBlend target, const float interpSpeed, const float deltaTime) {
	const float f = UKismetMathLibrary::FInterpTo(current.F, target.F, deltaTime, interpSpeed);
	const float b = UKismetMathLibrary::FInterpTo(current.B, target.B, deltaTime, interpSpeed);
	const float l = UKismetMathLibrary::FInterpTo(current.L, target.L, deltaTime, interpSpeed);
	const float r = UKismetMathLibrary::FInterpTo(current.R, target.R, deltaTime, interpSpeed);

	return FLmVelocityBlend(f, b, l, r);
}

FLmLeanAmount ULmCharacterAnimInstance::InterpLeanAmount(FLmLeanAmount& current, FLmLeanAmount& target, const float interpSpeed, const float deltaTime) {
	auto retValue = FLmLeanAmount();
	retValue.FrontBack = FMath::FInterpTo(current.FrontBack, target.FrontBack, deltaTime, interpSpeed);
	retValue.LeftRight = FMath::FInterpTo(current.LeftRight, target.LeftRight, deltaTime, interpSpeed);
	return retValue;
}

void ULmCharacterAnimInstance::Response_AnimNotifyPivot() {
	bPivot = Speed < TriggerPivotSpeedLimit;

	if (GetWorld()->GetTimerManager().GetTimerRemaining(AnimNotifyPivotHandle) > 0)
		return;

	FTimerDelegate PivotDel;
	PivotDel.BindLambda([this] {
		GetWorld()->GetTimerManager().ClearTimer(AnimNotifyPivotHandle);
		bPivot = false;
	});
	GetWorld()->GetTimerManager().SetTimer(AnimNotifyPivotHandle, PivotDel, 0.1f, false);
}

TEnumAsByte<EDrawDebugTrace::Type> ULmCharacterAnimInstance::GetDebugTraceType(TEnumAsByte<EDrawDebugTrace::Type> ShowTraceType) {
	const auto playerController = static_cast<ALmPlayerController*>(UGameplayStatics::GetPlayerController(this, 0));
	if (playerController && playerController->GetClass()->ImplementsInterface(ULmControllerInterface::StaticClass())) {
		const bool bShowTraces = ILmControllerInterface::Execute_GetDebugInfo(playerController).bShowTraces;
		return bShowTraces ? ShowTraceType : EDrawDebugTrace::None;
	}

	return EDrawDebugTrace::None;
}

void ULmCharacterAnimInstance::PlayTransition(FLmDynamicMontageParams params) {
	PlaySlotAnimationAsDynamicMontage(params.Animation, FName(TEXT("Grounded Slot")), params.BlendInTime, params.BlendOutTime, params.PlayRate, 1, 0.0f, params.StartTime);
}

void ULmCharacterAnimInstance::PlayDynamicTransition(const float ReTriggerDelay, const FLmDynamicMontageParams Parameters) {
	//Ignore incoming requests when there is an existing request in progress
	if (bDynamicTransitionGate_IsOpen) {
		bDynamicTransitionGate_IsOpen = false;

		GetWorld()->GetTimerManager().ClearTimer(DynamicTransitionHandle);

		PlaySlotAnimationAsDynamicMontage(Parameters.Animation, FName(TEXT("Grounded Slot")), Parameters.BlendInTime, Parameters.BlendOutTime, Parameters.PlayRate, 1, 0.0f, Parameters.StartTime);

		FTimerDelegate DynamicTransitionDel;
		//Binding the function with specific values
		DynamicTransitionDel.BindLambda([this] {
			bDynamicTransitionGate_IsOpen = true;
		});

		GetWorld()->GetTimerManager().SetTimer(DynamicTransitionHandle, DynamicTransitionDel, ReTriggerDelay, false);
	}
}

void ULmCharacterAnimInstance::Jumped_Implementation() {
	if (bJumped)	//Disabling multiple jumping
		return;

	bJumped = true;
	JumpPlayRate = UKismetMathLibrary::MapRangeClamped(Speed, 0.0f, 600.0f, 1.2f, 1.5f);

	if (GetWorld()->GetTimerManager().GetTimerRemaining(JumpedHandle) > 0)
		return;

	FTimerDelegate JumpDelegate;
	JumpDelegate.BindLambda([this] {bJumped = false; });

	GetWorld()->GetTimerManager().SetTimer(JumpedHandle, JumpDelegate, 0.1f, false);
}

void ULmCharacterAnimInstance::SetGroundedEntryState_Implementation(const ELmGroundedEntryState groundedEntryState) {
	this->GroundedEntryState = groundedEntryState;
}

void ULmCharacterAnimInstance::SetOverlayOverrideState_Implementation(const int overlayOverrideState) {
	this->OverlayOverrideState = overlayOverrideState;
}