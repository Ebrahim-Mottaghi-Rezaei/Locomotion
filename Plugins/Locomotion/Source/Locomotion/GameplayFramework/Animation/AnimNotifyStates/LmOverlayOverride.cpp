#include "LmOverlayOverride.h"
#include "Locomotion/GameplayFramework/Animation/Interfaces/LmCharacterAnimationInterface.h"


ULmOverlayOverride::ULmOverlayOverride() {
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor::FromHex( TEXT( "00BCFFFF" ) );
#endif
}


FString ULmOverlayOverride::GetNotifyName_Implementation() const {
	return FString::Printf( TEXT( "Overlay Override State: %d" ) , OverlayOverriderState );
}


void ULmOverlayOverride::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) {
	if ( !IsValid( MeshComp ) || !IsValid( MeshComp->GetAnimInstance() ) || !MeshComp->GetAnimInstance()->GetClass()->ImplementsInterface( ULmCharacterAnimationInterface::StaticClass() ) )
		return;

	ILmCharacterAnimationInterface::Execute_SetOverlayOverrideState( MeshComp->GetAnimInstance() , OverlayOverriderState );
}


void ULmOverlayOverride::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	if ( !IsValid( MeshComp ) || !IsValid( MeshComp->GetAnimInstance() ) || !MeshComp->GetAnimInstance()->GetClass()->ImplementsInterface( ULmCharacterAnimationInterface::StaticClass() ) )
		return;

	ILmCharacterAnimationInterface::Execute_SetOverlayOverrideState( MeshComp->GetAnimInstance() , 0 );
}
