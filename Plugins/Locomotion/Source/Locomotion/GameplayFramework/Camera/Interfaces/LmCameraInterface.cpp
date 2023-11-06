#include "LmCameraInterface.h"
#include "Locomotion/Logging/LMLogger.h"

// Add default functionality here for any ILmCameraInterface functions that are not pure virtual.

FLmCameraParameters ILmCameraInterface::GetCameraParameters_Implementation() {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCameraInterface::GetCameraParameters_Implementation" ) );
	return FLmCameraParameters();
}


FVector ILmCameraInterface::GetFPCameraTarget_Implementation() {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCameraInterface::GetFPCameraTarget_Implementation" ) );
	return FVector();
}


FTransform ILmCameraInterface::Get3PPivotTarget_Implementation() {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCameraInterface::Get3PPivotTarget_Implementation" ) );
	return FTransform();
}


FLmTraceParams ILmCameraInterface::Get3PTraceParameters_Implementation() {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmCameraInterface::Get3PTraceParameters_Implementation" ) );
	return FLmTraceParams();
}
