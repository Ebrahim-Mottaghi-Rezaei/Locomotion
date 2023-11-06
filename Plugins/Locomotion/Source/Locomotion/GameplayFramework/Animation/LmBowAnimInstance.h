#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LmBowAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBowDraw, float, draw);

UCLASS()
class LOCOMOTION_API ULmBowAnimInstance : public UAnimInstance {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Locomotion")
		FOnBowDraw OnBowDrawChanged;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Locomotion")
		float Draw;

	UFUNCTION(BlueprintCallable, Category = "Locomotion")
		void ChangeDraw(const float NewDraw);
};
