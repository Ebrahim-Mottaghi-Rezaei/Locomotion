

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../LmEnums.h"
#include <GameFramework/PlayerController.h>
#include "LmCameraAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class LOCOMOTION_API ULmCameraAnimInstance : public UAnimInstance {
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		bool bDebugView = false;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		bool bRightShoulder = false;
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		APawn* controlledPawn;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		APlayerController* playerController;
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		ELmMovementState MovementState = ELmMovementState::Lm_None;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		ELmMovementAction MovementAction = ELmMovementAction::Lm_None;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		ELmRotationMode RotationMode = ELmRotationMode::Lm_VelocityDirection;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		ELmGait Gait = ELmGait::Lm_Walking;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		ELmStance Stance = ELmStance::Lm_Standing;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		ELmViewMode ViewMode = ELmViewMode::Lm_TPS;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
