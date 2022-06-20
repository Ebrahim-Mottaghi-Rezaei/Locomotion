


#include "ALSControllerInterface.h"
#include "../ALSLogger.h"

// Add default functionality here for any IALSControllerInterface functions that are not pure virtual.

FALSDebugInfo IALSControllerInterface::GetDebugInfo_Implementation() {
	UALSLogger::LogError(TEXT("Invalid interface method calling. IALSControllerInterface::GetDebugInfo_Implementation"));
	return FALSDebugInfo();
}