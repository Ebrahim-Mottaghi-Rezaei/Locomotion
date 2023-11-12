#include "LmCharacterInterface.h"
#include "Locomotion/Logging/LMLogger.h"

// Add default functionality here for any ILmCharacterInterface functions that are not pure virtual.

FLmCurrentState ILmCharacterInterface::GetCurrentState_Implementation() {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCharacterInterface::GetCurrentState_Implementation" ) );
	return FLmCurrentState();
}


FLmEssentialValues ILmCharacterInterface::GetEssentialValues_Implementation() {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCharacterInterface::GetEssentialValues_Implementation" ) );
	return FLmEssentialValues();
}


void ILmCharacterInterface::SetMovementState_Implementation(ELmMovementState NewMovementState) {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCharacterInterface::SetMovementState_Implementation" ) );
}


void ILmCharacterInterface::SetOverlayState_Implementation(ELmOverlayState NewOverlayState) {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCharacterInterface::SetOverlayState_Implementation" ) );
}


void ILmCharacterInterface::SetViewMode_Implementation(ELmViewMode NewViewMode) {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCharacterInterface::SetViewMode_Implementation" ) );
}


void ILmCharacterInterface::SetGait_Implementation(ELmGait NewGait) {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCharacterInterface::SetGait_Implementation" ) );
}


void ILmCharacterInterface::SetStance_Implementation(ELmStance NewStance) {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCharacterInterface::SetStance_Implementation" ) );
}


void ILmCharacterInterface::SetRotationMode_Implementation(ELmRotationMode NewRotationMode) {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCharacterInterface::SetRotationMode_Implementations" ) );
}


void ILmCharacterInterface::SetMovementAction_Implementation(ELmMovementAction NewMovementAction) {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCharacterInterface::SetMovementAction_Implementation" ) );
}


//~ Camera methods
FLmCameraParameters ILmCharacterInterface::GetCameraParameters_Implementation() {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCharacterInterface::GetCameraParameters_Implementation" ) );
	return FLmCameraParameters();
}


FVector ILmCharacterInterface::GetFPCameraTarget_Implementation() {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCharacterInterface::GetFPCameraTarget_Implementation" ) );
	return FVector();
}


FTransform ILmCharacterInterface::Get3PPivotTarget_Implementation() {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCharacterInterface::Get3PPivotTarget_Implementation" ) );
	return FTransform();
}


FLmTraceParams ILmCharacterInterface::Get3PTraceParameters_Implementation() {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCharacterInterface::Get3PTraceParameters_Implementation" ) );
	return FLmTraceParams();
}
