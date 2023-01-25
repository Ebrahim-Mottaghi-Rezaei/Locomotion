#include "LmCharacterInterface.h"
#include "../LmLogger.h"

// Add default functionality here for any ILmCharacterInterface functions that are not pure virtual.

FLmCurrentState ILmCharacterInterface::GetCurrentState_Implementation() {
	ULmLogger::LogError(TEXT("Invalid interface method calling. ILmCharacterInterface::GetCurrentState_Implementation"));
	return FLmCurrentState();
}

FLmEssentialValues ILmCharacterInterface::GetEssentialValues_Implementation() {
	ULmLogger::LogError(TEXT("Invalid interface method calling. ILmCharacterInterface::GetEssentialValues_Implementation"));
	return FLmEssentialValues();
}

void ILmCharacterInterface::SetMovementState_Implementation(ELmMovementState NewMovementState) {
	ULmLogger::LogError(TEXT("Invalid interface method calling. ILmCharacterInterface::SetMovementState_Implementation"));
}

void ILmCharacterInterface::SetOverlayState_Implementation(ELmOverlayState NewOverlayState) {
	ULmLogger::LogError(TEXT("Invalid interface method calling. ILmCharacterInterface::SetOverlayState_Implementation"));
}

void ILmCharacterInterface::SetViewMode_Implementation(ELmViewMode NewViewMode) {
	ULmLogger::LogError(TEXT("Invalid interface method calling. ILmCharacterInterface::SetViewMode_Implementation"));
}

void ILmCharacterInterface::SetGait_Implementation(ELmGait NewGait) {
	ULmLogger::LogError(TEXT("Invalid interface method calling. ILmCharacterInterface::SetGait_Implementation"));
}

void ILmCharacterInterface::SetRotationMode_Implementation(ELmRotationMode NewRotationMode) {
	ULmLogger::LogError(TEXT("Invalid interface method calling. ILmCharacterInterface::SetRotationMode_Implementations"));
}

void ILmCharacterInterface::SetMovementAction_Implementation(ELmMovementAction NewMovementAction) {
	ULmLogger::LogError(TEXT("Invalid interface method calling. ILmCharacterInterface::SetMovementAction_Implementation"));
}