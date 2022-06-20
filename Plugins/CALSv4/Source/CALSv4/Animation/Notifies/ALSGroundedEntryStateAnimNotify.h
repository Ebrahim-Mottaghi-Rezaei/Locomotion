#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CALSv4/Data/ALSEnums.h"
#include "ALSGroundedEntryStateAnimNotify.generated.h"

UCLASS()
class CALSV4_API UALSGroundedEntryStateAnimNotify : public UAnimNotify {
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EALSGroundedEntryState GroundedEntryState;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual FString GetNotifyName_Implementation() const override;
};