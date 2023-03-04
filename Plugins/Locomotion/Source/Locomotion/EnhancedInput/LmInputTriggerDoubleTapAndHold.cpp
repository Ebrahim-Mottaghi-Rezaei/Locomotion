#include "LmInputTriggerDoubleTapAndHold.h"
#include "InputTriggers.h"
#include "EnhancedPlayerInput.h"

ETriggerState ULmInputTriggerDoubleTapAndHold::UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) {

	if (!IsActuated(LastValue) && IsActuated(ModifiedValue)) {
		const float currentTime = PlayerInput->GetOuterAPlayerController()->GetWorld()->GetRealTimeSeconds();
		const float delta = currentTime - lastTapTime;
		bFlag = delta < MaxWaitingTime;
		lastTapTime = currentTime;
	}

	if (bFlag && IsActuated(LastValue) && IsActuated(ModifiedValue))
		return ETriggerState::Triggered;

	return ETriggerState::None;
}
