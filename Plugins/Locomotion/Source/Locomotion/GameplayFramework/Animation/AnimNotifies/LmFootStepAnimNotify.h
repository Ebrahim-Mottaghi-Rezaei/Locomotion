#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "Locomotion/DataTypes/LmEnums.h"
#include "LmFootStepAnimNotify.generated.h"

UCLASS( DisplayName="Foot Step" )
class LOCOMOTION_API ULmFootStepAnimNotify : public UAnimNotify {
	GENERATED_BODY()

protected:
	ULmFootStepAnimNotify();

	UPROPERTY( BlueprintReadWrite , EditAnywhere )
	USoundBase* Sound;
	UPROPERTY( BlueprintReadWrite , EditInstanceOnly )
	FName AttachPointName = FName( TEXT( "root" ) );
	UPROPERTY( BlueprintReadWrite , EditInstanceOnly )
	ELmFootStepType FootStepType = ELmFootStepType::Lm_Step;
	UPROPERTY( BlueprintReadWrite , EditInstanceOnly )
	float VolumeMultiplier = 1.0f;
	UPROPERTY( BlueprintReadWrite , EditInstanceOnly )
	float PitchMultiplier = 1.0f;
	UPROPERTY( BlueprintReadWrite , EditInstanceOnly )
	bool bOverrideMaskCurve;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	virtual FString GetNotifyName_Implementation() const override;
};
