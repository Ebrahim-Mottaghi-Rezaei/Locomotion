#include "ALSGroundedEntryStateAnimNotify.h"

#include "CALSv4/Core/Interfaces/ALSAnimationInterface.h"

void UALSGroundedEntryStateAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	IALSAnimationInterface::Execute_SetGroundedEntryState(MeshComp->GetAnimInstance(), GroundedEntryState);
}

FString UALSGroundedEntryStateAnimNotify::GetNotifyName_Implementation() const {
	return FString::Printf(TEXT("[C++ ALS] Grounded Entry State: %s"), *UEnum::GetValueAsString(GroundedEntryState));
}