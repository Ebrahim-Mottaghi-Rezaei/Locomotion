


#include "ALSCharacterAnimationInterface.h"
#include "../ALSLogger.h"

// Add default functionality here for any IALSAnimationInterface functions that are not pure virtual.

void IALSCharacterAnimationInterface::Jumped_Implementation() {
	UALSLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterAnimationInterface::Jumped_Implementation"));
}

void IALSCharacterAnimationInterface::SetGroundedEntryState_Implementation(EALSGroundedEntryState GroundedEntryState) {
	UALSLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterAnimationInterface::SetGroundedEntryState_Implementation"));
}

void IALSCharacterAnimationInterface::SetOverlayOverrideState_Implementation(int OverlayOverrideState) {
	UALSLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterAnimationInterface::SetOverlayOverrideState_Implementation"));
}
