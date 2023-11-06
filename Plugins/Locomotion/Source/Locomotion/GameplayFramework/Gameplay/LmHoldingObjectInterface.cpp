#include "LmHoldingObjectInterface.h"
#include "Locomotion/Logging/LMLogger.h"

void ILmHoldingObjectInterface::SetHoldingActor_Implementation(AActor* owner) {
	ULmLogger::LogError(TEXT("Invalid interface method called. ILmHoldingObjectInterface::SetHoldingActor_Implementation"));
}