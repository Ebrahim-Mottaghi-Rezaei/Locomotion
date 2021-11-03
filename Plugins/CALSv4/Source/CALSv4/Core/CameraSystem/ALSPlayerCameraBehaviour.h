#pragma once
#include "CoreMinimal.h"
#include "CALSv4/Data/ALSEnums.h"
#include "ALSPlayerCameraBehaviour.generated.h"

UCLASS(Transient, Blueprintable, BlueprintType, hideCategories = (AnimInstance))
class CALSV4_API UALSPlayerCameraBehaviour :public UAnimInstance {
	GENERATED_BODY()
public:
	UALSPlayerCameraBehaviour();
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		bool bDebugView;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		bool bRightShoulder;
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		APawn* controlledPawn;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		APlayerController* playerController;
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		EALSMovementState MovementState;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		EALSMovementAction MovementAction;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		EALSRotationMode RotationMode;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		EALSGait Gait;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		EALSStance Stance;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		EALSViewMode ViewMode;

	virtual  void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};