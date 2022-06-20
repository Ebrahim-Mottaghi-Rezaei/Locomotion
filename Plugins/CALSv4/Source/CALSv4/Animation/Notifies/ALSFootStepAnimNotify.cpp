#include "ALSFootStepAnimNotify.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void UALSFootStepAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	if (!IsValid(MeshComp) || !IsValid(MeshComp->GetAnimInstance()) || IsValid(Sound))
		return;

	auto * audioComp = UGameplayStatics::SpawnSoundAttached(Sound, MeshComp, AttachPointName, FVector(ForceInit), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false, VolumeMultiplier, PitchMultiplier);

	if (IsValid(audioComp)) {
		audioComp->SetIntParameter("FootstepType", static_cast<int>(FootStepType));
	}
}