#pragma once

#include "CoreMinimal.h"
#include "AnimationModifier.h"
#include "ALSCreateLayeringCurves.generated.h"


UCLASS(BlueprintType, Transient, Category = "C++ ALS|Animation Modifiers")
class CALSV4_API UALSCreateLayeringCurves : public UAnimationModifier {
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		TArray<FName> CurvesToCreate;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		float DefaultValue;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		bool KeyEachFrame;
public:
	UALSCreateLayeringCurves();
	void OnApply_Implementation(UAnimSequence* AnimationSequence) override;
};