#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "../../ALSEnums.h"
#include <Animation/AnimMontage.h>
#include "ALSEarlyBlendOut.generated.h"

UCLASS()
class CALSV4_API UALSEarlyBlendOut : public UAnimNotifyState {
	GENERATED_BODY()
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		UAnimMontage* Montage;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		float BlendOutTime = 0.25f;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		bool bCheckMovementState;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		EALSMovementState MovementState = EALSMovementState::ALS_None;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		bool bCheckStance;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		EALSStance Stance = EALSStance::ALS_Standing;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		bool bCheckMovementInput;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual FString GetNotifyName_Implementation() const override;
};