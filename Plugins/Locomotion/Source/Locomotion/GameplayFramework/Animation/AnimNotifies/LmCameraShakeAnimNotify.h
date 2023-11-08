#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Camera/CameraShakeBase.h"
#include "LmCameraShakeAnimNotify.generated.h"

class USkeletalMeshComponent;
class UAnimSequenceBase;

UCLASS( DisplayName="Camera Shake" )
class LOCOMOTION_API ULmCameraShakeAnimNotify : public UAnimNotify {
	GENERATED_BODY()

protected:
	UPROPERTY( EditInstanceOnly , BlueprintReadWrite , meta = (ClampMin = "0" , ClampMax = "3" , UIMin = "0" , UIMax = "3") )
	TSubclassOf<UCameraShakeBase> CameraShake;
	UPROPERTY( EditInstanceOnly , BlueprintReadWrite )
	float Scale = 1.f;

public:
	ULmCameraShakeAnimNotify();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	virtual FString GetNotifyName_Implementation() const override;
};
