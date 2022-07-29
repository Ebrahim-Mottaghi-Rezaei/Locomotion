#include "LmMovementAction.h"
#include "../../Gameplay/LmCharacterInterface.h"
#include "../../LmLogger.h"
#include "../../LmEnums.h"
#include <Animation/AnimSequenceBase.h>
#include <Animation/AnimNotifyQueue.h>

FString ULmMovementAction::GetNotifyName_Implementation() const {
	return  FString::Printf(TEXT("#Movement Action: %s"), *UEnum::GetDisplayValueAsText(MovementAction).ToString());
}

void ULmMovementAction::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (IsValid(MeshComp) && IsValid(MeshComp->GetOwner())) {
		if (MeshComp->GetOwner()->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass())) {
			ILmCharacterInterface::Execute_SetMovementAction(MeshComp->GetOwner(), MovementAction);
		}
	}
}

void ULmMovementAction::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::NotifyEnd(MeshComp, Animation);

	if (IsValid(MeshComp) && IsValid(MeshComp->GetOwner())) {
		if (MeshComp->GetOwner()->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass())) {
			if (ILmCharacterInterface::Execute_GetCurrentState(MeshComp->GetOwner()).MovementAction == MovementAction) {
				ILmCharacterInterface::Execute_SetMovementAction(MeshComp->GetOwner(), ELmMovementAction::Lm_None);
			}
		}
	}
}