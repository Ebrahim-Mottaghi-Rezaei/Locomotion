#pragma once

#include "CoreMinimal.h"
#include "ALSEnums.h"
#include "Engine/EngineTypes.h"

#include "ALSStructs.generated.h"

class UPrimitiveComponent;
class UCurveVector;
class UAnimMontage;
class UAnimSequenceBase;
class ACharacter;

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSComponentAndTransform {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UPrimitiveComponent* Component;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FTransform Transform;

	FALSComponentAndTransform();
	FALSComponentAndTransform(FTransform transform, UPrimitiveComponent* component);
};

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSCameraSettings {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TargetArmLength;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector SocketOffset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float LagSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float RotationLagSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool DoCollisionTest;
};

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSCameraSettingsGait {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FALSCameraSettings Walking;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FALSCameraSettings Running;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FALSCameraSettings Sprinting;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FALSCameraSettings Crouching;
};


USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSCameraSettingsState {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FALSCameraSettingsGait VelocityDirection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FALSCameraSettingsGait LookingDirection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FALSCameraSettingsGait Aiming;
};

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSDynamicMontageParams {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UAnimSequenceBase* Animation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float BlendInTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float BlendOutTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float PlayRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float StartTime;

	FALSDynamicMontageParams();
	FALSDynamicMontageParams(UAnimSequenceBase* animation, float blendInTime, float blendOutTime, float playRate, float startTime);
};

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSLeanAmount {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float FrontBack;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float LeftRight;

	FALSLeanAmount();
	FALSLeanAmount(float FB, float LR);
};

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSMantleAsset {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UAnimMontage* AnimMontage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCurveVector* PositionCorrectionCurve;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector StartingOffset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float LowHeight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float LowPlayRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float LowStartPosition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float HighHeight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float HighPlayRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float HighStartPosition;

	FALSMantleAsset();
	FALSMantleAsset(UAnimMontage* AnimMontage, UCurveVector* PositionCorrectionCurve, FVector StartingOffset, float LowHeight, float LowPlayRate, float LowStartPosition, float HighHeight, float HighPlayRate, float HighStartPosition);
};

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSMantleParams {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UAnimMontage* AnimMontage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCurveVector* PositionCorrectionCurve;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float StartingPosition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float PlayRate = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector StartingOffset;

	FALSMantleParams();
	FALSMantleParams(UAnimMontage* animMontage, UCurveVector* positionCorrectionCurve, float startingPosition, FVector startingOffset, float playRate = 1.0);
};


USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSMantleTraceSettings {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MinLedgeHeight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxLedgeHeight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ReachDistance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ForwardTraceRadius;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float DownwardTraceRadius;
};

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSMovementSettings {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float WalkSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float RunSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float SprintSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCurveVector* MovementCurve;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCurveFloat* RotationRateCurve;
};

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSMovementSettingsStance {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FALSMovementSettings Standing;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FALSMovementSettings Crouching;
};

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSMovementSettingsState {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FALSMovementSettingsStance VelocityDirection;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FALSMovementSettingsStance LookingDirection;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FALSMovementSettingsStance Aiming;
};

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSRotateInPlaceAsset {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UAnimSequenceBase* Animation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName SlotName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float SlowTurnRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float FastTurnRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float SlowPlayRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float FastPlayRate;
};

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSTurnInPlaceAsset {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UAnimSequenceBase* Animation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName SlotName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AnimatedAngle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float PlayRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool ScaleTurnAngle;
};

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSVelocityBlend {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float F;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float B;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float L;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float R;

	FALSVelocityBlend();
	FALSVelocityBlend(float f, float b, float l, float r);

};

//Animation Modifiers Structures.
USTRUCT(BlueprintType, Category = "C++ ALS|Animation Modifiers")
struct FAnimCurveCreationData {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int FrameNumber;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float CurveValue;
};

USTRUCT(BlueprintType, Category = "C++ ALS|Animation Modifiers")
struct FALSAnimCurveCreationParams {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName CurveName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool KeyEachFrame;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FAnimCurveCreationData> Keys;
};

USTRUCT(BlueprintType, Category = "C++ ALS|Character Information")
struct FALSCurrentState {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<EMovementMode> PawnMovementMode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EALSMovementState MovementState;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EALSMovementState PrevMovementState;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EALSMovementAction MovementAction;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EALSRotationMode RotationMode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EALSGait ActualGait;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EALSStance ActualStance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EALSViewMode ViewMode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EALSOverlayState OverlayState;

	FALSCurrentState();
};

USTRUCT(BlueprintType, Category = "C++ ALS|Character Information")
struct FALSEssentialValues {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector Velocity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector Acceleration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector MovementInput;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bIsMoving;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bHasMovementInput;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Speed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MovementInputAmount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FRotator AimingRotation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AimYawRate;
};

USTRUCT(BlueprintType, Category = "C++ ALS|Debug")
struct FDebugInfo {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ACharacter* DebugFocusCharacter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bDebugView;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bShowHUD;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bShowTraces;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bShowDebugShapes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bShowLayerColors;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bSlomo;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bShowCharacterInfo;

	FDebugInfo() {
		DebugFocusCharacter = nullptr;
	}
};

USTRUCT(BlueprintType, Category = "C++ ALS|Camera System")
struct FALSCameraParameters {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TP_FOV;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float FP_FOV;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bRightShoulder;
	FALSCameraParameters();
};

USTRUCT(BlueprintType, Category = "C++ ALS|Camera System")
struct FALSTraceParams {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<ETraceTypeQuery> TraceChannel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector TraceOrigin;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TraceRadius;

	FALSTraceParams();
};

USTRUCT(BlueprintType, Category = "C++ ALS|Camera System")
struct FALSCameraBehaviourResult {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector Location;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FRotator Rotation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float FOV;

	FALSCameraBehaviourResult();

	FALSCameraBehaviourResult(FVector location, FRotator rotation, float fov);
};

//Function Return Value Types
struct FALSControlVectors {
	FVector Forward;
	FVector Right;
};

struct FALSHitResult {
	bool bHit;
	FHitResult SweepHitResult;
};