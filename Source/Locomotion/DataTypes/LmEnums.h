#pragma once

#include "CoreMinimal.h"
#include "LmEnums.generated.h"

UENUM(BlueprintType)
enum class  ELmGait :uint8 {
	Lm_Walking = 0		UMETA(DisplayName = "Walking"),
	Lm_Running = 1		UMETA(DisplayName = "Running"),
	Lm_Sprinting = 2	UMETA(DisplayName = "Sprinting")
};

UENUM(BlueprintType)
enum class ELmMovementAction :uint8 {
	Lm_None				UMETA(DisplayName = "None"),
	Lm_LowMantle		UMETA(DisplayName = "Low Mantle"),
	Lm_HighMantle		UMETA(DisplayName = "High Mantle"),
	Lm_Rolling			UMETA(DisplayName = "Rolling"),
	Lm_GettingUp		UMETA(DisplayName = "Getting Up")
};

UENUM(BlueprintType)
enum class ELmMovementState :uint8 {
	Lm_None				UMETA(DisplayName = "None"),
	Lm_Grounded			UMETA(DisplayName = "Grounded"),
	Lm_InAir			UMETA(DisplayName = "In Air"),
	Lm_Mantling			UMETA(DisplayName = "Mantling"),
	Lm_Ragdoll			UMETA(DisplayName = "Ragdoll")
};

UENUM(BlueprintType)
enum class ELmOverlayState :uint8 {
	Lm_Default			UMETA(DisplayName = "Default"),
	Lm_Masculine		UMETA(DisplayName = "Masculine"),
	Lm_Feminine			UMETA(DisplayName = "Feminine"),
	Lm_Injured			UMETA(DisplayName = "Injured"),
	Lm_HandsTied		UMETA(DisplayName = "HandsTied"),
	Lm_Rifle			UMETA(DisplayName = "Rifle"),
	Lm_Pistol1H			UMETA(DisplayName = "Pistol 1 Hand"),
	Lm_Pistol2H			UMETA(DisplayName = "Pistol 2 Hands"),
	Lm_Bow				UMETA(DisplayName = "Bow"),
	Lm_Torch			UMETA(DisplayName = "Torch"),
	Lm_Binoculars		UMETA(DisplayName = "Binoculars"),
	Lm_Box				UMETA(DisplayName = "Box"),
	Lm_Barrel			UMETA(DisplayName = "Barrel"),
	Lm_Count			UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ELmStance :uint8 {
	Lm_Standing			UMETA(DisplayName = "Standing"),
	Lm_Crouching		UMETA(DisplayName = "Crouching")
};

UENUM(BlueprintType)
enum class ELmViewMode :uint8 {
	Lm_TPS				UMETA(DisplayName = "Third Person"),
	Lm_FPS				UMETA(DisplayName = "First Person")
};

UENUM(BlueprintType)
enum class ELmFootStepType :uint8 {
	Lm_Step				UMETA(DisplayName = "Step"),
	Lm_WalkRun			UMETA(DisplayName = "Walk|Run"),
	Lm_Jump				UMETA(DisplayName = "Jump"),
	Lm_Land				UMETA(DisplayName = "Land")
};

UENUM(BlueprintType)
enum class ELmGroundedEntryState :uint8 {
	Lm_None				UMETA(DisplayName = "None"),
	Lm_Roll				UMETA(DisplayName = "Roll")
};

UENUM(BlueprintType)
enum class ELmHipsDirection :uint8 {
	Lm_F				UMETA(DisplayName = "Front"),
	Lm_B				UMETA(DisplayName = "Back"),
	Lm_RF				UMETA(DisplayName = "Right Front"),
	Lm_RB				UMETA(DisplayName = "Right Back"),
	Lm_LF				UMETA(DisplayName = "Left Front"),
	Lm_LB				UMETA(DisplayName = "Left Back")
};

UENUM(BlueprintType)
enum class ELmMantleType :uint8 {
	Lm_HighMantle		UMETA(DisplayName = "High Mantle"),
	Lm_LowMantle		UMETA(DisplayName = "Low Mantle"),
	Lm_FallingCatch		UMETA(DisplayName = "Falling Catch")
};

UENUM(BlueprintType)
enum class ELmMovementDirection :uint8 {
	Lm_Forward			UMETA(DisplayName = "Forward"),
	Lm_Backward			UMETA(DisplayName = "Backward"),
	Lm_Right			UMETA(DisplayName = "Right"),
	Lm_Left				UMETA(DisplayName = "Left")
};

UENUM(BlueprintType)
enum class ELmInputProcessingMode :uint8 {
	Lm_PressAndHold		UMETA(DisplayName = "Press And Hold"),
	Lm_DoublePress		UMETA(DisplayName = "Double Press")
};

UENUM(BlueprintType)
enum class ELmButtonPressType :uint8 {
	Lm_Tapping			UMETA(DisplayName = "Tapping"),
	Lm_Holding			UMETA(DisplayName = "Holding"),
	Lm_Released			UMETA(DisplayName = "Released"),
};

UENUM(BlueprintType)
enum class ELmCharacterMeshStyle :uint8 {
	Lm_Default			UMETA(DisplayName = "Default"),
	Lm_Skin				UMETA(DisplayName = "Skin")
};

UENUM(BlueprintType)
enum class ELmRotationMode :uint8 {
	Lm_VelocityDirection	UMETA(DisplayName = "Velocity Direction"),
	Lm_LookingDirection		UMETA(DisplayName = "Looking Direction"),
	Lm_Aiming				UMETA(DisplayName = "Aiming")
};

UENUM(BlueprintType)
enum class ELmAnimFeaturesExample :uint8 {
	Lm_StrideBlending		UMETA(DisplayName = "Stride Blending"),
	Lm_AdditiveLeaning		UMETA(DisplayName = "Additive Leaningn"),
	Lm_SprintImpulse		UMETA(DisplayName = "Sprint Impulse")
};

UENUM(BlueprintType)
enum class ELmStateTracking :uint8 {
	Lm_WhileTrue		UMETA(DisplayName = "While True"),
	Lm_WhileFalse		UMETA(DisplayName = "While False"),
	Lm_ChangedToTrue	UMETA(DisplayName = "Changed To True"),
	Lm_ChangedToFalse	UMETA(DisplayName = "Changed To False")
};

UENUM(BlueprintType)
enum class ELmUsingHand :uint8 {
	Lm_LeftHand			UMETA(DisplayName = "Left Hand"),
	Lm_RightHand		UMETA(DisplayName = "Right Hand"),
	Lm_BothHands		UMETA(DisplayName = "Both Hands")
};