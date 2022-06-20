#include "ALSAnimInstance.h"

#include <CALSv4/Data/ALSEnums.h>
#include <CALSv4/Data/ALSStructs.h>
#include <CALSv4/Core/Utilities/ALSHelpers.h>

#include "CALSv4/Core/Player/ALSPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Curves/CurveVector.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


UALSAnimInstance::UALSAnimInstance() {
	RootMotionMode = ERootMotionMode::RootMotionFromMontagesOnly;

#pragma region Setting up the Turn In place assets
	N_TurnIP_L90 = FALSTurnInPlaceAsset();
	N_TurnIP_L90.AnimatedAngle = -90.0f;
	N_TurnIP_L90.SlotName = TEXT("(N) Turn/Rotate");
	N_TurnIP_L90.PlayRate = 1.2f;
	N_TurnIP_L90.ScaleTurnAngle = true;

	const ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_N_TurnIP_L90(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/TurnInPlace/ALS_N_TurnIP_L90.ALS_N_TurnIP_L90'"));
	if (IsValid(ALS_N_TurnIP_L90.Object) && ALS_N_TurnIP_L90.Succeeded())
		N_TurnIP_L90.Animation = ALS_N_TurnIP_L90.Object;
	else
		UALSLogger::LogError(TEXT("Animation not found: ALS_N_TurnIP_L90"));

	N_TurnIP_R90 = FALSTurnInPlaceAsset();
	N_TurnIP_R90.AnimatedAngle = 90.0f;
	N_TurnIP_R90.SlotName = TEXT("(N) Turn/Rotate");
	N_TurnIP_R90.PlayRate = 1.2f;
	N_TurnIP_R90.ScaleTurnAngle = true;
	const ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_N_TurnIP_R90(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/TurnInPlace/ALS_N_TurnIP_R90.ALS_N_TurnIP_R90'"));
	if (IsValid(ALS_N_TurnIP_R90.Object) && ALS_N_TurnIP_R90.Succeeded())
		N_TurnIP_R90.Animation = ALS_N_TurnIP_R90.Object;
	else
		UALSLogger::LogError(TEXT("Animation not found: ALS_N_TurnIP_R90"));

	N_TurnIP_L180 = FALSTurnInPlaceAsset();
	N_TurnIP_L180.AnimatedAngle = -180.0f;
	N_TurnIP_L180.SlotName = TEXT("(N) Turn/Rotate");
	N_TurnIP_L180.PlayRate = 1.2f;
	N_TurnIP_L180.ScaleTurnAngle = true;
	const ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_N_TurnIP_L180(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/TurnInPlace/ALS_N_TurnIP_L180.ALS_N_TurnIP_L180'"));
	if (IsValid(ALS_N_TurnIP_L180.Object) && ALS_N_TurnIP_L180.Succeeded())
		N_TurnIP_L180.Animation = ALS_N_TurnIP_L180.Object;
	else
		UALSLogger::LogError(TEXT("Animation not found: ALS_N_TurnIP_L180"));

	N_TurnIP_R180 = FALSTurnInPlaceAsset();
	N_TurnIP_R180.AnimatedAngle = 180.0f;
	N_TurnIP_R180.SlotName = TEXT("(N) Turn/Rotate");
	N_TurnIP_R180.PlayRate = 1.2f;
	N_TurnIP_R180.ScaleTurnAngle = true;
	const ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_N_TurnIP_R180(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/TurnInPlace/ALS_N_TurnIP_R180.ALS_N_TurnIP_R180'"));
	if (IsValid(ALS_N_TurnIP_R180.Object) && ALS_N_TurnIP_R180.Succeeded())
		N_TurnIP_R180.Animation = ALS_N_TurnIP_R180.Object;
	else
		UALSLogger::LogError(TEXT("Animation not found: ALS_N_TurnIP_R180"));

	CLF_TurnIP_L90 = FALSTurnInPlaceAsset();
	CLF_TurnIP_L90.AnimatedAngle = -90.0f;
	CLF_TurnIP_L90.SlotName = TEXT("(CLF) Turn/Rotate");
	CLF_TurnIP_L90.PlayRate = 1.2f;
	CLF_TurnIP_L90.ScaleTurnAngle = false;
	const ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_CLF_TurnIP_L90(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/TurnInPlace/ALS_CLF_TurnIP_L90.ALS_CLF_TurnIP_L90'"));
	if (IsValid(ALS_CLF_TurnIP_L90.Object) && ALS_CLF_TurnIP_L90.Succeeded())
		CLF_TurnIP_L90.Animation = ALS_CLF_TurnIP_L90.Object;
	else
		UALSLogger::LogError(TEXT("Animation not found: ALS_CLF_TurnIP_L90"));

	CLF_TurnIP_R90 = FALSTurnInPlaceAsset();
	CLF_TurnIP_R90.AnimatedAngle = 90.0f;
	CLF_TurnIP_R90.SlotName = TEXT("(CLF) Turn/Rotate");
	CLF_TurnIP_R90.PlayRate = 1.2f;
	CLF_TurnIP_R90.ScaleTurnAngle = false;
	const ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_CLF_TurnIP_R90(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/TurnInPlace/ALS_CLF_TurnIP_R90.ALS_CLF_TurnIP_R90'"));
	if (IsValid(ALS_CLF_TurnIP_R90.Object) && ALS_CLF_TurnIP_R90.Succeeded())
		CLF_TurnIP_R90.Animation = ALS_CLF_TurnIP_R90.Object;
	else
		UALSLogger::LogError(TEXT("Animation not found: ALS_CLF_TurnIP_R90"));

	CLF_TurnIP_L180 = FALSTurnInPlaceAsset();
	CLF_TurnIP_L180.AnimatedAngle = -180.0f;
	CLF_TurnIP_L180.SlotName = TEXT("(CLF) Turn/Rotate");
	CLF_TurnIP_L180.PlayRate = 1.2f;
	CLF_TurnIP_L180.ScaleTurnAngle = false;
	const ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_CLF_TurnIP_L180(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/TurnInPlace/ALS_CLF_TurnIP_L180.ALS_CLF_TurnIP_L180'"));
	if (IsValid(ALS_CLF_TurnIP_L180.Object) && ALS_CLF_TurnIP_L180.Succeeded())
		CLF_TurnIP_L180.Animation = ALS_CLF_TurnIP_L180.Object;
	else
		UALSLogger::LogError(TEXT("Animation not found: ALS_CLF_TurnIP_L180"));

	CLF_TurnIP_R180 = FALSTurnInPlaceAsset();
	CLF_TurnIP_R180.AnimatedAngle = 180.0f;
	CLF_TurnIP_R180.SlotName = TEXT("(CLF) Turn/Rotate");
	CLF_TurnIP_R180.PlayRate = 1.2f;
	CLF_TurnIP_R180.ScaleTurnAngle = false;
	const ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_CLF_TurnIP_R180(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/TurnInPlace/ALS_CLF_TurnIP_R180.ALS_CLF_TurnIP_R180'"));
	if (IsValid(ALS_CLF_TurnIP_R180.Object) && ALS_CLF_TurnIP_R180.Succeeded())
		CLF_TurnIP_R180.Animation = ALS_CLF_TurnIP_R180.Object;
	else
		UALSLogger::LogError(TEXT("Animation not found: ALS_CLF_TurnIP_R180"));
#pragma endregion

#pragma region Setting Up Blend Curves
	const ConstructorHelpers::FObjectFinder<UCurveFloat> _DiagonalScaleAmountCurve(TEXT("CurveFloat'/Game/AdvancedLocomotionV4/Data/Curves/AnimationBlendCurves/DiagonalScaleAmount.DiagonalScaleAmount'"));
	if (IsValid(_DiagonalScaleAmountCurve.Object) && _DiagonalScaleAmountCurve.Succeeded())
		DiagonalScaleAmountCurve = _DiagonalScaleAmountCurve.Object;
	else
		UALSLogger::LogError(TEXT("Curve not found: DiagonalScaleAmount"));

	const ConstructorHelpers::FObjectFinder<UCurveFloat> _StrideBlend_N_Walk(TEXT("CurveFloat'/Game/AdvancedLocomotionV4/Data/Curves/AnimationBlendCurves/StrideBlend_N_Walk.StrideBlend_N_Walk'"));
	if (IsValid(_StrideBlend_N_Walk.Object) && _StrideBlend_N_Walk.Succeeded())
		StrideBlend_N_Walk = _StrideBlend_N_Walk.Object;
	else
		UALSLogger::LogError(TEXT("Curve not found: StrideBlend_N_Walk"));

	const ConstructorHelpers::FObjectFinder<UCurveFloat> _StrideBlend_N_Run(TEXT("CurveFloat'/Game/AdvancedLocomotionV4/Data/Curves/AnimationBlendCurves/StrideBlend_N_Run.StrideBlend_N_Run'"));
	if (IsValid(_StrideBlend_N_Run.Object) && _StrideBlend_N_Run.Succeeded())
		StrideBlend_N_Run = _StrideBlend_N_Run.Object;
	else
		UALSLogger::LogError(TEXT("Curve not found: StrideBlend_N_Run"));

	const ConstructorHelpers::FObjectFinder<UCurveFloat> _StrideBlend_C_Walk(TEXT("CurveFloat'/Game/AdvancedLocomotionV4/Data/Curves/AnimationBlendCurves/StrideBlend_N_Walk.StrideBlend_N_Walk'"));
	if (IsValid(_StrideBlend_C_Walk.Object) && _StrideBlend_C_Walk.Succeeded())
		StrideBlend_C_Walk = _StrideBlend_C_Walk.Object;
	else
		UALSLogger::LogError(TEXT("Curve not found: StrideBlend_C_Walk"));

	const ConstructorHelpers::FObjectFinder<UCurveFloat> _LandPredictionCurve(TEXT("CurveFloat'/Game/AdvancedLocomotionV4/Data/Curves/AnimationBlendCurves/LandPredictionBlend.LandPredictionBlend'"));
	if (IsValid(_LandPredictionCurve.Object) && _LandPredictionCurve.Succeeded())
		LandPredictionCurve = _LandPredictionCurve.Object;
	else
		UALSLogger::LogError(TEXT("Curve not found: LandPredictionCurve"));

	const ConstructorHelpers::FObjectFinder<UCurveFloat> _LeanInAirAmount(TEXT("CurveFloat'/Game/AdvancedLocomotionV4/Data/Curves/AnimationBlendCurves/LeanInAirAmount.LeanInAirAmount'"));
	if (IsValid(_LeanInAirAmount.Object) && _LeanInAirAmount.Succeeded())
		LeanInAirCurve = _LeanInAirAmount.Object;
	else
		UALSLogger::LogError(TEXT("Curve not found: LeanInAirCurve"));

	const ConstructorHelpers::FObjectFinder<UCurveVector> _YawOffset_FB(TEXT("CurveVector'/Game/AdvancedLocomotionV4/Data/Curves/AnimationBlendCurves/YawOffset_FB.YawOffset_FB'"));
	if (IsValid(_YawOffset_FB.Object) && _YawOffset_FB.Succeeded())
		YawOffset_FB = _YawOffset_FB.Object;
	else
		UALSLogger::LogError(TEXT("Curve not found: YawOffset_FB"));

	const ConstructorHelpers::FObjectFinder<UCurveVector> _YawOffset_LR(TEXT("CurveVector'/Game/AdvancedLocomotionV4/Data/Curves/AnimationBlendCurves/YawOffset_LR.YawOffset_LR'"));
	if (IsValid(_YawOffset_LR.Object) && _YawOffset_LR.Succeeded())
		YawOffset_LR = _YawOffset_LR.Object;
	else
		UALSLogger::LogError(TEXT("Curve not found: YawOffset_LR"));
#pragma endregion

#pragma region Setting Up Transitions
	static ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_N_Transition_R_Finder(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/Transitions/ALS_N_Transition_R.ALS_N_Transition_R'"));
	if (IsValid(ALS_N_Transition_R_Finder.Object) && ALS_N_Transition_R_Finder.Succeeded()) {
		ALS_N_Transition_R = ALS_N_Transition_R_Finder.Object;
	} else {
		UALSLogger::LogError(TEXT("Animation not found: ALS_N_Transition_R"));
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> ALS_N_Transition_L_Finder(TEXT("AnimSequence'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Base/Transitions/ALS_N_Transition_L.ALS_N_Transition_L'"));
	if (IsValid(ALS_N_Transition_L_Finder.Object) && ALS_N_Transition_L_Finder.Succeeded()) {
		ALS_N_Transition_L = ALS_N_Transition_L_Finder.Object;
	} else {
		UALSLogger::LogError(TEXT("Animation not found: ALS_N_Transition_R"));
	}
#pragma endregion

}

void UALSAnimInstance::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();

	//Initialize Anim Instance
	if (TryGetPawnOwner()) {
		Character = static_cast<AALSBaseCharacter*>(TryGetPawnOwner());
		bDynamicTransitionGate_IsOpen = true;
		if (GetWorld()->GetTimerManager().IsTimerPending(DynamicTransitionHandle)) {
			GetWorld()->GetTimerManager().ClearTimer(DynamicTransitionHandle);
		}
	}
}

void UALSAnimInstance::NativeBeginPlay() {
	Super::NativeBeginPlay();
}

void UALSAnimInstance::NativeUpdateAnimation(const float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	//Only update if character is valid
	if (DeltaSeconds == 0 || !Character)
		return;

	DeltaTimeX = DeltaSeconds;

	//Do Every Frame
	UpdateCharacterInfo();
	UpdateAimingValues();
	UpdateLayerValues();
	UpdateFootIK();

	if (MovementState == EALSMovementState::ALS_Grounded) {
		bShouldMove = ShouldMoveCheck();

		if (bShouldMove == bShouldMove_Last) {
			if (bShouldMove) {
				//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, TEXT("While True"));

				//Do While Moving
				UpdateMovementValues();
				UpdateRotationValues();
			} else {
				//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, TEXT("While False"));

				//Do While Not Moving
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
			}
		} else {
			if (bShouldMove) {
				//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, TEXT("Changed to True"));

				//Do When Starting To Move
				ElapsedDelayTime = 0.0f;
				bRotateL = false;
				bRotateR = false;
			}
		}

		bShouldMove_Last = bShouldMove;

	} else if (MovementState == EALSMovementState::ALS_InAir) {
		//Do While InAir
		UpdateInAirValues();
	} else if (MovementState == EALSMovementState::ALS_Ragdoll) {
		//Do While Rag-dolling
		UpdateRagdollValues();
	}
}

float UALSAnimInstance::GetAnimCurveClamped(const FName Name, const float Bias, const float ClampMin, const float ClampMax) {
	const float value = GetCurveValue(Name);
	;	return FMath::Clamp(value + Bias, ClampMin, ClampMax);
}

void UALSAnimInstance::ResetIKOffsets() {
	FootOffset_L_Location = UKismetMathLibrary::VInterpTo(FootOffset_L_Location, FVector::ZeroVector, DeltaTimeX, 15.0f);
	FootOffset_R_Location = UKismetMathLibrary::VInterpTo(FootOffset_R_Location, FVector::ZeroVector, DeltaTimeX, 15.0f);

	FootOffset_L_Rotation = UKismetMathLibrary::RInterpTo(FootOffset_L_Rotation, FRotator::ZeroRotator, DeltaTimeX, 15.0f);
	FootOffset_R_Rotation = UKismetMathLibrary::RInterpTo(FootOffset_R_Rotation, FRotator::ZeroRotator, DeltaTimeX, 15.0f);
}

void UALSAnimInstance::UpdateCharacterInfo() {
	if (Character && Character->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
		const auto values = IALSCharacterInterface::Execute_GetEssentialValues(Character);
		Velocity = values.Velocity;
		Acceleration = values.Acceleration;
		MovementInput = values.MovementInput;
		bIsMoving = values.bIsMoving;
		bHasMovementInput = values.bHasMovementInput;
		Speed = values.Speed;
		MovementInputAmount = values.MovementInputAmount;
		AimingRotation = values.AimingRotation;
		AimYawRate = values.AimYawRate;
		//UALSLogger::LogInfo(*values.ToString());

		const auto states = IALSCharacterInterface::Execute_GetCurrentState(Character);
		MovementState = states.MovementState;
		PrevMovementState = states.PrevMovementState;
		MovementAction = states.MovementAction;
		RotationMode = states.RotationMode;
		Gait = states.ActualGait;
		Stance = states.ActualStance;
		ViewMode = states.ViewMode;
		OverlayState = states.OverlayState;
		//UALSLogger::LogInfo(*states.ToString());
	}
}

void UALSAnimInstance::UpdateAimingValues() {
	//Interp the Aiming Rotation value to achieve smooth aiming rotation changes. Interpolating the rotation before calculating the angle ensures the value is not affected by changes in actor rotation, allowing slow aiming rotation changes with fast actor rotation changes.
	SmoothAimingRotation = UKismetMathLibrary::RInterpTo(SmoothAimingRotation, AimingRotation, DeltaTimeX, SmoothedAimingRotationInterpSpeed);

	//Calculate the Aiming angle and Smoothed Aiming Angle by getting the delta between the aiming rotation and the actor rotation.
	const FRotator actorRotation = Character->GetActorRotation();
	const FRotator delta1 = UKismetMathLibrary::NormalizedDeltaRotator(AimingRotation, actorRotation);
	AimingAngle = FVector2D(delta1.Yaw, delta1.Pitch);
	const FRotator delta2 = UKismetMathLibrary::NormalizedDeltaRotator(SmoothAimingRotation, actorRotation);
	SmoothedAimingAngle = FVector2D(delta2.Yaw, delta2.Pitch);

	//Clamp the Aiming Pitch Angle to a range of 1 to 0 for use in the vertical aim sweeps.
	if (RotationMode != EALSRotationMode::ALS_VelocityDirection) {
		AimSweepTime = UKismetMathLibrary::MapRangeClamped(AimingAngle.Y, -90.0f, 90.0f, 1.0f, 0.0f);
		//Use the Aiming Yaw Angle divided by the number of spine+pelvis bones to get the amount of spine rotation needed to remain facing the camera direction.
		SpineRotation = FRotator(0.0f, AimingAngle.X / 4.0f, 0.0);
	} else {
		//Get the delta between the Movement Input rotation and Actor rotation and map it to a range of 0-1. This value is used in the aim offset behavior to make the character look toward the Movement Input.
		if (bHasMovementInput) {
			const FRotator delta3 = UKismetMathLibrary::NormalizedDeltaRotator(MovementInput.ToOrientationRotator(), actorRotation);
			const float target = UKismetMathLibrary::MapRangeClamped(delta3.Yaw, -180.0f, 180.0f, 0.0f, 1.0f);
			InputYawOffsetTime = UKismetMathLibrary::FInterpTo(InputYawOffsetTime, target, DeltaTimeX, InputYawOffsetInterpSpeed);
		}
	}

	//Separate the Aiming Yaw Angle into 3 separate Yaw Times. These 3 values are used in the Aim Offset behavior to improve the blending of the aim offset when rotating completely around the character. This allows you to keep the aiming responsive but still smoothly blend from left to right or right to left.
	LeftYawTime = UKismetMathLibrary::MapRangeClamped(FMath::Abs(SmoothedAimingAngle.X), 0.0f, 180.0f, 0.5f, 0.0f);
	RightYawTime = UKismetMathLibrary::MapRangeClamped(FMath::Abs(SmoothedAimingAngle.X), 0.0f, 180.0f, 0.5f, 1.0f);
	ForwardYawTime = UKismetMathLibrary::MapRangeClamped(SmoothedAimingAngle.X, -180.0f, 180.0f, 0.0f, 1.0f);
}

void UALSAnimInstance::UpdateLayerValues() {
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

void UALSAnimInstance::UpdateFootIK() {
	//Update Foot Locking values.
	SetFootLocking(FName(TEXT("Enable_FootIK_L")), FName(TEXT("FootLock_L")), FName(TEXT("ik_foot_l")), FootLock_L_Alpha, FootLock_L_Location, FootLock_L_Rotation);
	SetFootLocking(FName(TEXT("Enable_FootIK_R")), FName(TEXT("FootLock_R")), FName(TEXT("ik_foot_r")), FootLock_R_Alpha, FootLock_R_Location, FootLock_R_Rotation);

	if (MovementState == EALSMovementState::ALS_InAir) {
		SetPelvisIKOffset(FVector::ZeroVector, FVector::ZeroVector);
		ResetIKOffsets();
	} else if (MovementState != EALSMovementState::ALS_Ragdoll) {
		FVector FootOffsetRTarget;
		FVector FootOffsetLTarget;

		SetFootOffsets(FName(TEXT("Enable_FootIK_L")), FName(TEXT("ik_foot_l")), FName(TEXT("root")), FootOffsetLTarget, FootOffset_L_Location, FootOffset_L_Rotation);
		SetFootOffsets(FName(TEXT("Enable_FootIK_R")), FName(TEXT("ik_foot_r")), FName(TEXT("root")), FootOffsetRTarget, FootOffset_R_Location, FootOffset_R_Rotation);

		SetPelvisIKOffset(FootOffsetLTarget, FootOffsetRTarget);
	}
}

void UALSAnimInstance::UpdateMovementValues() {
	//Interp and set the Velocity Blend.
	VelocityBlend = InterpVelocityBlend(VelocityBlend, CalculateVelocityBlend(), VelocityBlendInterpSpeed, DeltaTimeX);

	//Set the Diagonal Scale Amount.
	DiagonalScaleAmount = CalculateDiagonalScaleAmount();

	//Set the Relative Acceleration Amount and Interpolation the Lean Amount.
	RelativeAccelerationAmount = CalculateRelativeAccelerationAmount();
	auto leanAmountTarget = FALSLeanAmount(RelativeAccelerationAmount.X, RelativeAccelerationAmount.Y);
	LeanAmount = InterpLeanAmount(LeanAmount, leanAmountTarget, GroundedLeanInterpSpeed, DeltaTimeX);

	//Set the Walk Run Blend
	WalkRunBlend = CalculateWalkRunBlend();

	//Set the Stride Blend
	StrideBlend = CalculateStrideBlend();

	//Set the Standing and Crouching Play Rates
	StandingPlayRate = CalculateStandingPlayRate();
	CrouchingPlayRate = CalculateCrouchingPlayRate();

	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Cyan, FString::Printf(TEXT("VelocityBlend: %s\n  WalkRunBlend: %f, StrideBlend: %f, StandingPlayRate: %f, CrouchingPlayRate: %f"), *VelocityBlend.ToString(), WalkRunBlend, StrideBlend, StandingPlayRate, CrouchingPlayRate));
}

void UALSAnimInstance::UpdateRotationValues() {
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

void UALSAnimInstance::UpdateInAirValues() {
	//Update the fall speed. Setting this value only while in the air allows you to use it within the AnimGraph for the landing strength. If not, the Z velocity would return to 0 on landing. 
	FallSpeed = Velocity.Z;

	//Set the Land Prediction weight.
	LandPrediction = CalculateLandPrediction();

	//Interp and set the In Air Lean Amount
	auto inAirLeanAmount = CalculateInAirLeanAmount();
	LeanAmount = InterpLeanAmount(LeanAmount, inAirLeanAmount, InAirLeanInterpSpeed, DeltaTimeX);
}

void UALSAnimInstance::UpdateRagdollValues() {
	const auto ragdollVelocitySize = GetOwningComponent()->GetPhysicsLinearVelocity().Size();
	FlailRate = UKismetMathLibrary::MapRangeClamped(ragdollVelocitySize, 0.0f, 1000.0f, 0.0f, 1.0f);
}

bool UALSAnimInstance::ShouldMoveCheck() {
	//Enable Movement Animations if IsMoving and HasMovementInput, or if the Speed is greater than 150. 
	return (bIsMoving && bHasMovementInput) || Speed > 150.0f;
}

bool UALSAnimInstance::CanTurnInPlace() {
	//Only perform a Turn In Place check if the character is looking toward the camera in Third Person, and if the "Enable Transition" curve is fully weighted. The Enable_Transition curve is modified within certain states of the AnimBP so that the character can only turn while in those states.
	return RotationMode == EALSRotationMode::ALS_LookingDirection && ViewMode == EALSViewMode::ALS_TPS && GetCurveValue(FName(TEXT("Enable_Transition"))) > 0.99f;
}

bool UALSAnimInstance::CanRotateInPlace() {
	//Only perform a Rotate In Place Check if the character is Aiming or in First Person.
	return RotationMode == EALSRotationMode::ALS_Aiming || ViewMode == EALSViewMode::ALS_FPS;
}

bool UALSAnimInstance::CanDynamicTransition() {
	/*Only perform a Dynamic Transition check if the "Enable Transition" curve is fully weighted.
	The Enable_Transition curve is modified within certain states of the AnimBP so that the character can only transition while in those states.*/
	return GetCurveValue(FName(TEXT("Enable_Transition"))) == 1.0f;
}

bool UALSAnimInstance::CanOverlayTransition() {
	return !bShouldMove && Stance == EALSStance::ALS_Standing;
}

void UALSAnimInstance::TurnInPlace(const FRotator TargetRotation, const float PlayRateScale, const float StartTime, const bool bOverrideCurrent) {
	//Step 1: Set Turn Angle
	const float TurnAngle = UKismetMathLibrary::NormalizedDeltaRotator(TargetRotation, Character->GetActorRotation()).Yaw;
	FALSTurnInPlaceAsset TargetTurnAsset;

	//Step 2: Choose Turn Asset based on the Turn Angle and Stance
	if (FMath::Abs(TurnAngle) < Turn180Threshold) {
		if (TurnAngle < 0.0f) {
			if (Stance == EALSStance::ALS_Standing) {
				TargetTurnAsset = N_TurnIP_L90;
			} else {
				TargetTurnAsset = CLF_TurnIP_L90;
			}
		} else {
			if (Stance == EALSStance::ALS_Standing) {
				TargetTurnAsset = N_TurnIP_R90;
			} else {
				TargetTurnAsset = CLF_TurnIP_R90;
			}
		}
	} else {
		if (TurnAngle < 0.0f) {
			if (Stance == EALSStance::ALS_Standing) {
				TargetTurnAsset = N_TurnIP_L180;
			} else {
				TargetTurnAsset = CLF_TurnIP_L180;
			}
		} else {
			if (Stance == EALSStance::ALS_Standing) {
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

void UALSAnimInstance::TurnInPlaceCheck() {
	/*Step 1: Check if Aiming angle is outside of the Turn Check Min Angle, and if the Aim Yaw Rate is below the Aim Yaw Rate Limit.
	If so, begin counting the Elapsed Delay Time. If not, reset the Elapsed Delay Time.
	This ensures the conditions remain true for a sustained peroid of time before turning in place.*/
	if (AimYawRate < AimYawRateLimit && FMath::Abs(AimingAngle.X)>TurnCheckMinAngle) {
		ElapsedDelayTime += DeltaTimeX;

		//Step 2: Check if the Elapsed Delay time exceeds the set delay (mapped to the turn angle range). If so, trigger a Turn In Place.
		const float tmp = UKismetMathLibrary::MapRangeClamped(FMath::Abs(AimingAngle.X), TurnCheckMinAngle, 180.0f, MinAngleDelay, MaxAngleDelay);
		if (ElapsedDelayTime > tmp) {
			TurnInPlace(FRotator(0.0f, AimingRotation.Yaw, 0.0f), 1.0f, 0.0f, false);
		}
	} else {
		ElapsedDelayTime = 0.0f;
	}
}

void UALSAnimInstance::RotateInPlaceCheck() {
	//Step 1: Check if the character should rotate left or right by checking if the Aiming Angle exceeds the threshold.
	bRotateL = AimingAngle.X < RotateMinThreshold;
	bRotateR = AimingAngle.X > RotateMaxThreshold;

	/*Step 2: If the character should be rotating, set the Rotate Rate to scale with the Aim Yaw Rate. This makes the character rotate faster when moving the camera faster.*/
	if (bRotateL || bRotateR) {
		RotateRate = UKismetMathLibrary::MapRangeClamped(AimYawRate, AimYawRateMinRange, AimYawRateMaxRange, MinPlayRate, MaxPlayRate);
	}
}

void UALSAnimInstance::DynamicTransitionCheck() {
	/*Check each foot to see if the location difference between the IK_Foot bone and its desired / target location (determined via a virtual bone) exceeds a threshold.
	If it does, play an additive transition animation on that foot. The currently set transition plays the second half of a 2 foot transition animation, so that only a single foot moves.
	Because only the IK_Foot bone can be locked, the separate virtual bone allows the system to know its desired location when locked.*/
	const float distanceL = UALSHelpers::GetDistanceBetweenTwoSocketsAndMapRange(GetOwningComponent(), FName(TEXT("ik_foot_l")), RTS_Component, FName(TEXT("VB foot_target_l")), RTS_Component, false, 0.0f, 0.0f, 0.0f, 0.0f);
	if (distanceL > 8.0f)
		PlayDynamicTransition(0.1f, FALSDynamicMontageParams(ALS_N_Transition_R, 0.2f, 0.2f, 1.5f, 0.8f));

	const float distanceR = UALSHelpers::GetDistanceBetweenTwoSocketsAndMapRange(GetOwningComponent(), FName(TEXT("ik_foot_r")), RTS_Component, FName(TEXT("VB foot_target_r")), RTS_Component, false, 0.0f, 0.0f, 0.0f, 0.0f);
	if (distanceR > 8.0f)
		PlayDynamicTransition(0.1f, FALSDynamicMontageParams(ALS_N_Transition_L, 0.2f, 0.2f, 1.5f, 0.8f));
}

FALSVelocityBlend UALSAnimInstance::CalculateVelocityBlend() {
	/*Calculate the Velocity Blend. This value represents the velocity amount of the actor in each direction (normalized so that diagonals equal .5 for each direction),
	 *and is used in a BlendMulti node to produce better directional blending than a standard blend space.*/
	const FVector LocRelativeVelocityDir = Character->GetActorRotation().UnrotateVector(Velocity.GetSafeNormal());
	const float Sum = FMath::Abs(LocRelativeVelocityDir.X) + FMath::Abs(LocRelativeVelocityDir.Y) + FMath::Abs(LocRelativeVelocityDir.Z);

	const FVector RelativeDirection = LocRelativeVelocityDir / Sum;

	return FALSVelocityBlend(FMath::Clamp(RelativeDirection.X, 0.0f, 1.0f), FMath::Abs(FMath::Clamp(RelativeDirection.X, -1.0f, 0.0f)), FMath::Abs(FMath::Clamp(RelativeDirection.Y, -1.0f, 0.0f)), FMath::Clamp(RelativeDirection.Y, 0.0f, 1.0f));

}

float UALSAnimInstance::CalculateDiagonalScaleAmount() {
	//Calculate the Diagonal Scale Amount. This value is used to scale the Foot IK Root bone to make the Foot IK bones cover more distance on the diagonal blends.
	//Without scaling, the feet would not move far enough on the diagonal direction due to the linear translational blending of the IK bones. The curve is used to easily map the value.
	return DiagonalScaleAmountCurve->GetFloatValue(FMath::Abs(VelocityBlend.F + VelocityBlend.B));
}

FVector UALSAnimInstance::CalculateRelativeAccelerationAmount() {
	//Calculate the Relative Acceleration Amount. This value represents the current amount of acceleration / deceleration relative to the actor rotation.
	//It is normalized to a range of -1 to 1 so that -1 equals the Max Braking Deceleration, and 1 equals the Max Acceleration of the Character Movement Component.
	const float max = FVector::DotProduct(Acceleration, Velocity) > 0 ?
		Character->GetCharacterMovement()->GetMaxAcceleration() :
		Character->GetCharacterMovement()->GetMaxBrakingDeceleration();

	return  Character->GetActorRotation().UnrotateVector(Acceleration.GetClampedToMaxSize(max) / max);
}

float UALSAnimInstance::CalculateWalkRunBlend() {
	//Calculate the Walk Run Blend. This value is used within the BlendSpaces to blend between walking and running.
	return Gait == EALSGait::ALS_Walking ? 0.0f : 1.0f;
}

float UALSAnimInstance::CalculateStrideBlend() {
	//Calculate the Stride Blend. This value is used within the blendSpaces to scale the stride (distance feet travel) so that the character can walk or run at different movement speeds.
	//It also allows the walk or run gait animations to blend independently while still matching the animation speed to the movement speed, preventing the character from needing to play a half walk+half run blend.
	//The curves are used to map the stride amount to the speed for maximum control.
	const float LerpedA = FMath::Lerp(StrideBlend_N_Walk->GetFloatValue(Speed), StrideBlend_N_Run->GetFloatValue(Speed), GetAnimCurveClamped(FName(TEXT("Weight_Gait")), -1.0f, 0.0f, 1.0f));
	return FMath::Lerp(LerpedA, StrideBlend_C_Walk->GetFloatValue(Speed), GetCurveValue(FName(TEXT("BasePose_CLF"))));
}

float UALSAnimInstance::CalculateStandingPlayRate() {
	/*Calculate the Play Rate by dividing the Character's speed by the Animated Speed for each gait. The lerps are determined by the "Weight_Gait" anim curve that exists on every locomotion cycle so that the play rate is always in sync with the currently blended animation. The value is also divided by the Stride Blend and the mesh scale so that the play rate increases as the stride or scale gets smaller.*/
	const float lerpedA = FMath::Lerp(Speed / AnimatedWalkSpeed, Speed / AnimatedRunSpeed, GetAnimCurveClamped(FName(TEXT("Weight_Gait")), -1.0f, 0.0f, 1.0f));
	const float SecondLerpedLevel = FMath::Lerp(lerpedA, Speed / AnimatedSprintSpeed, GetAnimCurveClamped(TEXT("Weight_Gait"), -2.0f, 0.0f, 1.0f));

	const float tmp = SecondLerpedLevel / StrideBlend;
	return FMath::Clamp(tmp / GetOwningComponent()->GetComponentScale().Z, 0.0f, 3.0f);
}

float UALSAnimInstance::CalculateCrouchingPlayRate() {
	//Calculate the Crouching Play Rate by dividing the Character's speed by the Animated Speed. This value needs to be separate from the standing play rate to improve the blend from crouch to stand while in motion.

	const float x = Speed / AnimatedCrouchSpeed;
	const float y = x / StrideBlend;
	const float z = y / GetOwningComponent()->GetComponentScale().Z;
	return FMath::Clamp(z, 0.0f, 2.0f);
}

float UALSAnimInstance::CalculateLandPrediction() {
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
		return FMath::Lerp(LandPredictionCurve->GetFloatValue(HitResult.Time), 0.0f,
						   GetCurveValue(FName(TEXT("Mask_LandPrediction"))));
	return 0.0f;
}

FALSLeanAmount UALSAnimInstance::CalculateInAirLeanAmount() {
	/*Use the relative Velocity direction and amount to determine how much the character should lean while in air.
	 The Lean In Air curve gets the Fall Speed and is used as a multiplier to smoothly reverse the leaning direction when transitioning from moving upwards to moving downwards.*/

	const auto tmp1 = Character->GetActorRotation().UnrotateVector(Velocity) / 350.0f;
	const auto tmp2 = FVector2D(tmp1.Y, tmp1.X) * LeanInAirCurve->GetFloatValue(FallSpeed);
	return FALSLeanAmount(tmp2.Y, tmp2.X);
}

void UALSAnimInstance::SetFootOffsets(FName EnableFootIKCurve, FName IKFootBone, FName RootBone, FVector& CurrentLocationTarget, FVector& CurrentLocationOffset, FRotator& CurrentRotationOffset) {
	//Only update Foot IK offset values if the Foot IK curve has a weight. If it equals 0, clear the offset values.
	if (GetCurveValue(EnableFootIKCurve) <= 0.0f) {
		UALSHelpers::SetFVectorByRef(CurrentLocationOffset, FVector::ZeroVector);
		UALSHelpers::SetFRotatorByRef(CurrentRotationOffset, FRotator::ZeroRotator);
		return;
	}


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
		const auto tmpVector = HitResult.ImpactPoint + HitResult.ImpactNormal * FootHeight - (IKFootFloorLocation + FVector::UpVector * FootHeight);

		UALSHelpers::SetFVectorByRef(CurrentLocationTarget, tmpVector);

		//Step 1.2: Calculate the Rotation offset by getting the Atan2 of the Impact Normal.
		TargetRotationOffset = FRotator(-UKismetMathLibrary::DegAtan2(HitResult.ImpactNormal.X, HitResult.ImpactNormal.Z), 0.0f, UKismetMathLibrary::DegAtan2(HitResult.ImpactNormal.Y, HitResult.ImpactNormal.Z));
	}

	//Step 2: Interp the Current Location Offset to the new target value. Interpolate at different speeds based on whether the new target is above or below the current one.
	UALSHelpers::SetFVectorByRef(CurrentLocationOffset, UKismetMathLibrary::VInterpTo(CurrentLocationOffset, CurrentLocationTarget, DeltaTimeX, CurrentLocationOffset.Z > CurrentLocationTarget.Z ? 30.0f : 15.0f));

	//Step 3: Interp the Current Rotation Offset to the new target value.
	UALSHelpers::SetFRotatorByRef(CurrentRotationOffset, UKismetMathLibrary::RInterpTo(CurrentRotationOffset, TargetRotationOffset, DeltaTimeX, 30.0f));
}

void UALSAnimInstance::SetPelvisIKOffset(FVector FootOffset_L_Target, FVector FootOffset_R_Target) {
	//Calculate the Pelvis Alpha by finding the average Foot IK weight. If the alpha is 0, clear the offset.
	PelvisAlpha = (GetCurveValue(FName(TEXT("Enable_FootIK_L"))) + GetCurveValue(FName(TEXT("Enable_FootIK_R")))) / 2.0f;

	if (PelvisAlpha > 0) {

		//Step 1: Set the new Pelvis Target to be the lowest Foot Offset
		const FVector PelvisTarget = FootOffset_L_Target.Z < FootOffset_R_Target.Z ? FootOffset_L_Target : FootOffset_R_Target;

		//Step 2: Interp the Current Pelvis Offset to the new target value. Interpolate at different speeds based on whether the new target is above or below the current one.
		PelvisOffset = UKismetMathLibrary::VInterpTo(PelvisOffset, PelvisTarget, DeltaTimeX, PelvisTarget.Z > PelvisOffset.Z ? 10.0f : 15.0f);

	} else {
		PelvisOffset = FVector::ZeroVector;
	}
}

void UALSAnimInstance::SetFootLocking(FName Enable_FootIK_Curve, FName FootLockCurve, FName IKFootBone, float& CurrentFootLockAlpha, FVector& CurrentFootLockLocation, FRotator& CurrentFootLockRotation) {
	//Only update values if FootIK curve has a weight.
	if (GetCurveValue(Enable_FootIK_Curve) <= 0)
		return;

	//Step 1: Set Local FootLock Curve value
	const float FootLockCurveValue = GetCurveValue(FootLockCurve);

	//Step 2: Only update the FootLock Alpha if the new value is less than the current, or it equals 1. This makes it so that the foot can only blend out of the locked position or lock to a new position, and never blend in.
	if (FootLockCurveValue >= 0.99f || FootLockCurveValue < CurrentFootLockAlpha)
		CurrentFootLockAlpha = FootLockCurveValue;

	//Step 3: If the Foot Lock curve equals 1, save the new lock location and rotation in component space.
	if (CurrentFootLockAlpha >= 0.99f) {
		const auto tmpTransform = GetOwningComponent()->GetSocketTransform(IKFootBone, RTS_Component);
		UALSHelpers::SetFVectorByRef(CurrentFootLockLocation, tmpTransform.GetLocation());
		UALSHelpers::SetFRotatorByRef(CurrentFootLockRotation, tmpTransform.GetRotation().Rotator());
	}

	//Step 4: If the Foot Lock Alpha has a weight, update the Foot Lock offsets to keep the foot planted in place while the capsule moves.
	if (CurrentFootLockAlpha > 0.0f)
		SetFootLockOffsets(CurrentFootLockLocation, CurrentFootLockRotation);
}

void UALSAnimInstance::SetFootLockOffsets(FVector& LocalLocation, FRotator& LocalRotation) {
	FRotator RotationDifference;

	//Use the delta between the current and last updated rotation to find how much the foot should be rotated to remain planted on the ground.
	if (Character->GetCharacterMovement()->IsMovingOnGround())
		RotationDifference = UKismetMathLibrary::NormalizedDeltaRotator(Character->GetActorRotation(), Character->GetCharacterMovement()->GetLastUpdateRotation());

	//Get the distance traveled between frames relative to the mesh rotation to find how much the foot should be offset to remain planted on the ground.
	const FVector LocationDifference = GetOwningComponent()->GetComponentRotation().UnrotateVector(Velocity * UGameplayStatics::GetWorldDeltaSeconds(this));

	//Subtract the location difference from the current local location and rotate it by the rotation difference to keep the foot planted in component space.
	UALSHelpers::SetFVectorByRef(LocalLocation, UKismetMathLibrary::RotateAngleAxis(LocalLocation - LocationDifference, RotationDifference.Yaw, FVector::DownVector));

	//Subtract the Rotation Difference from the current Local Rotation to get the new local rotation.
	UALSHelpers::SetFRotatorByRef(LocalRotation, UKismetMathLibrary::NormalizedDeltaRotator(LocalRotation, RotationDifference));
}

EALSMovementDirection UALSAnimInstance::CalculateMovementDirection() {
	//Calculate the Movement Direction. This value represents the direction the character is moving relative to the camera during the Looking direction / Aiming rotation modes, and is used in the Cycle Blending Anim Layers to blend to the appropriate directional states.

	/*if (Gait == EALSGait::ALS_Sprinting)
		return EALSMovementDirection::ALS_Forward;

	if (RotationMode == EALSRotationMode::ALS_VelocityDirection)
		return EALSMovementDirection::ALS_Forward;*/


	if (Gait != EALSGait::ALS_Sprinting && RotationMode != EALSRotationMode::ALS_VelocityDirection) {
		return CalculateQuadrant(MovementDirection, 70.0f, -70.0, 110.0f, -110.0f, 5.0f, UKismetMathLibrary::NormalizedDeltaRotator(Velocity.ToOrientationRotator(), AimingRotation).Yaw);
	}

	return EALSMovementDirection::ALS_Forward;
}

EALSMovementDirection UALSAnimInstance::CalculateQuadrant(EALSMovementDirection Current, float FR_Threshold, float FL_Threshold, float BR_Threshold, float BL_Threshold, float buffer, float angle) {
	//Take the input angle and determine its quadrant (direction). Use the current Movement Direction to increase or decrease the buffers on the angle ranges for each quadrant.
	if (AngleInRange(angle, FL_Threshold, FR_Threshold, buffer, Current != EALSMovementDirection::ALS_Forward || Current != EALSMovementDirection::ALS_Backward))
		return EALSMovementDirection::ALS_Forward;

	if (AngleInRange(angle, FR_Threshold, BR_Threshold, buffer, Current != EALSMovementDirection::ALS_Right || Current != EALSMovementDirection::ALS_Left))
		return EALSMovementDirection::ALS_Right;

	if (AngleInRange(angle, BL_Threshold, FL_Threshold, buffer, Current != EALSMovementDirection::ALS_Right || Current != EALSMovementDirection::ALS_Left))
		return EALSMovementDirection::ALS_Left;

	return EALSMovementDirection::ALS_Backward;
}

bool UALSAnimInstance::AngleInRange(float angle, float minAngle, float maxAngle, float buffer, bool IncreaseBuffer) {
	if (IncreaseBuffer)
		return UKismetMathLibrary::InRange_FloatFloat(angle, minAngle - buffer, maxAngle + buffer, true, true);

	return UKismetMathLibrary::InRange_FloatFloat(angle, minAngle + buffer, maxAngle - buffer, true, true);
}

FALSVelocityBlend UALSAnimInstance::InterpVelocityBlend(const FALSVelocityBlend current, const FALSVelocityBlend target, const float interpSpeed, const float deltaTime) {
	const float f = UKismetMathLibrary::FInterpTo(current.F, target.F, deltaTime, interpSpeed);
	const float b = UKismetMathLibrary::FInterpTo(current.B, target.B, deltaTime, interpSpeed);
	const float l = UKismetMathLibrary::FInterpTo(current.L, target.L, deltaTime, interpSpeed);
	const float r = UKismetMathLibrary::FInterpTo(current.R, target.R, deltaTime, interpSpeed);

	return FALSVelocityBlend(f, b, l, r);
}

FALSLeanAmount UALSAnimInstance::InterpLeanAmount(FALSLeanAmount& current, FALSLeanAmount& target, const float interpSpeed, const float deltaTime) {
	auto retValue = FALSLeanAmount();
	retValue.FrontBack = FMath::FInterpTo(current.FrontBack, target.FrontBack, deltaTime, interpSpeed);
	retValue.LeftRight = FMath::FInterpTo(current.LeftRight, target.LeftRight, deltaTime, interpSpeed);
	return retValue;
}

void UALSAnimInstance::AnimNotifyPivot() {
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

TEnumAsByte<EDrawDebugTrace::Type> UALSAnimInstance::GetDebugTraceType(TEnumAsByte<EDrawDebugTrace::Type> ShowTraceType) {
	const auto playerController = static_cast<AALSPlayerController*>(UGameplayStatics::GetPlayerController(this, 0));
	if (playerController && playerController->GetClass()->ImplementsInterface(UALSControllerInterface::StaticClass())) {
		const bool bShowTraces = IALSControllerInterface::Execute_GetDebugInfo(playerController).bShowTraces;
		return bShowTraces ? ShowTraceType : EDrawDebugTrace::None;
	}

	return EDrawDebugTrace::None;
}

void UALSAnimInstance::PlayTransition(FALSDynamicMontageParams params) {
	PlaySlotAnimationAsDynamicMontage(params.Animation, FName(TEXT("Grounded Slot")), params.BlendInTime, params.BlendOutTime, params.PlayRate, 1, 0.0f, params.StartTime);
}

void UALSAnimInstance::PlayDynamicTransition(const float ReTriggerDelay, const FALSDynamicMontageParams Parameters) {
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

void UALSAnimInstance::Jumped_Implementation() {
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

void UALSAnimInstance::SetGroundedEntryState_Implementation(const EALSGroundedEntryState groundedEntryState) {
	this->GroundedEntryState = groundedEntryState;
}

void UALSAnimInstance::SetOverlayOverrideState_Implementation(const int overlayOverrideState) {
	this->OverlayOverrideState = overlayOverrideState;
}