#include "ALSGroundedEntryStateAnimNotify.h"
#include <CALSv4/Animation/ALSCharacterAnimInstance.h>
#include "../../ALSLogger.h"


void UALSGroundedEntryStateAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {

	if (IsValid(MeshComp)) {
		if (MeshComp->GetClass()->ImplementsInterface(UALSCharacterAnimationInterface::StaticClass())) {
			IALSCharacterAnimationInterface::Execute_SetGroundedEntryState(MeshComp->GetAnimInstance(), GroundedEntryState);
		}
	}
	/*else {
		UALSLogger::LogError(TEXT("UALSGroundedEntryStateAnimNotify@Notify| Mesh Component or It's Owner is null."));
	}*/
}

FString UALSGroundedEntryStateAnimNotify::GetNotifyName_Implementation() const {
	return FString::Printf(TEXT("#Grounded Entry State: %s"), *UEnum::GetDisplayValueAsText(GroundedEntryState).ToString());
}