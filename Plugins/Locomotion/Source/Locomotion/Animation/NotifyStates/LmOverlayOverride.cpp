#include "LmOverlayOverride.h"
#include "../../LmLogger.h"
#include "../LmCharacterAnimationInterface.h"

FString ULmOverlayOverride::GetNotifyName_Implementation() const {
	return  FString::Printf(TEXT("#Overlay Override State: %d"), OverlayOverriderState);
}

void ULmOverlayOverride::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	if (IsValid(MeshComp) && IsValid(MeshComp->GetAnimInstance())) {
		if (MeshComp->GetAnimInstance()->GetClass()->ImplementsInterface(ULmCharacterAnimationInterface::StaticClass())) {
			ILmCharacterAnimationInterface::Execute_SetOverlayOverrideState(MeshComp->GetAnimInstance(), OverlayOverriderState);
		}
	}
}

void ULmOverlayOverride::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	if (IsValid(MeshComp) && IsValid(MeshComp->GetAnimInstance())) {
		if (MeshComp->GetAnimInstance()->GetClass()->ImplementsInterface(ULmCharacterAnimationInterface::StaticClass())) {
			ILmCharacterAnimationInterface::Execute_SetOverlayOverrideState(MeshComp->GetAnimInstance(), 0);
		}
	}
}
