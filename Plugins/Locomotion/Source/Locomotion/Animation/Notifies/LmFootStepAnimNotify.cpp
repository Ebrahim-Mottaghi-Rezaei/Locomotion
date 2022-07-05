#include "LmFootStepAnimNotify.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../../LmLogger.h"
#include <Sound/SoundCue.h>

ULmFootStepAnimNotify::ULmFootStepAnimNotify() {
	static ConstructorHelpers::FObjectFinder<USoundCue> footStepSoundCue(TEXT("SoundCue'/Game/AdvancedLocomotionV4/Audio/Footsteps/Footstep_Cue.Footstep_Cue'"));
	if (footStepSoundCue.Succeeded())
		Sound = footStepSoundCue.Object;
	else
		ULmLogger::LogError("UALSFootStepAnimNotify | SoundCue not found.");
}

void ULmFootStepAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	if (IsValid(MeshComp) && IsValid(MeshComp->GetAnimInstance()) && IsValid(Sound)) {
		auto* audioComp = UGameplayStatics::SpawnSoundAttached(Sound, MeshComp, AttachPointName, FVector(ForceInit), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false, VolumeMultiplier, PitchMultiplier);

		if (IsValid(audioComp)) {
			audioComp->SetIntParameter("FootstepType", static_cast<int>(FootStepType));
		}
	}
}

FString ULmFootStepAnimNotify::GetNotifyName_Implementation() const {
	return  FString::Printf(TEXT("#FootStep: %s"), *UEnum::GetDisplayValueAsText(FootStepType).ToString());
}
