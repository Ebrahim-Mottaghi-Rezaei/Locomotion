#include "ALSFootStepAnimNotify.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../../ALSLogger.h"
#include <Sound/SoundCue.h>

UALSFootStepAnimNotify::UALSFootStepAnimNotify() {
	static ConstructorHelpers::FObjectFinder<USoundCue> footStepSoundCue(TEXT("SoundCue'/CALSv4/Data/Footstep_Cue.Footstep_Cue'"));
	if (footStepSoundCue.Succeeded())
		Sound = footStepSoundCue.Object;
	else
		UALSLogger::LogError("ProxyMesh not found.");
}

void UALSFootStepAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	if (IsValid(MeshComp) && IsValid(MeshComp->GetAnimInstance()) && IsValid(Sound)) {
		auto* audioComp = UGameplayStatics::SpawnSoundAttached(Sound, MeshComp, AttachPointName, FVector(ForceInit), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false, VolumeMultiplier, PitchMultiplier);

		if (IsValid(audioComp)) {
			audioComp->SetIntParameter("FootstepType", static_cast<int>(FootStepType));
		}
	}
	/*else {
		UALSLogger::LogError(TEXT("UALSFootStepAnimNotify@Notify| Mesh Component,It's AnimationBlueprint or Selected Sound is null."));
	}*/
}

FString UALSFootStepAnimNotify::GetNotifyName_Implementation() const {
	return  FString::Printf(TEXT("#FootStep: %s"), *UEnum::GetDisplayValueAsText(FootStepType).ToString());
}
