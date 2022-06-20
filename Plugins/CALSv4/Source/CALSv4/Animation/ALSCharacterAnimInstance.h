

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../Gameplay/ALSBaseCharacter.h"
#include "../ALSEnums.h"
#include "../ALSStructs.h"
#include "ALSCharacterAnimationInterface.h"
#include "ALSCharacterAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class CALSV4_API UALSCharacterAnimInstance : public UAnimInstance, public IALSCharacterAnimationInterface {
	GENERATED_BODY()

public:
	UALSCharacterAnimInstance();
protected:
#pragma region Variables
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		AALSBaseCharacter* Character;
	float DeltaTimeX = 0.0f;
	//Character Information
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		FRotator AimingRotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		FVector Velocity = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		FVector RelativeVelocityDirection = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		FVector Acceleration = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		FVector MovementInput = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		bool bIsMoving = false;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		bool bHasMovementInput = false;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		float Speed = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		float MovementInputAmount = 0.0f;;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		float AimYawRate = 0.0f;;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		float ZoomAmount = 0.0f;;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		EALSMovementState MovementState = EALSMovementState::ALS_None;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		EALSMovementState PrevMovementState = EALSMovementState::ALS_None;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		EALSMovementAction MovementAction = EALSMovementAction::ALS_LowMantle;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		EALSRotationMode RotationMode = EALSRotationMode::ALS_VelocityDirection;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		EALSGait Gait = EALSGait::ALS_Walking;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		EALSStance Stance = EALSStance::ALS_Standing;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		EALSViewMode ViewMode = EALSViewMode::ALS_TPS;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Character Information")
		EALSOverlayState OverlayState = EALSOverlayState::ALS_Default;
	//Anim Graph - Grounded State
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		EALSGroundedEntryState GroundedEntryState = EALSGroundedEntryState::ALS_None;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		EALSMovementDirection MovementDirection = EALSMovementDirection::ALS_Forward;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		EALSHipsDirection TrackedHipsDirection = EALSHipsDirection::ALS_F;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		FVector RelativeAccelerationAmount = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		bool bShouldMove = false;;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		bool bRotateL = false;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		bool bRotateR = false;;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		bool bPivot = false;;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		float RotateRate = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		float RotationScale = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		float DiagonalScaleAmount = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		float WalkRunBlend = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		float StandingPlayRate = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		float CrouchingPlayRate = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		float StrideBlend = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		FALSVelocityBlend VelocityBlend;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		FALSLeanAmount LeanAmount;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		float FYaw = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		float BYaw = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		float LYaw = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Grounded State")
		float RYaw = 0.0f;
	//Anim Graph - Aiming Values
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Aiming Values")
		FRotator SmoothAimingRotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Aiming Values")
		FRotator SpineRotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Aiming Values")
		FVector2D AimingAngle = FVector2D::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Aiming Values")
		FVector2D SmoothedAimingAngle = FVector2D::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Aiming Values")
		float AimSweepTime = 0.5f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Aiming Values")
		float InputYawOffsetTime = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Aiming Values")
		float ForwardYawTime = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Aiming Values")
		float LeftYawTime = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Aiming Values")
		float RightYawTime = 0.0f;
	//Anim Graph - In Air
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - In Air")
		bool bJumped = false;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - In Air")
		float JumpPlayRate = 1.2f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - In Air")
		float FallSpeed = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - In Air")
		float LandPrediction = 1.0f;
	//Anim Graph - LayerBlending
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		int OverlayOverrideState = 0;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float EnableAimOffset = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float EnableHandIK_L = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float EnableHandIK_R = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float BasePose_N = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float BasePose_CLF = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Arm_L = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Arm_L_Add = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Arm_L_LS = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Arm_L_MS = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Arm_R = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Arm_R_Add = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Arm_R_LS = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Arm_R_MS = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Hand_L = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Hand_R = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Legs = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Legs_Add = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Pelvis = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Pelvis_Add = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Spine = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Spine_Add = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Head = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - LayerBlending")
		float Head_Add = 0.0f;
	//Anim Graph - Foot IK
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Foot IK")
		float FootLock_L_Alpha = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Foot IK")
		float FootLock_R_Alpha = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Foot IK")
		FVector FootLock_L_Location = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Foot IK")
		FVector FootLock_R_Location = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Foot IK")
		FRotator FootLock_L_Rotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Foot IK")
		FRotator FootLock_R_Rotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Foot IK")
		FVector FootOffset_L_Location = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Foot IK")
		FVector FootOffset_R_Location = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Foot IK")
		FRotator FootOffset_L_Rotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Foot IK")
		FRotator FootOffset_R_Rotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Foot IK")
		FVector PelvisOffset = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Anim Graph - Foot IK")
		float PelvisAlpha = 0.0f;
	//Turn In Place
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Turn In Place|Setup")
		float TurnCheckMinAngle = 45.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Turn In Place|Setup")
		float Turn180Threshold = 130.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Turn In Place|Setup")
		float AimYawRateLimit = 50.0f;
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Turn In Place|Setup")
		float ElapsedDelayTime = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Turn In Place|Setup")
		float MinAngleDelay = 0.75f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Turn In Place|Setup")
		float MaxAngleDelay = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Turn In Place|Assets")
		FALSTurnInPlaceAsset N_TurnIP_L90;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Turn In Place|Assets")
		FALSTurnInPlaceAsset N_TurnIP_R90;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Turn In Place|Assets")
		FALSTurnInPlaceAsset N_TurnIP_L180;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Turn In Place|Assets")
		FALSTurnInPlaceAsset N_TurnIP_R180;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Turn In Place|Assets")
		FALSTurnInPlaceAsset CLF_TurnIP_L90;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Turn In Place|Assets")
		FALSTurnInPlaceAsset CLF_TurnIP_R90;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Turn In Place|Assets")
		FALSTurnInPlaceAsset CLF_TurnIP_L180;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Turn In Place|Assets")
		FALSTurnInPlaceAsset CLF_TurnIP_R180;
	//Rotate in Place
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Rotate in Place")
		float RotateMinThreshold = -50.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Rotate in Place")
		float RotateMaxThreshold = 50.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Rotate in Place")
		float AimYawRateMinRange = 90.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Rotate in Place")
		float AimYawRateMaxRange = 270.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Rotate in Place")
		float MinPlayRate = 1.15f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Rotate in Place")
		float MaxPlayRate = 3.0f;
	//Blend curves
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Blend Curves")
		UCurveFloat* DiagonalScaleAmountCurve;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Blend Curves")
		UCurveFloat* StrideBlend_N_Walk;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Blend Curves")
		UCurveFloat* StrideBlend_N_Run;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Blend Curves")
		UCurveFloat* StrideBlend_C_Walk;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Blend Curves")
		UCurveFloat* LandPredictionCurve;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Blend Curves")
		UCurveFloat* LeanInAirCurve;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Blend Curves")
		UCurveVector* YawOffset_FB;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Blend Curves")
		UCurveVector* YawOffset_LR;
	//Config
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Config")
		float AnimatedWalkSpeed = 150.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Config")
		float AnimatedRunSpeed = 350.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Config")
		float AnimatedSprintSpeed = 600.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Config")
		float AnimatedCrouchSpeed = 150.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Config")
		float VelocityBlendInterpSpeed = 12.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Config")
		float GroundedLeanInterpSpeed = 4.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Config")
		float InAirLeanInterpSpeed = 4.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Config")
		float SmoothedAimingRotationInterpSpeed = 10.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Config")
		float InputYawOffsetInterpSpeed = 8.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Config")
		float TriggerPivotSpeedLimit = 200.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Config")
		float FootHeight = 13.5f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Config")
		float IK_TraceDistanceAboveFoot = 50.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Config")
		float IK_TraceDistanceBelowFoot = 45.0f;
	//Rag-doll
	UPROPERTY(BlueprintReadOnly, Category = "ALS Anim Instance|Rag-doll")
		float FlailRate = 0.0f;
	//Transitions
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Transitions")
		UAnimSequence* ALS_N_Transition_R;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS Anim Instance|Transitions")
		UAnimSequence* ALS_N_Transition_L;
