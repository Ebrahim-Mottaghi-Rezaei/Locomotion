

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../Gameplay/LmBaseCharacter.h"
#include "../LmEnums.h"
#include "../LmStructs.h"
#include "LmCharacterAnimationInterface.h"
#include "LmCharacterAnimInstance.generated.h"

/**
 *
 */
UCLASS(Transient, Blueprintable)
class LOCOMOTION_API ULmCharacterAnimInstance : public UAnimInstance, public ILmCharacterAnimationInterface {
	GENERATED_BODY()

public:
	ULmCharacterAnimInstance();
protected:
#pragma region Variables
	float delta_time = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		ALmBaseCharacter* Character;
	//Character Information
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		FRotator AimingRotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		FVector Velocity = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		FVector RelativeVelocityDirection = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		FVector Acceleration = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		FVector MovementInput = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		bool bIsMoving = false;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		bool bHasMovementInput = false;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		float Speed = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		float MovementInputAmount = 0.0f;;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		float AimYawRate = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		float ZoomAmount = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		ELmMovementState MovementState = ELmMovementState::Lm_None;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		ELmMovementState PrevMovementState = ELmMovementState::Lm_None;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		ELmMovementAction MovementAction = ELmMovementAction::Lm_LowMantle;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		ELmRotationMode RotationMode = ELmRotationMode::Lm_VelocityDirection;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		ELmGait Gait = ELmGait::Lm_Walking;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		ELmStance Stance = ELmStance::Lm_Standing;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		ELmViewMode ViewMode = ELmViewMode::Lm_TPS;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		ELmOverlayState OverlayState = ELmOverlayState::Lm_Default;
	//Anim Graph - Grounded State
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Anim Graph - Grounded State")
		ELmGroundedEntryState GroundedEntryState = ELmGroundedEntryState::Lm_None;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		ELmMovementDirection MovementDirection = ELmMovementDirection::Lm_Forward;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Anim Graph - Grounded State")
		ELmHipsDirection TrackedHipsDirection = ELmHipsDirection::Lm_F;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		FVector RelativeAccelerationAmount = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		bool bShouldMove = false;;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		bool bRotateL = false;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		bool bRotateR = false;;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		bool bPivot = false;;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		float RotateRate = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		float RotationScale = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		float DiagonalScaleAmount = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		float WalkRunBlend = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		float StandingPlayRate = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		float CrouchingPlayRate = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		float StrideBlend = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		FLmVelocityBlend VelocityBlend;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		FLmLeanAmount LeanAmount;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		float FYaw = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		float BYaw = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		float LYaw = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Grounded State")
		float RYaw = 0.0f;
	//Anim Graph - Aiming Values
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Aiming Values")
		FRotator SmoothAimingRotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Aiming Values")
		FRotator SpineRotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Aiming Values")
		FVector2D AimingAngle = FVector2D::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Aiming Values")
		FVector2D SmoothedAimingAngle = FVector2D::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Aiming Values")
		float AimSweepTime = 0.5f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Aiming Values")
		float InputYawOffsetTime = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Aiming Values")
		float ForwardYawTime = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Aiming Values")
		float LeftYawTime = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Aiming Values")
		float RightYawTime = 0.0f;
	//Anim Graph - In Air
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - In Air")
		bool bJumped = false;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - In Air")
		float JumpPlayRate = 1.2f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - In Air")
		float FallSpeed = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - In Air")
		float LandPrediction = 1.0f;
	//Anim Graph - LayerBlending
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		int OverlayOverrideState = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float EnableAimOffset = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float EnableHandIK_L = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float EnableHandIK_R = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float BasePose_N = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float BasePose_CLF = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Arm_L = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Arm_L_Add = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Arm_L_LS = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Arm_L_MS = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Arm_R = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Arm_R_Add = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Arm_R_LS = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Arm_R_MS = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Hand_L = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Hand_R = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Legs = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Legs_Add = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Pelvis = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Pelvis_Add = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Spine = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Spine_Add = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Head = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - LayerBlending")
		float Head_Add = 0.0f;
	//Anim Graph - Foot IK
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Foot IK")
		FLmFootLock FootLock_L;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Foot IK")
		FLmFootLock FootLock_R;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Foot IK")
		FLmFootOffset FootOffsets_L;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Foot IK")
		FLmFootOffset FootOffsets_R;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Foot IK")
		FVector PelvisOffset;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Anim Graph - Foot IK")
		float PelvisAlpha = 0.0f;
	//Turn In Place
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Turn In Place|Setup")
		float TurnCheckMinAngle = 45.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Turn In Place|Setup")
		float Turn180Threshold = 130.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Turn In Place|Setup")
		float AimYawRateLimit = 50.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Turn In Place|Setup")
		float ElapsedDelayTime = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Turn In Place|Setup")
		float MinAngleDelay = 0.75f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Turn In Place|Setup")
		float MaxAngleDelay = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Turn In Place|Assets")
		FLmTurnInPlaceAsset N_TurnIP_L90;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Turn In Place|Assets")
		FLmTurnInPlaceAsset N_TurnIP_R90;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Turn In Place|Assets")
		FLmTurnInPlaceAsset N_TurnIP_L180;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Turn In Place|Assets")
		FLmTurnInPlaceAsset N_TurnIP_R180;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Turn In Place|Assets")
		FLmTurnInPlaceAsset CLF_TurnIP_L90;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Turn In Place|Assets")
		FLmTurnInPlaceAsset CLF_TurnIP_R90;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Turn In Place|Assets")
		FLmTurnInPlaceAsset CLF_TurnIP_L180;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Turn In Place|Assets")
		FLmTurnInPlaceAsset CLF_TurnIP_R180;
	//Rotate in Place
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Rotate in Place")
		float RotateMinThreshold = -50.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Rotate in Place")
		float RotateMaxThreshold = 50.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Rotate in Place")
		float AimYawRateMinRange = 90.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Rotate in Place")
		float AimYawRateMaxRange = 270.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Rotate in Place")
		float MinPlayRate = 1.15f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Rotate in Place")
		float MaxPlayRate = 3.0f;
	//Blend curves
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Blend Curves")
		UCurveFloat* DiagonalScaleAmountCurve;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Blend Curves")
		UCurveFloat* StrideBlend_N_Walk;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Blend Curves")
		UCurveFloat* StrideBlend_N_Run;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Blend Curves")
		UCurveFloat* StrideBlend_C_Walk;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Blend Curves")
		UCurveFloat* LandPredictionCurve;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Blend Curves")
		UCurveFloat* LeanInAirCurve;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Blend Curves")
		UCurveVector* YawOffset_FB;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Blend Curves")
		UCurveVector* YawOffset_LR;
	//Config
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Config")
		float AnimatedWalkSpeed = 150.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Config")
		float AnimatedRunSpeed = 350.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Config")
		float AnimatedSprintSpeed = 600.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Config")
		float AnimatedCrouchSpeed = 150.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Config")
		float VelocityBlendInterpSpeed = 12.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Config")
		float GroundedLeanInterpSpeed = 4.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Config")
		float InAirLeanInterpSpeed = 4.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Config")
		float SmoothedAimingRotationInterpSpeed = 10.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Config")
		float InputYawOffsetInterpSpeed = 8.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Config")
		float TriggerPivotSpeedLimit = 200.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Config")
		float FootHeight = 13.5f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Config")
		float IK_TraceDistanceAboveFoot = 50.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Config")
		float IK_TraceDistanceBelowFoot = 45.0f;
	//Rag-doll
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Rag-doll")
		float FlailRate = 0.0f;
	//Transitions
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Transitions")
		UAnimSequence* ALS_N_Transition_R;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Transitions")
		UAnimSequence* ALS_N_Transition_L;
#pragma endregion

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	//Macros
	UFUNCTION(BlueprintPure, Category = "Locomotion|Macros")
		virtual float GetAnimCurveClamped(FName Name, float Bias, float ClampMin, float ClampMax);

