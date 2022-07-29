#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "../../LmEnums.h"
#include <Animation/AnimMontage.h>
#include "LmEarlyBlendOut.generated.h"

UCLASS()
class LOCOMOTION_API ULmEarlyBlendOut : public UAnimNotifyState {
	GENERATED_BODY()
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, category = "Locomotion")
		UAnimMontage* Montage;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, category = "Locomotion")
		float BlendOutTime = 0.25f;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, category = "Locomotion")
		bool bCheckMovementState;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, category = "Locomotion")
		ELmMovementState MovementState = ELmMovementState::Lm_None;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, category = "Locomotion")
		bool bCheckStance;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, category = "Locomotion")
		ELmStance Stance = ELmStance::Lm_Standing;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, category = "Locomotion")
		bool bCheckMovementInput;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual FString GetNotifyName_Implementation() const override;
};