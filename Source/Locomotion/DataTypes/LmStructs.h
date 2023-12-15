#pragma once

#include <Animation/AnimSequenceBase.h>
#include <Curves/CurveVector.h>
#include "CoreMinimal.h"
#include "LmEnums.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveVector.h"
#include "Engine/DataTable.h"
#include "Engine/EngineTypes.h"
#include "Engine/HitResult.h"
#include "GameFramework/Character.h"
#include "LmStructs.generated.h"

USTRUCT( Category = "Locomotion|DataTypes" )
struct FLmStruct {
	GENERATED_BODY()
	virtual ~FLmStruct();

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmComponentAndTransform : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Component Transform" )
	UPrimitiveComponent* Component;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Component Transform" )
	FTransform Transform;

	FLmComponentAndTransform();

	FLmComponentAndTransform(const FTransform& transform, UPrimitiveComponent* component);

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmCameraSettings : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera Setting" )
	float TargetArmLength = 100.f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera Setting" )
	FVector SocketOffset = FVector::ZeroVector;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera Setting" )
	float LagSpeed = 1.0f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera Setting" )
	float RotationLagSpeed = 1.0;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera Setting" )
	bool DoCollisionTest = true;

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmCameraSettingsGait : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera Gait" )
	FLmCameraSettings Walking;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera Gait" )
	FLmCameraSettings Running;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera Gait" )
	FLmCameraSettings Sprinting;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera Gait" )
	FLmCameraSettings Crouching;

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmCameraSettingsState : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera State" )
	FLmCameraSettingsGait VelocityDirection;

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera State" )
	FLmCameraSettingsGait LookingDirection;

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera State" )
	FLmCameraSettingsGait Aiming;

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmDynamicMontageParams : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Locomotion|DataTypes" )
	UAnimSequenceBase* Animation;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Dynamic Montage Params" )
	float BlendInTime;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Dynamic Montage Params" )
	float BlendOutTime;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Dynamic Montage Params" )
	float PlayRate;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Dynamic Montage Params" )
	float StartTime;

	FLmDynamicMontageParams();

	FLmDynamicMontageParams(UAnimSequenceBase* animation, float blendInTime = 0.2f, float blendOutTime = 0.2f, float playRate = 1.5f, float = 0.2f);

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmLeanAmount : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Lean Amount" )
	float LeftRight;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Lean Amount" )
	float FrontBack;

	FLmLeanAmount();

	FLmLeanAmount(float FB, float LR);

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmMantleAsset : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Asset" )
	UAnimMontage* AnimMontage = nullptr;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Asset" )
	UCurveVector* PositionCorrectionCurve = nullptr;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Asset" )
	FVector StartingOffset = FVector::ZeroVector;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Asset" )
	float LowHeight = 0.0f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Asset" )
	float LowPlayRate = 1.0f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Asset" )
	float LowStartPosition = 0.0f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Asset" )
	float HighHeight = 0.0f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Asset" )
	float HighPlayRate = 1.0f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Asset" )
	float HighStartPosition = 0.0f;

	FLmMantleAsset();

	FLmMantleAsset(UAnimMontage*  AnimMontage,
	               UCurveVector*  PositionCorrectionCurve,
	               const FVector& StartingOffset,
	               float          LowHeight,
	               float          LowPlayRate,
	               float          LowStartPosition,
	               float          HighHeight,
	               float          HighPlayRate,
	               float          HighStartPosition);

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmMantleParams : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Params" )
	UAnimMontage* AnimMontage = nullptr;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Params" )
	UCurveVector* PositionCorrectionCurve = nullptr;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Params" )
	float StartingPosition = 0.0f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Params" )
	float PlayRate = 1.0f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Params" )
	FVector StartingOffset = FVector::ZeroVector;

	FLmMantleParams();

