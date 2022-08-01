#pragma once

#include "CoreMinimal.h"
#include "../../LmEnums.h"
#include <Animation/AnimNotifies/AnimNotifyState.h>
#include "LmMovementAction.generated.h"

UCLASS()
class LOCOMOTION_API ULmMovementAction : public UAnimNotifyState {
	GENERATED_BODY()
protected:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Locomotion")
		ELmMovementAction MovementAction;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	virtual FString GetNotifyName_Implementation() const override;
};
