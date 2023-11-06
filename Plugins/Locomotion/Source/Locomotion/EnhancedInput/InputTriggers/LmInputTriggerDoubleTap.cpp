#include "LmInputTriggerDoubleTap.h"
#include "InputTriggers.h"
#include "EnhancedPlayerInput.h"

ETriggerState ULmInputTriggerDoubleTap::UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, const FInputActionValue ModifiedValue, float DeltaTime) {
	if (IsActuated(ModifiedValue) && !IsActuated(LastValue)) {
		const float CurrentTime = PlayerInput->GetOuterAPlayerController()->GetWorld()->GetRealTimeSeconds();
		if (CurrentTime - LastTappedTime < Delay) {
			LastTappedTime = 0;
			return ETriggerState::Triggered;
		}
		LastTappedTime = CurrentTime;
	}
	return ETriggerState::None;
}
