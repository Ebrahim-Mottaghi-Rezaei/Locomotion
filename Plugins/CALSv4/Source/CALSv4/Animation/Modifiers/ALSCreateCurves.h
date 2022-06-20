#pragma once

#include "CoreMinimal.h"
#include "AnimationModifier.h"
#include <CALSv4/Data/ALSStructs.h>
#include "ALSCreateCurves.generated.h"

UCLASS(BlueprintType, Transient, Category = "C++ ALS|Animation Modifiers")
class CALSV4_API UALSCreateCurves : public UAnimationModifier {
	GENERATED_BODY()

protected:
	FALSAnimCurveCreationParams CurveParams;
	TArray<FALSAnimCurveCreationParams> CurvesToCreate;
public:
	void OnApply_Implementation(UAnimSequence* AnimationSequence) override;
};