#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Camera/CameraShakeBase.h"
#include "ALSCameraShakeAnimNotify.generated.h"


class USkeletalMeshComponent;
class UAnimSequenceBase;

UCLASS(BlueprintType, Category = "C++ ALS|Animation Notifies")
class CALSV4_API UALSCameraShakeAnimNotify : public UAnimNotify {
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "3", UIMin = "0", UIMax = "3"))
		float Scale = 1.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<UCameraShakeBase> CameraShake;
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};