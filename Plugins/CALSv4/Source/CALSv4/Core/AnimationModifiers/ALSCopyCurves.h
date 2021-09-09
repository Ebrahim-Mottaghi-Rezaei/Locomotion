#pragma once

#include "CoreMinimal.h"
#include "AnimationModifier.h"
#include "Chaos/Array.h"
#include "ALSCopyCurves.generated.h"

UCLASS(BlueprintType, Transient, Category = "C++ ALS|Animation Modifiers")
class CALSV4_API UALSCopyCurves : public UAnimationModifier {
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		bool CopyAllCurves;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		UAnimSequence* AnimToCopyFrom;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FName> CurvesToCopy;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FName> AllCurves;

	UAnimSequence* AnimSequence;
public:
	UALSCopyCurves();
	/// <summary>
	/// This Anim Modifier simply copies curves from one animation to another.
	/// </summary>
	/// <param name="AnimationSequence"></param>
	void OnApply_Implementation(UAnimSequence* AnimationSequence) override;
};