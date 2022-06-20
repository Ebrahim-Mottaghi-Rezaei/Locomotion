#pragma once

#include "CoreMinimal.h"
#include "ALSEnums.generated.h"

UENUM(BlueprintType)
enum class  EALSGait :uint8 {
	ALS_Walking = 0 UMETA(DisplayName = "Walking"),
	ALS_Running = 1 UMETA(DisplayName = "Running"),
	ALS_Sprinting = 2 UMETA(DisplayName = "Sprinting")
};

UENUM(BlueprintType)
enum class EALSMovementAction :uint8 {
	ALS_None UMETA(DisplayName = "None"),
	ALS_LowMantle UMETA(DisplayName = "Low Mantle"),
	ALS_HighMantle  UMETA(DisplayName = "High Mantle"),
	ALS_Rolling UMETA(DisplayName = "Rolling"),
	ALS_GettingUp  UMETA(DisplayName = "Getting Up")
};

UENUM(BlueprintType)
enum class EALSMovementState :uint8 {
	ALS_None UMETA(DisplayName = "None"),
	ALS_Grounded UMETA(DisplayName = "Grounded"),
	ALS_InAir  UMETA(DisplayName = "In Air"),
	ALS_Mantling UMETA(DisplayName = "Mantling"),
	ALS_Ragdoll  UMETA(DisplayName = "Ragdoll")
};

UENUM(BlueprintType)
enum class EALSOverlayState :uint8 {
	ALS_Default UMETA(DisplayName = "Default"),
	ALS_Masculine UMETA(DisplayName = "Masculine"),
	ALS_Feminine  UMETA(DisplayName = "Feminine"),
	ALS_Injured UMETA(DisplayName = "Injured"),
	ALS_HandsTied  UMETA(DisplayName = "HandsTied"),
	ALS_Rifle  UMETA(DisplayName = "Rifle"),
	ALS_Pistol1H  UMETA(DisplayName = "Pistol 1 Hand"),
	ALS_Pistol2H  UMETA(DisplayName = "Pistol 2 Hands"),
	ALS_Bow  UMETA(DisplayName = "Bow"),
	ALS_Torch  UMETA(DisplayName = "Torch"),
	ALS_Binoculars  UMETA(DisplayName = "Binoculars"),
	ALS_Box  UMETA(DisplayName = "Carrying Box"),
	ALS_Barrel  UMETA(DisplayName = "Carrying Barrel")
};

UENUM(BlueprintType)
enum class EALSRotationMode :uint8 {
	ALS_VelocityDirection UMETA(DisplayName = "Velocity Direction"),
	ALS_LookingDirection UMETA(DisplayName = "Looking Direction"),
	ALS_Aiming  UMETA(DisplayName = "Aiming")
};

UENUM(BlueprintType)
enum class EALSStance :uint8 {
	ALS_Standing UMETA(DisplayName = "Standing"),
	ALS_Crouching UMETA(DisplayName = "Crouching")
};

UENUM(BlueprintType)
enum class EALSViewMode :uint8 {
	ALS_TPS UMETA(DisplayName = "Third Person"),
	ALS_FPS UMETA(DisplayName = "First Person")
};

UENUM(BlueprintType)
enum class EALSAnimFeaturesExample :uint8 {
	ALS_StrideBlending UMETA(DisplayName = "Stride Blending"),
	ALS_AdditiveLeaning UMETA(DisplayName = "Additive Leaningn"),
	ALS_SprintImpulse UMETA(DisplayName = "Sprint Impulse")
};

UENUM(BlueprintType)
enum class EALSFootStepType :uint8 {
	ALS_Step UMETA(DisplayName = "Stride Blending"),
	ALS_WalkRun UMETA(DisplayName = "Walk|Run"),
	ALS_Jump UMETA(DisplayName = "Jump"),
	ALS_Land UMETA(DisplayName = "Land")
};

UENUM(BlueprintType)
enum class EALSGroundedEntryState :uint8 {
	ALS_None UMETA(DisplayName = "None"),
	ALS_Roll UMETA(DisplayName = "Roll")
};

UENUM(BlueprintType)
enum class EALSHipsDirection :uint8 {
	ALS_F UMETA(DisplayName = "Front"),
	ALS_B UMETA(DisplayName = "Back"),
	ALS_RF UMETA(DisplayName = "Right Front"),
	ALS_RB UMETA(DisplayName = "Right Back"),
	ALS_LF UMETA(DisplayName = "Left Front"),
	ALS_LB UMETA(DisplayName = "Left Back")
};

UENUM(BlueprintType)
enum class EALSMantleType :uint8 {
	ALS_HighMantle UMETA(DisplayName = "High Mantle"),
	ALS_LowMantle UMETA(DisplayName = "Low Mantle"),
	ALS_FallingCatch UMETA(DisplayName = "Falling Catch")
};

UENUM(BlueprintType)
enum class EALSMovementDirection :uint8 {
	ALS_Forward UMETA(DisplayName = "Forward"),
	ALS_Backward UMETA(DisplayName = "Backward"),
	ALS_Right UMETA(DisplayName = "Right"),
	ALS_Left UMETA(DisplayName = "Left")
};

UENUM(BlueprintType)
enum class EALSInputProcessingMode :uint8 {
	ALS_PressAndHold UMETA(DisplayName = "Press And Hold"),
	ALS_DoublePress UMETA(DisplayName = "Double Press")
};

UENUM(BlueprintType)
enum class EALSButtonPressType :uint8 {
	ALS_Tapping UMETA(DisplayName = "Tapping"),
	ALS_Holding UMETA(DisplayName = "Holding"),
	ALS_Released UMETA(DisplayName = "Released"),
};

UENUM(BlueprintType)
enum class EALSMannequinMeshType :uint8 {
	ALS_Default UMETA(DisplayName = "ALS Default"),
	ALS_Mannequin UMETA(DisplayName = "UE Mannequin")
};

