#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "LmOverlayOverride.generated.h"

UCLASS( DisplayName="Overlay Override" )
class LOCOMOTION_API ULmOverlayOverride : public UAnimNotifyState {
	GENERATED_BODY()

public:
	ULmOverlayOverride();

protected:
	UPROPERTY( EditInstanceOnly , BlueprintReadWrite )
	int OverlayOverriderState = 0;

	virtual FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
