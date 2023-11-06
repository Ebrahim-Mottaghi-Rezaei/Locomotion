#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "LmInputTriggerDoubleTapAndHold.generated.h"

UCLASS(NotBlueprintable, meta = (DisplayName = "Double Tap and Hold", NotInputConfigurable = "true"))
class LOCOMOTION_API ULmInputTriggerDoubleTapAndHold : public UInputTrigger {
	GENERATED_BODY()
protected:
	virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Trigger Settings", meta = (DisplayThumbnail = "false", UIMin = 0.f, UIMax = 0.5f, ClampMin = 0.1f, ClampMax = 0.5f))
		float MaxWaitingTime = .2f;
private:

	float lastTapTime;
	bool bFlag;
};