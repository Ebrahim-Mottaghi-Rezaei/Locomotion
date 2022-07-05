#include "LmCameraInterface.h"
#include "../LmLogger.h"

// Add default functionality here for any ILmCameraInterface functions that are not pure virtual.

FLmCameraParameters ILmCameraInterface::GetCameraParameters_Implementation() {
	ULmLogger::LogError(TEXT("Invalid interface method calling. IALSCameraInterface::GetCameraParameters_Implementation"));
	return FLmCameraParameters();
}

FVector ILmCameraInterface::GetFPCameraTarget_Implementation() {
	ULmLogger::LogError(TEXT("Invalid interface method calling. IALSCameraInterface::GetFPCameraTarget_Implementation"));
	return FVector();
}

FTransform ILmCameraInterface::Get3PPivotTarget_Implementation() {
	ULmLogger::LogError(TEXT("Invalid interface method calling. IALSCameraInterface::Get3PPivotTarget_Implementation"));
	return FTransform();
}

FLmTraceParams ILmCameraInterface::Get3PTraceParameters_Implementation() {
	ULmLogger::LogError(TEXT("Invalid interface method calling. IALSCameraInterface::Get3PTraceParameters_Implementation"));
	return FLmTraceParams();
}
