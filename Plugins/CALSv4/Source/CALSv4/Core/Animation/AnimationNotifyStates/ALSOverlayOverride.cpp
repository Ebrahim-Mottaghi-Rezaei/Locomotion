#include "ALSOverlayOverride.h"
#include "CALSv4/Core/Interfaces/ALSAnimationInterface.h"
#include "CALSv4/Core/Utilities/ALSHelpers.h"

FString UALSOverlayOverride::GetNotifyName_Implementation() const {
	return  FString::Printf(TEXT("Overlay Override State: %d"), OverlayOverriderState);
}

void UALSOverlayOverride::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration) {
	if (IsValid(MeshComp) && IsValid(MeshComp->GetAnimInstance())) {
		if (MeshComp->GetAnimInstance()->GetClass()->ImplementsInterface(UALSAnimationInterface::StaticClass())) {
			IALSAnimationInterface::Execute_SetOverlayOverrideState(MeshComp->GetAnimInstance(), OverlayOverriderState);
		}
	} else {
		UALSLogger::LogError(TEXT("Mesh Component or It's Anim Instance is null."));
	}
}

void UALSOverlayOverride::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	if (IsValid(MeshComp) && IsValid(MeshComp->GetAnimInstance())) {
		if (MeshComp->GetAnimInstance()->GetClass()->ImplementsInterface(UALSAnimationInterface::StaticClass())) {
			IALSAnimationInterface::Execute_SetOverlayOverrideState(MeshComp->GetAnimInstance(), 0);
		}
	} else {
		UALSLogger::LogError(TEXT("Mesh Component or It's Anim Instance is null."));
	}
}