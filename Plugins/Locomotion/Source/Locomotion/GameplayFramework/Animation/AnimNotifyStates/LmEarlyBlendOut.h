#pragma once

#include <Animation/AnimMontage.h>
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Locomotion/DataTypes/LmEnums.h"
#include "LmEarlyBlendOut.generated.h"

UCLASS( DisplayName="Early Blend-Out" )
class LOCOMOTION_API ULmEarlyBlendOut : public UAnimNotifyState {
	GENERATED_BODY()

public:
	ULmEarlyBlendOut();

	UPROPERTY( EditInstanceOnly , BlueprintReadWrite , category = "Locomotion" )
	UAnimMontage* Montage = nullptr;
	UPROPERTY( EditInstanceOnly , BlueprintReadWrite , category = "Locomotion" )
	float BlendOutTime = 0.25f;
	UPROPERTY( EditInstanceOnly , BlueprintReadWrite , category = "Locomotion" )
	bool bCheckMovementState = true;
	UPROPERTY( EditInstanceOnly , BlueprintReadWrite , category = "Locomotion" )
	ELmMovementState MovementState = ELmMovementState::Lm_None;
	UPROPERTY( EditInstanceOnly , BlueprintReadWrite , category = "Locomotion" )
	bool bCheckStance = true;
	UPROPERTY( EditInstanceOnly , BlueprintReadWrite , category = "Locomotion" )
	ELmStance Stance = ELmStance::Lm_Standing;
	UPROPERTY( EditInstanceOnly , BlueprintReadWrite , category = "Locomotion" )
	bool bCheckMovementInput = true;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;

	virtual FString GetNotifyName_Implementation() const override;
};
