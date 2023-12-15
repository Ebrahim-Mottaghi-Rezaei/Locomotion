#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LmBowAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBowDraw , float , draw );

UCLASS()
class LOCOMOTION_API ULmBowAnimInstance : public UAnimInstance {
	GENERATED_BODY()

public:
	ULmBowAnimInstance();

	UPROPERTY( BlueprintAssignable , BlueprintCallable , Category = "Locomotion" )
	FOnBowDraw OnBowDrawChanged;

	UPROPERTY( BlueprintReadOnly , VisibleAnywhere , Category = "Locomotion" )
	float Draw = 0.0f;

	UFUNCTION( BlueprintCallable , Category = "Locomotion" )
	void ChangeDraw(const float NewDraw);
};
