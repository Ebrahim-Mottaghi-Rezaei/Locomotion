#pragma once

#include "CoreMinimal.h"
#include "UObject/NameTypes.h"
#include "AnimationModifiers/Public/AnimationModifier.h"
#include "Animation/AnimSequence.h"
#include "ALSCalulateRotationAmount.generated.h"

class UAnimSequenceBase;

UCLASS(BlueprintType,Transient, Category = "C++ ALS|Animation Modifiers")
class CALSV4_API UALSCalulateRotationAmount : public UAnimationModifier {
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UAnimSequence* AnimSequence;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName CurveName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName RootBoneName;

public:
	UALSCalulateRotationAmount();
	void OnApply_Implementation(UAnimSequence* AnimationSequence) override;
};