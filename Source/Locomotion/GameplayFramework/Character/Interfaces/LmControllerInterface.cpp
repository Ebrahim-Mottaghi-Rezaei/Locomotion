#include "LmControllerInterface.h"
#include "Locomotion/Logging/LMLogger.h"

// Add default functionality here for any ILmControllerInterface functions that are not pure virtual.

FLmDebugInfo ILmControllerInterface::GetDebugInfo_Implementation() {
	ULmLogger::LogError( TEXT( "Invalid interface method calling. ILmControllerInterface::GetDebugInfo_Implementation" ) );
	return FLmDebugInfo();
}
