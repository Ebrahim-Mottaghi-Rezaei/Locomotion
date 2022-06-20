

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ALSOverlayOverride.generated.h"

/**
 *
 */
UCLASS()
class CALSV4_API UALSOverlayOverride : public UAnimNotifyState {
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int OverlayOverriderState;
	virtual FString GetNotifyName_Implementation() const override;
	virtual  void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
