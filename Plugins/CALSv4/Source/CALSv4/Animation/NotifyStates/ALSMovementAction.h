

#pragma once

#include "CoreMinimal.h"
#include "../../ALSEnums.h"
#include <Animation/AnimNotifies/AnimNotifyState.h>
#include "ALSMovementAction.generated.h"

/**
 *
 */
UCLASS()
class CALSV4_API UALSMovementAction : public UAnimNotifyState {
	GENERATED_BODY()
protected:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		EALSMovementAction MovementAction;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	virtual FString GetNotifyName_Implementation() const override;
};
