#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CALSv4/Data/ALSEnums.h"
#include "ALSFootStepAnimNotify.generated.h"

UCLASS()
class CALSV4_API UALSFootStepAnimNotify : public UAnimNotify {
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		bool bOverriderMaskCurve;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FName AttachPointName = FName(TEXT("root"));
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		float VolumeMultiplier = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		float PitchMultiplier = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		EALSFootStepType FootStepType = EALSFootStepType::ALS_Step;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		USoundBase* Sound;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};