#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "LmOverlayOverride.generated.h"

UCLASS()
class LOCOMOTION_API ULmOverlayOverride : public UAnimNotifyState {
	GENERATED_BODY()
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Locomotion")
		int OverlayOverriderState;

	virtual FString GetNotifyName_Implementation() const override;
	virtual  void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
