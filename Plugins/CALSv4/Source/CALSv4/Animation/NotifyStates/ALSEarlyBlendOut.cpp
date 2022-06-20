#include "ALSEarlyBlendOut.h"
#include "../../Gameplay/ALSCharacterInterface.h"
#include "../../ALSLogger.h"

FString UALSEarlyBlendOut::GetNotifyName_Implementation() const {
	return TEXT("#Early Blend Out");
}

void UALSEarlyBlendOut::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) {
	AActor* owningActor = MeshComp->GetOwner();
	UAnimInstance* animInstance = MeshComp->GetAnimInstance();

	if (!IsValid(MeshComp) || !IsValid(owningActor) || !IsValid(animInstance)) {
		//UALSLogger::LogError(TEXT("UALSEarlyBlendOut@NotifyTick| Mesh Component,it's Owner or it's AnimationBlueprint is null."));
		return;
	}

	if (owningActor->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
		const auto CurrentState = IALSCharacterInterface::Execute_GetCurrentState(owningActor);

		if ((bCheckMovementState && CurrentState.MovementState == MovementState) || (bCheckStance && Stance == CurrentState.ActualStance)) {
			animInstance->Montage_Stop(BlendOutTime, Montage);
			return;
		}

		const auto EssentialValues = IALSCharacterInterface::Execute_GetEssentialValues(owningActor);
		if (bCheckMovementInput && EssentialValues.bHasMovementInput) {
			animInstance->Montage_Stop(BlendOutTime, Montage);
			return;
		}
	}
}