	//Global Scope
	virtual void ResetIKOffsets();
	//Update Values
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Update Values")
		virtual void UpdateCharacterInfo();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Update Values")
		virtual void UpdateAimingValues();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Update Values")
		virtual void UpdateLayerValues();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Update Values")
		virtual void UpdateFootIK();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Update Values")
		virtual void UpdateMovementValues();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Update Values")
		virtual void UpdateRotationValues();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Update Values")
		virtual void UpdateInAirValues();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Update Values")
		virtual void UpdateRagdollValues();
	//Grounded
	UFUNCTION(BlueprintPure, Category = "Locomotion|Grounded")
		virtual bool ShouldMoveCheck();
	UFUNCTION(BlueprintPure, Category = "Locomotion|Grounded")
		virtual bool CanTurnInPlace();
	UFUNCTION(BlueprintPure, Category = "Locomotion|Grounded")
		virtual bool CanRotateInPlace();
	UFUNCTION(BlueprintPure, Category = "Locomotion|Grounded")
		virtual bool CanDynamicTransition();
	UFUNCTION(BlueprintPure, Category = "Locomotion|Grounded")
		virtual bool CanOverlayTransition();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Grounded")
		virtual void TurnInPlace(FRotator TargetRotation, float PlayRateScale, float StartTime, bool bOverrideCurrent);
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Grounded")
		virtual void TurnInPlaceCheck();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Grounded")
		virtual void RotateInPlaceCheck();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Grounded")
		virtual void DynamicTransitionCheck();
	//Movement
	UFUNCTION(BlueprintPure, Category = "Locomotion|Movement")
		virtual FLmVelocityBlend CalculateVelocityBlend();
	UFUNCTION(BlueprintPure, Category = "Locomotion|Movement")
		virtual float CalculateDiagonalScaleAmount();
	UFUNCTION(BlueprintPure, Category = "Locomotion|Movement")
		virtual FVector CalculateRelativeAccelerationAmount();
	UFUNCTION(BlueprintPure, Category = "Locomotion|Movement")
		virtual float CalculateWalkRunBlend();
	UFUNCTION(BlueprintPure, Category = "Locomotion|Movement")
		virtual float CalculateStrideBlend();
	UFUNCTION(BlueprintPure, Category = "Locomotion|Movement")
		virtual float CalculateStandingPlayRate();
	UFUNCTION(BlueprintPure, Category = "Locomotion|Movement")
		virtual float CalculateCrouchingPlayRate();
	//In Air
	UFUNCTION(BlueprintPure, Category = "Locomotion|In Air")
		virtual float CalculateLandPrediction();
	UFUNCTION(BlueprintPure, Category = "Locomotion|In Air")
		virtual FLmLeanAmount CalculateInAirLeanAmount();
	//Foot IK
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Anim Instance|Foot IK")
		virtual FLmFootOffset SetFootOffsets(FName EnableFootIKCurve, FName IKFootBone, FName RootBone, FLmFootOffset params);
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Anim Instance|Foot IK")
		virtual void UpdatePelvisIKOffset(FVector FootOffset_L_Target, FVector FootOffset_R_Target);
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Anim Instance|Foot IK")
		virtual FLmFootLock UpdateFootLock(FName Enable_FootIK_Curve, FName FootLockCurve, FName IKFootBone, FLmFootLock lastValue);
	//Rotation
	UFUNCTION(BlueprintPure, Category = "Locomotion|Rotation")
		virtual ELmMovementDirection CalculateMovementDirection();
	UFUNCTION(BlueprintPure, Category = "Locomotion|Rotation")
		virtual ELmMovementDirection CalculateQuadrant(ELmMovementDirection Current, float FR_Threshold, float FL_Threshold, float BR_Threshold, float BL_Threshold, float buffer, float angle);
	UFUNCTION(BlueprintPure, Category = "Locomotion|Rotation")
		virtual bool AngleInRange(float angle, float minAngle, float maxAngle, float buffer, bool IncreaseBuffer);
	UFUNCTION(BlueprintPure, Category = "Locomotion|Rotation")
		virtual FLmVelocityBlend InterpVelocityBlend(FLmVelocityBlend current, FLmVelocityBlend target, float interpSpeed, float deltaTime);
	UFUNCTION(BlueprintPure, Category = "Locomotion|Rotation")
		virtual FLmLeanAmount InterpLeanAmount(FLmLeanAmount& current, FLmLeanAmount& target, float interpSpeed, float deltaTime);
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Notify Events")
		void Response_AnimNotifyPivot();
	//Debug
	UFUNCTION(BlueprintPure, Category = "Locomotion|Debug")
		virtual TEnumAsByte<EDrawDebugTrace::Type> GetDebugTraceType(TEnumAsByte<EDrawDebugTrace::Type> ShowTraceType);

	//Custom Events
	bool bDynamicTransitionGate_IsOpen = true;
	FTimerHandle AnimNotifyPivotHandle;
	FTimerHandle DynamicTransitionHandle;
	FTimerHandle JumpedHandle;

	//Play Additive Transition Animation
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Custom Events")
		void PlayTransition(FLmDynamicMontageParams params);
	//Play Dynamic Additive Transition Animation
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Custom Events")
		void PlayDynamicTransition(float ReTriggerDelay, FLmDynamicMontageParams Parameters);
	//Interface Events
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Interface Calls")
		void Jumped();
	virtual void Jumped_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Interface Calls")
		void SetGroundedEntryState(ELmGroundedEntryState NewState);
	virtual void SetGroundedEntryState_Implementation(ELmGroundedEntryState NewState) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Interface Calls")
		void SetOverlayOverrideState(int NewState);
	virtual void SetOverlayOverrideState_Implementation(int NewState) override;

private:
	bool bShouldMove_Last;
};
