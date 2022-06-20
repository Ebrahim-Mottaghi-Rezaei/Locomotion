#pragma once

#include "CoreMinimal.h"
#include <Animation/AnimNotifies/AnimNotify.h>
#include <Components/SkeletalMeshComponent.h>
#include <Animation/AnimSequenceBase.h>
#include "../../ALSEnums.h"
#include "ALSFootStepAnimNotify.generated.h"

UCLASS()
class CALSV4_API UALSFootStepAnimNotify : public UAnimNotify {
	GENERATED_BODY()
protected:
	UALSFootStepAnimNotify();

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
		USoundBase* Sound;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
		FName AttachPointName = FName(TEXT("root"));
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
		EALSFootStepType FootStepType = EALSFootStepType::ALS_Step;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
		float VolumeMultiplier = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
		float PitchMultiplier = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
		bool bOverrideMaskCurve;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual FString GetNotifyName_Implementation() const;
};