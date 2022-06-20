#include "ALSMovementAction.h"
#include "../../Gameplay/ALSCharacterInterface.h"
#include "../../ALSLogger.h"
#include "../../ALSEnums.h"
#include <Animation/AnimSequenceBase.h>
#include <Animation/AnimNotifyQueue.h>

FString UALSMovementAction::GetNotifyName_Implementation() const {
	return  FString::Printf(TEXT("#Movement Action: %s"), *UEnum::GetDisplayValueAsText(MovementAction).ToString());
}

void UALSMovementAction::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) {
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (IsValid(MeshComp) && IsValid(MeshComp->GetOwner())) {
		if (MeshComp->GetOwner()->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
			IALSCharacterInterface::Execute_SetMovementAction(MeshComp->GetOwner(), MovementAction);
		}
	}
	/*else {
		UALSLogger::LogError(TEXT("UALSMovementAction@NotifyBegin| Mesh Component or It's Owner is null."));
	}*/
}

void UALSMovementAction::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (IsValid(MeshComp) && IsValid(MeshComp->GetOwner())) {
		if (MeshComp->GetOwner()->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
			if (IALSCharacterInterface::Execute_GetCurrentState(MeshComp->GetOwner()).MovementAction == MovementAction) {
				IALSCharacterInterface::Execute_SetMovementAction(MeshComp->GetOwner(), EALSMovementAction::ALS_None);
			}
		}
	}
	/*else {
		UALSLogger::LogError(TEXT("UALSMovementAction@NotifyEnd| Mesh Component or It's Owner is null."));
	}*/
}