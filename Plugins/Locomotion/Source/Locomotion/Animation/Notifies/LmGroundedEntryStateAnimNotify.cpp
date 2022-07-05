#include "LmGroundedEntryStateAnimNotify.h"
#include "../LmCharacterAnimInstance.h"
#include "../../LmLogger.h"


void ULmGroundedEntryStateAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {

	if (IsValid(MeshComp)) {
		if (MeshComp->GetClass()->ImplementsInterface(ULmCharacterAnimationInterface::StaticClass())) {
			ILmCharacterAnimationInterface::Execute_SetGroundedEntryState(MeshComp->GetAnimInstance(), GroundedEntryState);
		}
	}
}

FString ULmGroundedEntryStateAnimNotify::GetNotifyName_Implementation() const {
	return FString::Printf(TEXT("#Grounded Entry State: %s"), *UEnum::GetDisplayValueAsText(GroundedEntryState).ToString());
}