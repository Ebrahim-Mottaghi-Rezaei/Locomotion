#pragma once

#include "CoreMinimal.h"
#include <Animation/AnimNotifies/AnimNotify.h>
#include <Components/SkeletalMeshComponent.h>
#include <Animation/AnimSequenceBase.h>
#include "../../LmEnums.h"
#include "LmFootStepAnimNotify.generated.h"

UCLASS()
class LOCOMOTION_API ULmFootStepAnimNotify : public UAnimNotify {
	GENERATED_BODY()
protected:
	ULmFootStepAnimNotify();

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Locomotion")
		USoundBase* Sound;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Locomotion")
		FName AttachPointName = FName(TEXT("root"));
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Locomotion")
		ELmFootStepType FootStepType = ELmFootStepType::Lm_Step;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Locomotion")
		float VolumeMultiplier = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Locomotion")
		float PitchMultiplier = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Locomotion")
		bool bOverrideMaskCurve;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual FString GetNotifyName_Implementation() const;
};