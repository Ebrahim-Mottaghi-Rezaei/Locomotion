#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../../Data/ALSEnums.h"
#include "../../Data/ALSStructs.h"
#include "../Interfaces/ALSAnimationInterface.h"
#include <CALSv4/Core/Player/ALSCharacter.h>

#include "TimerManager.h"

#include "ALSAnimInstance.generated.h"

UCLASS(Transient, Blueprintable, BlueprintType, hideCategories = (AnimInstance))
class CALSV4_API UALSAnimInstance : public UAnimInstance, public IALSAnimationInterface {
	GENERATED_BODY()
public:
	UALSAnimInstance();
protected:
#pragma region Variables
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		AALSBaseCharacter* Character;
	float DeltaTimeX;
	//Character Information
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		FRotator AimingRotation;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		FVector Velocity;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		FVector RelativeVelocityDirection;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		FVector Acceleration;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		FVector MovementInput;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		bool bIsMoving;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		bool bHasMovementInput;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		float Speed;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		float MovementInputAmount;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		float AimYawRate;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		float ZoomAmount;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		EALSMovementState MovementState;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		EALSMovementState PrevMovementState;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		EALSMovementAction MovementAction;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		EALSRotationMode RotationMode;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		EALSGait Gait;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		EALSStance Stance;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		EALSViewMode ViewMode;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Character Information")
		EALSOverlayState OverlayState;
	//Anim Graph - Grounded State
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		EALSGroundedEntryState GroundedEntryState;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		EALSMovementDirection MovementDirection;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		EALSHipsDirection TrackedHipsDirection;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		FVector RelativeAccelerationAmount;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		bool bShouldMove;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		bool bRotateL;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		bool bRotateR;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		bool bPivot;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		float RotateRate;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		float RotationScale;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		float DiagonalScaleAmount;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		float WalkRunBlend;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		float StandingPlayRate;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		float CrouchingPlayRate;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		float StrideBlend;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		FALSVelocityBlend VelocityBlend;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		FALSLeanAmount LeanAmount;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		float FYaw;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		float BYaw;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		float RYaw;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Grounded State")
		float LYaw;
	//Anim Graph - In Air
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - In Air")
		bool bJumped;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - In Air")
		float JumpPlayRate;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - In Air")
		float FallSpeed;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - In Air")
		float LandPrediction;
	//Anim Graph - Aiming Values
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Aiming Values")
		FRotator SmoothAimingRotation;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Aiming Values")
		FRotator SpineRotation;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Aiming Values")
		FVector2D AimingAngle;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Aiming Values")
		FVector2D SmoothedAimingAngle;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Aiming Values")
		float AimSweepTime;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Aiming Values")
		float InputYawOffsetTime;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Aiming Values")
		float ForwardYawTime;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Aiming Values")
		float LeftYawTime;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Aiming Values")
		float RightYawTime;

	//Rag-doll
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Rag-doll")
		float FlailRate;
	//Anim Graph - LayerBlending
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		int OverlayOverrideState;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float EnableAimOffset;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float BasePose_N;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float BasePose_CLF;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Arm_L;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Arm_L_Add;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Arm_L_LS;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Arm_L_MS;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Arm_R;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Arm_R_Add;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Arm_R_LS;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Arm_R_MS;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Hand_L;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Hand_R;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Legs;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Legs_Add;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Pelvis;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Pelvis_Add;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Spine;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Spine_Add;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Head;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float Head_Add;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float EnableHandIK_L;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - LayerBlending")
		float EnableHandIK_R;

