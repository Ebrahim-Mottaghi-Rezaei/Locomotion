#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CALSv4/Data/ALSEnums.h"
#include "ALSEarlyBlendOut.generated.h"

UCLASS()
class CALSV4_API UALSEarlyBlendOut : public UAnimNotifyState {
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UAnimMontage* Montage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float BlendOutTime = 0.25f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bCheckMovementState;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		EALSMovementState MovementState = EALSMovementState::ALS_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bCheckStance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		EALSStance Stance = EALSStance::ALS_Standing;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bCheckMovementInput;

	void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual FString GetNotifyName_Implementation() const override;
};