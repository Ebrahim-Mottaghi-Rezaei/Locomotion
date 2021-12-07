#pragma once
#include "CoreMinimal.h"
#include "CALSv4/Data/ALSEnums.h"
#include "ALSPlayerCameraBehaviour.generated.h"

UCLASS(Transient, Blueprintable, BlueprintType, hideCategories = (AnimInstance))
class CALSV4_API UALSPlayerCameraBehaviour :public UAnimInstance {
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Camera Animation")
		bool bDebugView = false;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Camera Animation")
		bool bRightShoulder = false;
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Camera Animation")
		APawn* controlledPawn;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Camera Animation")
		APlayerController* playerController;
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Camera Animation")
		EALSMovementState MovementState = EALSMovementState::ALS_None;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Camera Animation")
		EALSMovementAction MovementAction = EALSMovementAction::ALS_None;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Camera Animation")
		EALSRotationMode RotationMode = EALSRotationMode::ALS_VelocityDirection;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Camera Animation")
		EALSGait Gait = EALSGait::ALS_Walking;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Camera Animation")
		EALSStance Stance = EALSStance::ALS_Standing;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Camera Animation")
		EALSViewMode ViewMode = EALSViewMode::ALS_TPS;

	virtual  void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};