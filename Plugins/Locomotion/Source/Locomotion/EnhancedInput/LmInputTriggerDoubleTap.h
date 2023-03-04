#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "LmInputTriggerDoubleTap.generated.h"

UCLASS(NotBlueprintable, meta = (DisplayName = "Double Tap", NotInputConfigurable = "true"))
class LOCOMOTION_API ULmInputTriggerDoubleTap : public UInputTrigger {
	GENERATED_BODY()

protected:
	virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;
public:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Trigger Settings", meta = (DisplayThumbnail = "false"))
		float Delay = .5f;

private:
	float LastTappedTime = 0.f;
};