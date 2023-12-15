#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include <GameFramework/PlayerController.h>

#include "Locomotion/DataTypes/LmEnums.h"
#include "LmCameraAnimInstance.generated.h"

UCLASS()
class LOCOMOTION_API ULmCameraAnimInstance : public UAnimInstance {
	GENERATED_BODY()

protected:
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion" )
	bool bDebugView = false;
	UPROPERTY( BlueprintReadOnly , VisibleDefaultsOnly , Category = "Locomotion" )
	bool bRightShoulder = true;

	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion" )
	ELmMovementState MovementState = ELmMovementState::Lm_None;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion" )
	ELmMovementAction MovementAction = ELmMovementAction::Lm_None;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion" )
	ELmRotationMode RotationMode = ELmRotationMode::Lm_LookingDirection;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion" )
	ELmGait Gait = ELmGait::Lm_Walking;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion" )
	ELmStance Stance = ELmStance::Lm_Standing;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion" )
	ELmViewMode ViewMode = ELmViewMode::Lm_TPS;

public:
	UFUNCTION( BlueprintCallable , Category = "Locomotion" )
	void SetControlledPawn(APawn* Pawn);

	UFUNCTION( BlueprintCallable , Category = "Locomotion" )
	void SetPlayerController(APlayerController* Controller);

protected:
	//~ Event handlers
	UFUNCTION()
	void OnGaitChanged(const ELmGait NewGait);

	UFUNCTION()
	void OnMovementStateChanged(const ELmMovementState NewMovementState);

	UFUNCTION()
	void OnMovementActionChanged(const ELmMovementAction NewMovementAction);

	UFUNCTION()
	void OnStanceChanged(const ELmStance NewStance);

	UFUNCTION()
	void OnRotationModeChanged(const ELmRotationMode NewRotationMode);

	UFUNCTION()
	void OnViewModeChanged(const ELmViewMode NewViewMode);

	UFUNCTION()
	void OnCameraShoulderChanged(const bool bRight);

	UFUNCTION()
	void OnDebugViewChanged(const bool bNewDebugView);

	//~ Event Handlers
};