#pragma endregion

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	//Macros
	UFUNCTION(BlueprintPure)
		virtual float GetAnimCurveClamped(FName Name, float Bias, float ClampMin, float ClampMax);

	//Global Scope
	virtual void ResetIKOffsets();
	//Update Values
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Update Values")
		virtual void UpdateCharacterInfo();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Update Values")
		virtual void UpdateAimingValues();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Update Values")
		virtual void UpdateLayerValues();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Update Values")
		virtual void UpdateFootIK();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Update Values")
		virtual void UpdateMovementValues();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Update Values")
		virtual void UpdateRotationValues();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Update Values")
		virtual void UpdateInAirValues();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Update Values")
		virtual void UpdateRagdollValues();
	//Grounded
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Grounded")
		virtual bool ShouldMoveCheck();
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Grounded")
		virtual bool CanTurnInPlace();
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Grounded")
		virtual bool CanRotateInPlace();
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Grounded")
		virtual bool CanDynamicTransition();
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Grounded")
		virtual bool CanOverlayTransition();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Grounded")
		virtual void TurnInPlace(FRotator TargetRotation, float PlayRateScale, float StartTime, bool bOverrideCurrent);
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Grounded")
		virtual void TurnInPlaceCheck();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Grounded")
		virtual void RotateInPlaceCheck();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Grounded")
		virtual void DynamicTransitionCheck();
	//Movement
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Movement")
		virtual FALSVelocityBlend CalculateVelocityBlend();
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Movement")
		virtual float CalculateDiagonalScaleAmount();
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Movement")
		virtual FVector CalculateRelativeAccelerationAmount();
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Movement")
		virtual float CalculateWalkRunBlend();
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Movement")
		virtual float CalculateStrideBlend();
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Movement")
		virtual float CalculateStandingPlayRate();
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Movement")
		virtual float CalculateCrouchingPlayRate();
	//In Air
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|In Air")
		virtual float CalculateLandPrediction();
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|In Air")
		virtual FALSLeanAmount CalculateInAirLeanAmount();
	//Foot IK
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Foot IK")
		virtual void SetFootOffsets(FName EnableFootIKCurve, FName IKFootBone, FName RootBone, FVector& CurrentLocationTarget, FVector& CurrentLocationOffset, FRotator& CurrentRotationOffset);
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Foot IK")
		virtual void SetPelvisIKOffset(FVector FootOffset_L_Target, FVector FootOffset_R_Target);
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Foot IK")
		virtual void SetFootLocking(FName Enable_FootIK_Curve, FName FootLockCurve, FName IKFootBone, float& CurrentFootLockAlpha, FVector& CurrentFootLockLocation, FRotator& CurrentFootLockRotation);
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Foot IK")
		virtual void SetFootLockOffsets(FVector& LocalLocation, FRotator& LocalRotation);
	//Rotation
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Rotation")
		virtual EALSMovementDirection CalculateMovementDirection();
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Rotation")
		virtual EALSMovementDirection CalculateQuadrant(EALSMovementDirection Current, float FR_Threshold, float FL_Threshold, float BR_Threshold, float BL_Threshold, float buffer, float angle);
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Rotation")
		virtual bool AngleInRange(float angle, float minAngle, float maxAngle, float buffer, bool IncreaseBuffer);
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Rotation")
		virtual FALSVelocityBlend InterpVelocityBlend(FALSVelocityBlend current, FALSVelocityBlend target, float interpSpeed, float deltaTime);
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Rotation")
		virtual FALSLeanAmount InterpLeanAmount(FALSLeanAmount& current, FALSLeanAmount& target, float interpSpeed, float deltaTime);
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Notify Events")
		void AnimNotifyPivot();
	//Debug
	UFUNCTION(BlueprintPure, Category = "Advanced Locomotion System|Anim Instance|Debug")
		virtual TEnumAsByte<EDrawDebugTrace::Type> GetDebugTraceType(TEnumAsByte<EDrawDebugTrace::Type> ShowTraceType);

	//Custom Events
	bool bDynamicTransitionGate_IsOpen = true;
	FTimerHandle AnimNotifyPivotHandle;
	FTimerHandle DynamicTransitionHandle;
	FTimerHandle JumpedHandle;

	//Play Additive Transition Animation
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Custom Events")
		void PlayTransition(FALSDynamicMontageParams params);
	//Play Dynamic Additive Transition Animation
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Custom Events")
		void PlayDynamicTransition(float ReTriggerDelay, FALSDynamicMontageParams Parameters);
	//Interface Events
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Anim Instance|Interface Calls")
		void Jumped();
	virtual void Jumped_Implementation() override;
	/*UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Anim Instance|Interface Calls")
		void JumpedReset();*/

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Anim Instance|Interface Calls")
		void SetGroundedEntryState(EALSGroundedEntryState NewState);
	virtual void SetGroundedEntryState_Implementation(EALSGroundedEntryState NewState) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Anim Instance|Interface Calls")
		void SetOverlayOverrideState(int NewState);
	virtual void SetOverlayOverrideState_Implementation(int NewState) override;

private:
	bool bShouldMove_Last;
};