	FLmMantleParams(UAnimMontage* animMontage, UCurveVector* positionCorrectionCurve, float startingPosition, const FVector& startingOffset, float playRate = 1.0f);

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmMantleTraceSettings : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Trace Settings" )
	float MinLedgeHeight = 0.0f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Trace Settings" )
	float MaxLedgeHeight = 0.0f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Trace Settings" )
	float ReachDistance = 0.0f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Trace Settings" )
	float ForwardTraceRadius = 0.0f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Mantle Trace Settings" )
	float DownwardTraceRadius = 0.0f;

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmMovementSettings : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Movement Settings" )
	float WalkSpeed = 0.0f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Movement Settings" )
	float RunSpeed = 0.0f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Movement Settings" )
	float SprintSpeed = 0.0f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Movement Settings" )
	UCurveVector* MovementCurve = nullptr;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Movement Settings" )
	UCurveFloat* RotationRateCurve = nullptr;

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmMovementSettingsStance : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Movement Stance" )
	FLmMovementSettings Standing;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Movement Stance" )
	FLmMovementSettings Crouching;

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmMovementSettingsState : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Movement State" )
	FLmMovementSettingsStance VelocityDirection;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Movement State" )
	FLmMovementSettingsStance LookingDirection;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Movement State" )
	FLmMovementSettingsStance Aiming;

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmRotateInPlaceAsset : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Rotate InPlace Asset" )
	UAnimSequenceBase* Animation = nullptr;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Rotate InPlace" )
	FName SlotName = NAME_None;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Rotate InPlace" )
	float SlowTurnRate = 0.f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Rotate InPlace" )
	float FastTurnRate = 0.f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Rotate InPlace" )
	float SlowPlayRate = 0.f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Rotate InPlace" )
	float FastPlayRate = 0.f;

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmTurnInPlaceAsset : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Turn InPlace" )
	UAnimSequenceBase* Animation;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Turn InPlace" )
	FName SlotName;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Turn InPlace" )
	float AnimatedAngle;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Turn InPlace" )
	float PlayRate;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Turn InPlace" )
	bool ScaleTurnAngle;

	FLmTurnInPlaceAsset();

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmVelocityBlend : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Velocity Blend" )
	float F;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Velocity Blend" )
	float B;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Velocity Blend" )
	float L;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Velocity Blend" )
	float R;

	FLmVelocityBlend();

	FLmVelocityBlend(float f, float b, float l, float r);

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmCurrentState : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Current State" )
	TEnumAsByte<EMovementMode> PawnMovementMode = MOVE_Walking;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Current State" )
	ELmMovementState MovementState = ELmMovementState::Lm_Grounded;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Current State" )
	ELmMovementState PrevMovementState = ELmMovementState::Lm_None;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Current State" )
	ELmMovementAction MovementAction = ELmMovementAction::Lm_None;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Current State" )
	ELmRotationMode RotationMode = ELmRotationMode::Lm_LookingDirection;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Current State" )
	ELmGait ActualGait = ELmGait::Lm_Walking;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Current State" )
	ELmStance ActualStance = ELmStance::Lm_Standing;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Current State" )
	ELmViewMode ViewMode = ELmViewMode::Lm_TPS;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Current State" )
	ELmOverlayState OverlayState = ELmOverlayState::Lm_Default;

	FLmCurrentState();

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmEssentialValues : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Essential Values" )
	FVector Velocity = FVector::ZeroVector;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Essential Values" )
	FVector Acceleration = FVector::ZeroVector;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Essential Values" )
	FVector MovementInput = FVector::ZeroVector;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Essential Values" )
	bool bIsMoving = false;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Essential Values" )
	bool bHasMovementInput = false;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Essential Values" )
	float Speed = 0.f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Essential Values" )
	float MovementInputAmount = 0.0f;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Essential Values" )
	FRotator AimingRotation = FRotator::ZeroRotator;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Essential Values" )
	float AimYawRate = 0.f;

	FLmEssentialValues();

	FLmEssentialValues(const FVector&  velocity,
	                   const FVector&  acceleration,
	                   const FVector&  movementInput,
	                   bool            isMoving,
	                   bool            hasMovementInput,
	                   float           speed,
	                   float           movementInputAmount,
	                   const FRotator& aimingRotation,
	                   float           aimYawRate);

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmDebugInfo : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Debug Info" )
	ACharacter* DebugFocusCharacter = nullptr;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Debug Info" )
	bool bDebugView = false;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Debug Info" )
	bool bShowHUD = false;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Debug Info" )
	bool bShowTraces = false;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Debug Info" )
	bool bShowDebugShapes = false;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Debug Info" )
	bool bShowLayerColors = false;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Debug Info" )
	bool bSlowMotion = false;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Debug Info" )
	bool bShowCharacterInfo = false;

	FLmDebugInfo();

	FLmDebugInfo(ACharacter* FocusedDebugCharacter, bool DebugView, bool ShowHUD, bool ShowTraces, bool ShowDebugShapes, bool ShowLayerColors, bool SlowMotion, bool ShowCharacterInfo);

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmCameraParameters : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera Parameters" )
	float TP_FOV;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera Parameters" )
	float FP_FOV;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera Parameters" )
	bool bRightShoulder;