	//Anim Graph - Foot IK
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Foot IK")
		float FootLock_L_Alpha;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Foot IK")
		float FootLock_R_Alpha;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Foot IK")
		FVector FootLock_L_Location;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Foot IK")
		FVector FootLock_R_Location;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Foot IK")
		FRotator FootLock_L_Rotation;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Foot IK")
		FRotator FootLock_R_Rotation;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Foot IK")
		FVector FootOffset_L_Location;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Foot IK")
		FVector FootOffset_R_Location;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Foot IK")
		FRotator FootOffset_L_Rotation;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Foot IK")
		FRotator FootOffset_R_Rotation;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Foot IK")
		FVector PelvisOffset;
	UPROPERTY(BlueprintReadOnly, Category = "ALS AnimInstance|Anim Graph - Foot IK")
		float PelvisAlpha;
	//Turn In Place
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Turn In Place|Setup")
		float TurnCheckMinAngle;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Turn In Place|Setup")
		float Turn180Threshold;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Turn In Place|Setup")
		float AimYawRateLimit;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Turn In Place|Setup")
		float ElapsedDelayTime;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Turn In Place|Setup")
		float MinAngleDelay;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Turn In Place|Setup")
		float MaxAngleDelay;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Turn In Place|Assets")
		FALSTurnInPlaceAsset N_TurnIP_L90;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Turn In Place|Assets")
		FALSTurnInPlaceAsset N_TurnIP_R90;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Turn In Place|Assets")
		FALSTurnInPlaceAsset N_TurnIP_L180;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Turn In Place|Assets")
		FALSTurnInPlaceAsset N_TurnIP_R180;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Turn In Place|Assets")
		FALSTurnInPlaceAsset CLF_TurnIP_L90;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Turn In Place|Assets")
		FALSTurnInPlaceAsset CLF_TurnIP_R90;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Turn In Place|Assets")
		FALSTurnInPlaceAsset CLF_TurnIP_L180;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Turn In Place|Assets")
		FALSTurnInPlaceAsset CLF_TurnIP_R180;
	//Rotate in Place
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Rotate in Place")
		float RotateMinThreshold;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Rotate in Place")
		float RotateMaxThreshold;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Rotate in Place")
		float AimYawRateMinRange;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Rotate in Place")
		float AimYawRateMaxRange;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Rotate in Place")
		float MinPlayRate;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Rotate in Place")
		float MaxPlayRate;
	//Blend curves
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Blend Curves")
		UCurveFloat* DiagonalScaleAmountCurve;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Blend Curves")
		UCurveFloat* StrideBlend_N_Walk;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Blend Curves")
		UCurveFloat* StrideBlend_N_Run;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Blend Curves")
		UCurveFloat* StrideBlend_C_Walk;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Blend Curves")
		UCurveFloat* LandPredictionCurve;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Blend Curves")
		UCurveFloat* LeanInAirCurve;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Blend Curves")
		UCurveVector* YawOffset_FB;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Blend Curves")
		UCurveVector* YawOffset_LR;
	//Config
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Config")
		float AnimatedWalkSpeed;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Config")
		float AnimatedRunSpeed;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Config")
		float AnimatedSprintSpeed;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Config")
		float AnimatedCrouchSpeed;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Config")
		float VelocityBlendInterpSpeed;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Config")
		float GroundedLeanInterpSpeed;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Config")
		float InAirLeanInterpSpeed;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Config")
		float SmoothedAimingRotationInterpSpeed;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Config")
		float InputYawOffsetInterpSpeed;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Config")
		float TriggerPivotSpeedLimit;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Config")
		float FootHeight;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Config")
		float IK_TraceDistanceAboveFoot;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ALS AnimInstance|Config")
		float IK_TraceDistanceBelowFoot;

