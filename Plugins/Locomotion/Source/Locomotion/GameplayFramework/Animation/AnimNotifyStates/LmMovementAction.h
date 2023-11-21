#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Locomotion/DataTypes/LmEnums.h"
#include "LmMovementAction.generated.h"

UCLASS( DisplayName="Movement Action" )
class LOCOMOTION_API ULmMovementAction : public UAnimNotifyState {
	GENERATED_BODY()

public:
	ULmMovementAction();

protected:
	UPROPERTY( EditInstanceOnly , BlueprintReadWrite , Category= "Locomotion" )
	ELmMovementAction MovementAction = ELmMovementAction::Lm_None;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	virtual FString GetNotifyName_Implementation() const override;
};
