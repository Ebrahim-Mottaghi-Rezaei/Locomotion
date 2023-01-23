#include "LmHoldingObjectInterface.h"
#include <Locomotion/LmLogger.h>

// Add default functionality here for any ILmHoldingObjectInterface functions that are not pure virtual.

void ILmHoldingObjectInterface::SetParent_Implementation(APawn* owner) {
	ULmLogger::LogError(TEXT("Invalid interface method called. ILmHoldingObjectInterface::SetParent_Implementation"));
}