#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ALSBowAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBowDraw, float, draw);

UCLASS()
class CALSV4_API UALSBowAnimInstance : public UAnimInstance {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Advanced Locomotion System|Bow")
		FOnBowDraw OnBowDrawChanged;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Advanced Locomotion System|Bow")
		float Draw;

	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Bow")
		void ChangeDraw(const float NewDraw);
};