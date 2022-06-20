


#include "ALSCameraInterface.h"
#include "../ALSLogger.h"

// Add default functionality here for any IALSCameraInterface functions that are not pure virtual.

FALSCameraParameters IALSCameraInterface::GetCameraParameters_Implementation() {
	UALSLogger::LogError(TEXT("Invalid interface method calling. IALSCameraInterface::GetCameraParameters_Implementation"));
	return FALSCameraParameters();
}

FVector IALSCameraInterface::GetFPCameraTarget_Implementation() {
	UALSLogger::LogError(TEXT("Invalid interface method calling. IALSCameraInterface::GetFPCameraTarget_Implementation"));
	return FVector();
}

FTransform IALSCameraInterface::Get3PPivotTarget_Implementation() {
	UALSLogger::LogError(TEXT("Invalid interface method calling. IALSCameraInterface::Get3PPivotTarget_Implementation"));
	return FTransform();
}

FALSTraceParams IALSCameraInterface::Get3PTraceParameters_Implementation() {
	UALSLogger::LogError(TEXT("Invalid interface method calling. IALSCameraInterface::Get3PTraceParameters_Implementation"));
	return FALSTraceParams();
}
