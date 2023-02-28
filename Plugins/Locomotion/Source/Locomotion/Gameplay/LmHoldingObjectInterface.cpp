#include "LmHoldingObjectInterface.h"
#include <Locomotion/LmLogger.h>

// Add default functionality here for any ILmHoldingObjectInterface functions that are not pure virtual.

void ILmHoldingObjectInterface::SetHoldingActor_Implementation(AActor* owner) {
	ULmLogger::LogError(TEXT("Invalid interface method called. ILmHoldingObjectInterface::SetHoldingActor_Implementation"));
}