	//used in code
	TArray<AActor*> IgnoredActors;
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
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Update Values")
		virtual void UpdateCharacterInfo();
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Update Values")
		virtual void UpdateAimingValues();
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Update Values")
		virtual void UpdateLayerValues();
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Update Values")
		virtual void UpdateFootIK();
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Update Values")
		virtual void UpdateMovementValues();
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Update Values")
		virtual void UpdateRotationValues();
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Update Values")
		virtual void UpdateInAirValues();
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Update Values")
		virtual void UpdateRagdollValues();
	//Grounded
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Grounded")
		virtual bool ShouldMoveCheck();
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Grounded")
		virtual bool CanTurnInPlace();
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Grounded")
		virtual bool CanRotateInPlace();
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Grounded")
		virtual bool CanDynamicTransition();
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Grounded")
		virtual bool CanOverlayTransition();
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Grounded")
		virtual void TurnInPlace(FRotator TargetRotation, float PlayRateScale, float StartTime, bool bOverrideCurrent);
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Grounded")
		virtual void TurnInPlaceCheck();
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Grounded")
		virtual void RotateInPlaceCheck();
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Grounded")
		virtual void DynamicTransitionCheck();
	//Movement
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Movement")
		virtual FALSVelocityBlend CalculateVelocityBlend();
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Movement")
		virtual float CalculateDiagonalScaleAmount();
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Movement")
		virtual FVector CalculateRelativeAccelerationAmount();
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Movement")
		virtual float CalculateWalkRunBlend();
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Movement")
		virtual float CalculateStrideBlend();
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Movement")
		virtual float CalculateStandingPlayRate();
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Movement")
		virtual float CalculateCrouchingPlayRate();
	//In Air
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|In Air")
		virtual float CalculateLandPrediction();
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|In Air")
		virtual FALSLeanAmount CalculateInAirLeanAmount();
	//Foot IK
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Foot IK")
		virtual void SetFootOffsets(FName EnableFootIKCurve, FName IKFootBone, FName RootBone, FVector& CurrentLocationTarget, FVector& CurrentLocationOffset, FRotator& CurrentRotationOffset);
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Foot IK")
		virtual void SetPelvisIKOffset(FVector FootOffset_L_Target, FVector FootOffset_R_Target);
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Foot IK")
		virtual void SetFootLocking(FName Enable_FootIK_Curve, FName FootLockCurve, FName IKFootBone, float& CurrentFootLockAlpha, FVector& CurrentFootLockLocation, FRotator& CurrentFootLockRotation);
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Foot IK")
		virtual void SetFootLockOffsets(FVector& LocalLocation, FRotator& LocalRotation);
	//Rotation
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Rotation")
		virtual EALSMovementDirection CalculateMovementDirection();
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Rotation")
		virtual EALSMovementDirection CalculateQuadrant(EALSMovementDirection Current, float FR_Threshold, float FL_Threshold, float BR_Threshold, float BL_Threshold, float buffer, float angle);
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Rotation")
		virtual bool AngleInRange(float angle, float minAngle, float maxAngle, float buffer, bool IncreaseBuffer);
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Rotation")
		virtual FALSVelocityBlend InterpVelocityBlend(FALSVelocityBlend current, FALSVelocityBlend target, float interpSpeed, float deltaTime);
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Rotation")
		virtual FALSLeanAmount InterpLeanAmount(FALSLeanAmount current, FALSLeanAmount target, float interpSpeed, float deltaTime);
	//Debug
	UFUNCTION(BlueprintPure, Category = "ALS AnimInstance|Debug")
		virtual TEnumAsByte<EDrawDebugTrace::Type> GetDebugTraceType(TEnumAsByte<EDrawDebugTrace::Type> ShowTraceType);

	//Custom Events
	bool bDynamicTransitionFlag;
	FTimerHandle DynamicTransitionHandle;
	FTimerDelegate DynamicTransitionDel;
	FTimerHandle JumpedHandle;

	//Play Additive Transition Animation
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Custom Events")
		void PlayTransition(FALSDynamicMontageParams params);
	//Play Dynamic Additive Transition Animation
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Custom Events")
		void PlayDynamicTransition(float ReTriggerDelay, FALSDynamicMontageParams Parameters);
	UFUNCTION()
		void PlayDynamicTransitionDo(FALSDynamicMontageParams Params);
	//Interface Events
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Interface Calls")
		virtual void Jumped_Implementation() override;
	UFUNCTION(BlueprintCallable, Category = "ALS AnimInstance|Interface Calls")
		void JumpedReset();
	virtual void SetGroundedEntryState_Implementation(EALSGroundedEntryState groundedEntryState) override;
	virtual void SetOverlayOverrideState_Implementation(int OverlayOverrideState) override;
};