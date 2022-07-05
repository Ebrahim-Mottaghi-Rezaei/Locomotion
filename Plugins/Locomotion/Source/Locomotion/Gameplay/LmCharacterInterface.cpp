#include "LmCharacterInterface.h"
#include "../LmLogger.h"

// Add default functionality here for any ILmCharacterInterface functions that are not pure virtual.

FLmCurrentState ILmCharacterInterface::GetCurrentState_Implementation() {
	ULmLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterInterface::GetCurrentState_Implementation"));
	return FLmCurrentState();
}

FLmEssentialValues ILmCharacterInterface::GetEssentialValues_Implementation() {
	ULmLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterInterface::GetEssentialValues_Implementation"));
	return FLmEssentialValues();
}

void ILmCharacterInterface::SetMovementState_Implementation(ELmMovementState NewMovementState) {
	ULmLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterInterface::SetMovementState_Implementation"));
}

void ILmCharacterInterface::SetOverlayState_Implementations(ELmOverlayState NewOverlayState) {
	ULmLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterInterface::SetOverlayState_Implementations"));
}

void ILmCharacterInterface::SetViewMode_Implementations(ELmViewMode NewViewMode) {
	ULmLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterInterface::SetViewMode_Implementations"));
}

void ILmCharacterInterface::SetGait_Implementations(ELmGait NewGait) {
	ULmLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterInterface::SetGait_Implementations"));
}

void ILmCharacterInterface::SetRotationMode_Implementations(ELmRotationMode NewRotationMode) {
	ULmLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterInterface::SetRotationMode_Implementations"));
}

void ILmCharacterInterface::SetMovementAction_Implementations(ELmMovementAction NewMovementAction) {
	ULmLogger::LogError(TEXT("Invalid interface method calling. IALSCharacterInterface::SetMovementAction_Implementations"));
}
