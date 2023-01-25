#include "LmCharacterAnimationInterface.h"
#include "../LmLogger.h"

// Add default functionality here for any ILmCharacterAnimationInterface functions that are not pure virtual.
void ILmCharacterAnimationInterface::Jumped_Implementation() {
	ULmLogger::LogError(TEXT("Invalid interface method calling. ILmCharacterAnimationInterface::Jumped_Implementation"));
}

void ILmCharacterAnimationInterface::SetGroundedEntryState_Implementation(ELmGroundedEntryState GroundedEntryState) {
	ULmLogger::LogError(TEXT("Invalid interface method calling. ILmCharacterAnimationInterface::SetGroundedEntryState_Implementation"));
}

void ILmCharacterAnimationInterface::SetOverlayOverrideState_Implementation(int OverlayOverrideState) {
	ULmLogger::LogError(TEXT("Invalid interface method calling. ILmCharacterAnimationInterface::SetOverlayOverrideState_Implementation"));
}