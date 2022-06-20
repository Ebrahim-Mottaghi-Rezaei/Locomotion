#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShakeBase.h"
#include <Animation/AnimNotifies/AnimNotify.h>
#include "ALSCameraShakeAnimNotify.generated.h"


class USkeletalMeshComponent;
class UAnimSequenceBase;

UCLASS(BlueprintType, Category = "C++ ALS|Animation Notifies")
class CALSV4_API UALSCameraShakeAnimNotify : public UAnimNotify {
	GENERATED_BODY()
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		TSubclassOf<UCameraShakeBase> CameraShake;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "3", UIMin = "0", UIMax = "3"))
		float Scale = 1.f;
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual FString GetNotifyName_Implementation() const;
};