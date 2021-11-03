#include "ALSEarlyBlendOut.h"
#include "CALSv4/Core/Interfaces/ALSCharacterInterface.h"

void UALSEarlyBlendOut::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) {
	AActor* owningActor = MeshComp->GetOwner();
	UAnimInstance* animInstance = MeshComp->GetAnimInstance();

	FALSCurrentState CurrentState;

	if (bCheckMovementState) {
		if (owningActor->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
			CurrentState = IALSCharacterInterface::Execute_GetCurrentState(owningActor);
			if (CurrentState.MovementState == MovementState) {
				animInstance->Montage_Stop(BlendOutTime, Montage);
				return;
			}
		}
	}

	if (bCheckMovementState) {
		if (owningActor->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
			CurrentState = IALSCharacterInterface::Execute_GetCurrentState(owningActor);
			if (CurrentState.ActualStance == Stance) {
				animInstance->Montage_Stop(BlendOutTime, Montage);
				return;
			}
		}
	}

	if (bCheckMovementInput) {
		if (owningActor->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
			const auto values = IALSCharacterInterface::Execute_GetEssentialValues(owningActor);
			if (values.bHasMovementInput) {
				animInstance->Montage_Stop(BlendOutTime, Montage);
				return;
			}
		}
	}
}

FString UALSEarlyBlendOut::GetNotifyName_Implementation() const {
	return TEXT("[C++ ALS] Early Blend Out");
}