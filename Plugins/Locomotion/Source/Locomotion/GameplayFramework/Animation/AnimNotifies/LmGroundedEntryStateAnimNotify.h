#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Locomotion/DataTypes/LmEnums.h"
#include "LmGroundedEntryStateAnimNotify.generated.h"

UCLASS( DisplayName="Grounded Entry State" )
class LOCOMOTION_API ULmGroundedEntryStateAnimNotify : public UAnimNotify {
	GENERATED_BODY()

protected:
	UPROPERTY( BlueprintReadWrite , EditInstanceOnly )
	ELmGroundedEntryState GroundedEntryState;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	virtual FString GetNotifyName_Implementation() const override;
};
