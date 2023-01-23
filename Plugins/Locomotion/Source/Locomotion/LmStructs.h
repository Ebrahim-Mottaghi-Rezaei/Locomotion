#pragma once

#include "CoreMinimal.h"
#include "LmEnums.h"
#include "Engine/DataTable.h"
#include "Engine/EngineTypes.h"
#include <Animation/AnimSequenceBase.h>
#include <Curves/CurveVector.h>
#include "LmStructs.generated.h"

class UPrimitiveComponent;
class UCurveVector;
class UCurveFloat;
class UAnimMontage;
class UAnimSequenceBase;
class ACharacter;

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmComponentAndTransform {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Component Transform")
		UPrimitiveComponent* Component;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Component Transform")
		FTransform Transform;

	FLmComponentAndTransform();
	FLmComponentAndTransform(FTransform transform, UPrimitiveComponent* component);

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmCameraSettings {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Setting")
		float TargetArmLength;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Setting")
		FVector SocketOffset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Setting")
		float LagSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Setting")
		float RotationLagSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Setting")
		bool DoCollisionTest;

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmCameraSettingsGait {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Gait")
		FLmCameraSettings Walking;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Gait")
		FLmCameraSettings Running;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Gait")
		FLmCameraSettings Sprinting;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Gait")
		FLmCameraSettings Crouching;

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmCameraSettingsState {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera State")
		FLmCameraSettingsGait VelocityDirection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera State")
		FLmCameraSettingsGait LookingDirection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera State")
		FLmCameraSettingsGait Aiming;

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmDynamicMontageParams {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|DataTypes")
		UAnimSequenceBase* Animation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dynamic Montage Params")
		float BlendInTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dynamic Montage Params")
		float BlendOutTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dynamic Montage Params")
		float PlayRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dynamic Montage Params")
		float StartTime;

	FLmDynamicMontageParams();
	FLmDynamicMontageParams(UAnimSequenceBase* animation, float blendInTime = 0.2f, float blendOutTime = 0.2f, float playRate = 1.5f, float = 0.2f);

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmLeanAmount {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lean Amount")
		float LeftRight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lean Amount")
		float FrontBack;


	FLmLeanAmount();
	FLmLeanAmount(float FB, float LR);

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmMantleAsset {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Asset")
		UAnimMontage* AnimMontage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Asset")
		UCurveVector* PositionCorrectionCurve;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Asset")
		FVector StartingOffset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Asset")
		float LowHeight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Asset")
		float LowPlayRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Asset")
		float LowStartPosition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Asset")
		float HighHeight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Asset")
		float HighPlayRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Asset")
		float HighStartPosition;

	FLmMantleAsset();
	FLmMantleAsset(UAnimMontage* AnimMontage, UCurveVector* PositionCorrectionCurve, FVector StartingOffset, float LowHeight, float LowPlayRate, float LowStartPosition, float HighHeight, float HighPlayRate, float HighStartPosition);

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmMantleParams {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Params")
		UAnimMontage* AnimMontage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Params")
		UCurveVector* PositionCorrectionCurve;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Params")
		float StartingPosition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Params")
		float PlayRate = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Params")
		FVector StartingOffset;

	FLmMantleParams();
	FLmMantleParams(UAnimMontage* animMontage, UCurveVector* positionCorrectionCurve, float startingPosition, FVector startingOffset, float playRate = 1.0f);

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmMantleTraceSettings {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Trace Settings")
		float MinLedgeHeight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Trace Settings")
		float MaxLedgeHeight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Trace Settings")
		float ReachDistance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Trace Settings")
		float ForwardTraceRadius;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mantle Trace Settings")
		float DownwardTraceRadius;

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmMovementSettings {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement Settings")
		float WalkSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement Settings")
		float RunSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement Settings")
		float SprintSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement Settings")
		UCurveVector* MovementCurve;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement Settings")
		UCurveFloat* RotationRateCurve;

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmMovementSettingsStance {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement Stance")
		FLmMovementSettings Standing;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement Stance")
		FLmMovementSettings Crouching;

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmMovementSettingsState :public FTableRowBase {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement State")
		FLmMovementSettingsStance VelocityDirection;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement State")
		FLmMovementSettingsStance LookingDirection;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement State")
		FLmMovementSettingsStance Aiming;

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmRotateInPlaceAsset {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rotate InPlace Asset")
		UAnimSequenceBase* Animation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rotate InPlace")
		FName SlotName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rotate InPlace")
		float SlowTurnRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rotate InPlace")
		float FastTurnRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rotate InPlace")
		float SlowPlayRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rotate InPlace")
		float FastPlayRate;

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmTurnInPlaceAsset {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turn InPlace")
		UAnimSequenceBase* Animation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turn InPlace")
		FName SlotName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turn InPlace")
		float AnimatedAngle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turn InPlace")
		float PlayRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turn InPlace")
		bool ScaleTurnAngle;

	FLmTurnInPlaceAsset();

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmVelocityBlend {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Velocity Blend")
		float F;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Velocity Blend")
		float B;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Velocity Blend")
		float L;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Velocity Blend")
		float R;

	FLmVelocityBlend();
	FLmVelocityBlend(float f, float b, float l, float r);

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmCurrentState {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Current State")
		TEnumAsByte<EMovementMode> PawnMovementMode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Current State")
		ELmMovementState MovementState;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Current State")
		ELmMovementState PrevMovementState;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Current State")
		ELmMovementAction MovementAction;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Current State")
		ELmRotationMode RotationMode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Current State")
		ELmGait ActualGait;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Current State")
		ELmStance ActualStance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Current State")
		ELmViewMode ViewMode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Current State")
		ELmOverlayState OverlayState;

	FLmCurrentState();

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmEssentialValues {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Values")
		FVector Velocity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Values")
		FVector Acceleration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Values")
		FVector MovementInput;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Values")
		bool bIsMoving;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Values")
		bool bHasMovementInput;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Values")
		float Speed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Values")
		float MovementInputAmount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Values")
		FRotator AimingRotation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Values")
		float AimYawRate;

	FLmEssentialValues();
	FLmEssentialValues(FVector velocity, FVector acceleration, FVector movementInput, bool isMoving, bool hasMovementInput, float speed, float movementInputAmount, FRotator aimingRotation, float aimYawRate);

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmDebugInfo {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug Info")
		ACharacter* DebugFocusCharacter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug Info")
		bool bDebugView;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug Info")
		bool bShowHUD;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug Info")
		bool bShowTraces;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug Info")
		bool bShowDebugShapes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug Info")
		bool bShowLayerColors;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug Info")
		bool bSlowMotion;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug Info")
		bool bShowCharacterInfo;

	FLmDebugInfo();
	FLmDebugInfo(ACharacter* FocusedDebugCharacter, bool DebugView, bool ShowHUD, bool ShowTraces, bool ShowDebugShapes, bool ShowLayerColors, bool SlowMotion, bool ShowCharacterInfo);

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmCameraParameters {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Parameters")
		float TP_FOV;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Parameters")
		float FP_FOV;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Parameters")
		bool bRightShoulder;
	FLmCameraParameters();
	FLmCameraParameters(float tP_FOV, float fp_FOV, bool rightShoulder);

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmTraceParams {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Trace Parameters")
		TEnumAsByte<ETraceTypeQuery> TraceChannel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Trace Parameters")
		FVector TraceOrigin;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Trace Parameters")
		float TraceRadius;

	FLmTraceParams();
	FLmTraceParams(TEnumAsByte<ETraceTypeQuery> traceChannel, FVector traceOrigin, float traceRadius);

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmCameraResult {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Result")
		FVector Location;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Result")
		FRotator Rotation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Result")
		float FOV;

	FLmCameraResult();
	FLmCameraResult(FVector location, FRotator rotation, float fov);

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmControlVectors {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Control Vectors")
		FVector Forward;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Control Vectors")
		FVector Right;

	FLmControlVectors();
	FLmControlVectors(FVector forward, FVector right);

	virtual FString ToString(bool bPrintToLog = false);
};

struct FLmHitResult {
	bool bHit;
	FHitResult SweepHitResult;

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmFootLock {

	GENERATED_BODY()

		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Foot IK")
		float Alpha;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Foot IK")
		FVector Location;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Foot IK")
		FRotator Rotation;

	FLmFootLock();
	FLmFootLock(FVector location, FRotator rotation, float alpha);

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct FLmFootOffset {
	GENERATED_BODY()
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Foot Offset")
		FVector LocationTarget;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Foot Offset")
		FVector LocationOffset;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Foot Offset")
		FRotator RotationOffset;

	FLmFootOffset();
	FLmFootOffset(FVector target_location, FVector offset_location, FRotator offset_rotation);

	virtual FString ToString(bool bPrintToLog = false);
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct LOCOMOTION_API FLmRoleSkinColors : public FTableRowBase {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ELmOverlayState Role;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool UseGloves = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool UseShoes = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = 0, ClampMax = 2))
		uint8 ShirtType = 3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = 0, ClampMax = 2))
		uint8 PantsType = 2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FLinearColor Skin = FColor::FromHex("E5B191FF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition = "ShirtType > 0", EditConditionHides))
		FLinearColor Shirt = FColor::FromHex("668F80FF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition = "UseGloves", EditConditionHides))
		FLinearColor Gloves = FColor::FromHex("A0AF84FF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FLinearColor Pants = FColor::FromHex("4A6670FF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition = "UseShoes", EditConditionHides))
		FLinearColor Shoes = FColor::FromHex("C3B59FFF");
};

USTRUCT(BlueprintType, Category = "Locomotion|DataTypes")
struct LOCOMOTION_API FLmHoldingInstance : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText Description;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		ELmUseWhichHand UsingHands;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FVector Offset;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		ELmOverlayState OverlayState;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		TSubclassOf<AActor> Instance;
};