	FLmCameraParameters();

	FLmCameraParameters(float tP_FOV, float fp_FOV, bool rightShoulder);

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmTraceParams : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Trace Parameters" )
	TEnumAsByte<ETraceTypeQuery> TraceChannel;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Trace Parameters" )
	FVector TraceOrigin;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Trace Parameters" )
	float TraceRadius;

	FLmTraceParams();

	FLmTraceParams(TEnumAsByte<ETraceTypeQuery> traceChannel, const FVector& traceOrigin, float traceRadius);

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmCameraResult : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera Result" )
	FVector Location;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera Result" )
	FRotator Rotation;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Camera Result" )
	float FOV;

	FLmCameraResult();

	FLmCameraResult(const FVector& location, const FRotator& rotation, float fov);

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmControlVectors : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadOnly , VisibleAnywhere , Category = "Control Vectors" )
	FVector Forward = FVector::ZeroVector;
	UPROPERTY( BlueprintReadOnly , VisibleAnywhere , Category = "Control Vectors" )
	FVector Right = FVector::ZeroVector;

	FLmControlVectors();

	FLmControlVectors(const FVector& forward, const FVector& right);

	virtual FString ToString(bool bPrintToLog = false) override;
};

struct FLmHitResult {
	virtual ~FLmHitResult();

	bool       bHit;
	FHitResult HitResult;

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmFootLock : public FLmStruct {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadOnly , VisibleAnywhere , Category = "Foot IK" )
	float Alpha = 0.f;

	UPROPERTY( BlueprintReadOnly , VisibleAnywhere , Category = "Foot IK" )
	FVector Location = FVector::ZeroVector;

	UPROPERTY( BlueprintReadOnly , VisibleAnywhere , Category = "Foot IK" )
	FRotator Rotation = FRotator::ZeroRotator;

	FLmFootLock();

	FLmFootLock(const FVector& location, const FRotator& rotation, float alpha);

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmFootOffset : public FLmStruct {
	GENERATED_BODY()
	UPROPERTY( BlueprintReadOnly , VisibleAnywhere , Category = "Foot Offset" )
	FVector LocationTarget = FVector::ZeroVector;

	UPROPERTY( BlueprintReadOnly , VisibleAnywhere , Category = "Foot Offset" )
	FVector LocationOffset = FVector::ZeroVector;

	UPROPERTY( BlueprintReadOnly , VisibleAnywhere , Category = "Foot Offset" )
	FRotator RotationOffset = FRotator::ZeroRotator;

	FLmFootOffset();

	FLmFootOffset(const FVector& target_location, const FVector& offset_location, const FRotator& offset_rotation);

	virtual FString ToString(bool bPrintToLog = false) override;
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct LOCOMOTION_API FLmRoleSkinColors : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Information" )
	ELmOverlayState Role = ELmOverlayState::Lm_Default;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Information" )
	FText Description;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Styling" )
	bool UseGloves = true;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Styling" )
	bool UseShoes = true;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , meta = (ClampMin = 0 , ClampMax = 3) , Category = "Styling" )
	uint8 ShirtType = 3;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , meta = (ClampMin = 0 , ClampMax = 2) , Category = "Styling" )
	uint8 PantsType = 2;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Styling" )
	FLinearColor Skin = FColor::FromHex( "E5B191FF" );
	UPROPERTY( BlueprintReadWrite , EditAnywhere , meta = (EditCondition = "ShirtType > 0") , Category = "Styling" )
	FLinearColor Shirt = FColor::FromHex( "668F80FF" );
	UPROPERTY( BlueprintReadWrite , EditAnywhere , meta = (EditCondition = "UseGloves") , Category = "Styling" )
	FLinearColor Gloves = FColor::FromHex( "A0AF84FF" );
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Styling" )
	FLinearColor Pants = FColor::FromHex( "4A6670FF" );
	UPROPERTY( BlueprintReadWrite , EditAnywhere , meta = (EditCondition = "UseShoes") , Category = "Styling" )
	FLinearColor Shoes = FColor::FromHex( "C3B59FFF" );
};

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct LOCOMOTION_API FLmHoldingInstance : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Information" )
	FText Name;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Information" )
	FText Description;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Information" )
	ELmUsingHand UsingHands = ELmUsingHand::Lm_RightHand;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Information" )
	FVector Offset = FVector::ZeroVector;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Information" )
	ELmOverlayState OverlayState = ELmOverlayState::Lm_Default;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Information" )
	TSubclassOf<AActor> Instance;
};
