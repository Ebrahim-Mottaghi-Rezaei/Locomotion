


#include "ALSCharacterInterface.h"
#include "../ALSLogger.h"

// Add default functionality here for any IALSCharacterInterface functions that are not pure virtual.

FALSCurrentState IALSCharacterInterface::GetCurrentState_Implementation() {
	UALSLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterInterface::GetCurrentState_Implementation"));
	return FALSCurrentState();
}

FALSEssentialValues IALSCharacterInterface::GetEssentialValues_Implementation() {
	UALSLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterInterface::GetEssentialValues_Implementation"));
	return FALSEssentialValues();
}

void IALSCharacterInterface::SetMovementState_Implementation(EALSMovementState NewMovementState) {
	UALSLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterInterface::SetMovementState_Implementation"));
}

void IALSCharacterInterface::SetOverlayState_Implementations(EALSOverlayState NewOverlayState) {
	UALSLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterInterface::SetOverlayState_Implementations"));
}

void IALSCharacterInterface::SetViewMode_Implementations(EALSViewMode NewViewMode) {
	UALSLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterInterface::SetViewMode_Implementations"));
}

void IALSCharacterInterface::SetGait_Implementations(EALSGait NewGait) {
	UALSLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterInterface::SetGait_Implementations"));
}

void IALSCharacterInterface::SetRotationMode_Implementations(EALSRotationMode NewRotationMode) {
	UALSLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterInterface::SetRotationMode_Implementations"));
}

void IALSCharacterInterface::SetMovementAction_Implementations(EALSMovementAction NewMovementAction) {
	UALSLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterInterface::SetMovementAction_Implementations"));
}
