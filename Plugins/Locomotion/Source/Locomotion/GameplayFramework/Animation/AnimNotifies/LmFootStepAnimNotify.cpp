#include "LmFootStepAnimNotify.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Locomotion/Logging/LMLogger.h"
#include "Sound/SoundCue.h"


ULmFootStepAnimNotify::ULmFootStepAnimNotify() {
	bOverrideMaskCurve = false;
	NotifyColor        = FColor::FromHex( TEXT( "E56300FF" ) );

	static ConstructorHelpers::FObjectFinder<USoundCue> FootStepSoundCue( TEXT( "/Script/Engine.SoundCue'/Locomotion/Audio/Footsteps/Footstep_Cue.Footstep_Cue'" ) );
	if ( FootStepSoundCue.Succeeded() )
		Sound = FootStepSoundCue.Object;
	else
		ULmLogger::LogError( "ULmFootStepAnimNotify: SoundCue not found." );
}


void ULmFootStepAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	if ( !IsValid( MeshComp ) || !IsValid( MeshComp->GetAnimInstance() ) || !IsValid( Sound ) )
		return;

	if ( !bOverrideMaskCurve ) {
		VolumeMultiplier *= 1.0 - MeshComp->GetAnimInstance()->GetCurveValue( TEXT( "Mask_FootstepSound" ) );
	}

	const auto AudioComp = UGameplayStatics::SpawnSoundAttached( Sound ,
	                                                             MeshComp ,
	                                                             AttachPointName ,
	                                                             FVector::ZeroVector ,
	                                                             FRotator::ZeroRotator ,
	                                                             EAttachLocation::KeepRelativeOffset ,
	                                                             true ,
	                                                             VolumeMultiplier ,
	                                                             PitchMultiplier );

	if ( IsValid( AudioComp ) ) {
		AudioComp->SetIntParameter( "FootstepType" , static_cast<int>(FootStepType) );
	}
}


FString ULmFootStepAnimNotify::GetNotifyName_Implementation() const {
	return FString::Printf( TEXT( "FootStep: %s" ) , *UEnum::GetDisplayValueAsText( FootStepType ).ToString() );
}
