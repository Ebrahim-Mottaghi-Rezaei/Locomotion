#include "LmEarlyBlendOut.h"
#include "../../Gameplay/LmCharacterInterface.h"
#include "../../LmLogger.h"

FString ULmEarlyBlendOut::GetNotifyName_Implementation() const {
	return TEXT("#Early Blend Out");
}

void ULmEarlyBlendOut::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) {
	AActor* owningActor = MeshComp->GetOwner();
	UAnimInstance* animInstance = MeshComp->GetAnimInstance();

	if (!IsValid(MeshComp) || !IsValid(owningActor) || !IsValid(animInstance)) {
		return;
	}

	if (owningActor->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass())) {
		const auto CurrentState = ILmCharacterInterface::Execute_GetCurrentState(owningActor);

		if ((bCheckMovementState && CurrentState.MovementState == MovementState) || (bCheckStance && Stance == CurrentState.ActualStance)) {
			animInstance->Montage_Stop(BlendOutTime, Montage);
			return;
		}

		const auto EssentialValues = ILmCharacterInterface::Execute_GetEssentialValues(owningActor);
		if (bCheckMovementInput && EssentialValues.bHasMovementInput) {
			animInstance->Montage_Stop(BlendOutTime, Montage);
			return;
		}
	}
}
