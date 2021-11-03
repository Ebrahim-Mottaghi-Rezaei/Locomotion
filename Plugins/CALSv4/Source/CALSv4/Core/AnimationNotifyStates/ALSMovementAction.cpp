#include "ALSMovementAction.h"
#include "CALSv4/Core/Interfaces/ALSCharacterInterface.h"
#include "CALSv4/Core/Utilities/ALSDebug.h"

FString UALSMovementAction::GetNotifyName_Implementation() const {
	return  FString::Printf(TEXT("MovementAction: %s"), *UEnum::GetValueAsString(MovementAction));
}

void UALSMovementAction::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (IsValid(MeshComp) && IsValid(MeshComp->GetOwner())) {
		if (MeshComp->GetOwner()->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
			IALSCharacterInterface::Execute_SetMovementAction(MeshComp->GetAnimInstance(), MovementAction);
		}
	} else {
		ALSDebug::LogError(TEXT("Mesh Component or It's Owner is null."));
	}
}

void UALSMovementAction::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::NotifyEnd(MeshComp, Animation);
	if (!IsValid(MeshComp) || !IsValid(MeshComp->GetOwner())) {
		if (MeshComp->GetOwner()->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
			if (IALSCharacterInterface::Execute_GetCurrentState(MeshComp->GetOwner()).MovementAction == MovementAction) {
				IALSCharacterInterface::Execute_SetMovementAction(MeshComp->GetOwner(), EALSMovementAction::ALS_None);
			}
		}
	} else {
		ALSDebug::LogError(TEXT("Mesh Component or It's Owner is null."));
	}
}