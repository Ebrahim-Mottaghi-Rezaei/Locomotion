#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimSequenceBase.h"
#include "ALSStructs.generated.h"

class UPrimitiveComponent;
class UCurveVector;
class UAnimMontage;
class UAnimSequenceBase;

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSComponentAndTransform {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UPrimitiveComponent* Component;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FTransform Transform;

	FALSComponentAndTransform() {
		Component = nullptr;
		Transform = FTransform();
	}
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
};

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSLeanAmount {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float FrontBack;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float LeftRight;
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
};

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSMantleParams {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UAnimMontage* AnimMontage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCurveVector* PositionCorrectionCurve;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector StartingPosition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float PlayRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float StartingOffset;
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
		UCurveVector* RotationRateCurve;
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
		float ScaleTurnAngle;
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
};

///Animation Modifiers Structures.
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