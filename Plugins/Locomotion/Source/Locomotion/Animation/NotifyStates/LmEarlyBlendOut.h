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
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		UAnimMontage* Montage;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		float BlendOutTime = 0.25f;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		bool bCheckMovementState;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		ELmMovementState MovementState = ELmMovementState::Lm_None;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		bool bCheckStance;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		ELmStance Stance = ELmStance::Lm_Standing;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		bool bCheckMovementInput;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual FString GetNotifyName_Implementation() const override;
};