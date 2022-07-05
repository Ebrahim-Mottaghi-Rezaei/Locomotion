#pragma once

#include "CoreMinimal.h"
#include <Animation/AnimNotifies/AnimNotify.h>
#include "../../LmEnums.h"
#include "LmGroundedEntryStateAnimNotify.generated.h"

UCLASS()
class LOCOMOTION_API ULmGroundedEntryStateAnimNotify : public UAnimNotify {
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Locomotion")
		ELmGroundedEntryState GroundedEntryState;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual FString GetNotifyName_Implementation() const override;
};