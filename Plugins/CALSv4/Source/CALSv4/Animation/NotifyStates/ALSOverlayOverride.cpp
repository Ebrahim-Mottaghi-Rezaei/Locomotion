#include "ALSOverlayOverride.h"

#include "../../ALSLogger.h"
#include "../ALSCharacterAnimationInterface.h"

FString UALSOverlayOverride::GetNotifyName_Implementation() const {
	return  FString::Printf(TEXT("#Overlay Override State: %d"), OverlayOverriderState);
}

void UALSOverlayOverride::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) {
	if (IsValid(MeshComp) && IsValid(MeshComp->GetAnimInstance())) {
		if (MeshComp->GetAnimInstance()->GetClass()->ImplementsInterface(UALSCharacterAnimationInterface::StaticClass())) {
			IALSCharacterAnimationInterface::Execute_SetOverlayOverrideState(MeshComp->GetAnimInstance(), OverlayOverriderState);
		}
	}
	/*else {
		UALSLogger::LogError(TEXT("Mesh Component or It's Anim Instance is null."));
	}*/
}

void UALSOverlayOverride::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	if (IsValid(MeshComp) && IsValid(MeshComp->GetAnimInstance())) {
		if (MeshComp->GetAnimInstance()->GetClass()->ImplementsInterface(UALSCharacterAnimationInterface::StaticClass())) {
			IALSCharacterAnimationInterface::Execute_SetOverlayOverrideState(MeshComp->GetAnimInstance(), 0);
		}
	}
	/*else {
		UALSLogger::LogError(TEXT("Mesh Component or It's Anim Instance is null."));
	}*/
}
