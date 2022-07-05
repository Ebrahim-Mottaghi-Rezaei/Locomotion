#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShakeBase.h"
#include <Animation/AnimNotifies/AnimNotify.h>
#include "LmCameraShakeAnimNotify.generated.h"


class USkeletalMeshComponent;
class UAnimSequenceBase;

UCLASS(BlueprintType, Category = "Locomotion|Animation Notifies")
class LOCOMOTION_API ULmCameraShakeAnimNotify : public UAnimNotify {
	GENERATED_BODY()
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Locomotion", meta = (ClampMin = "0", ClampMax = "3", UIMin = "0", UIMax = "3"))
		TSubclassOf<UCameraShakeBase> CameraShake;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Locomotion")
		float Scale = 1.f;
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	virtual FString GetNotifyName_Implementation() const;
};