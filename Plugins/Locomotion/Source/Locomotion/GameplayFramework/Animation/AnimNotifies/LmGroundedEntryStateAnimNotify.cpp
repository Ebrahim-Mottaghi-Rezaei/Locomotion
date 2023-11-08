#include "LmGroundedEntryStateAnimNotify.h"
#include "Locomotion/GameplayFramework/Animation/Interfaces/LmCharacterAnimationInterface.h"


void ULmGroundedEntryStateAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	if ( !IsValid( MeshComp ) )
		return;
	if ( MeshComp->GetAnimInstance()->GetClass()->ImplementsInterface( ULmCharacterAnimationInterface::StaticClass() ) )
		ILmCharacterAnimationInterface::Execute_SetGroundedEntryState( MeshComp->GetAnimInstance() , GroundedEntryState );
}


FString ULmGroundedEntryStateAnimNotify::GetNotifyName_Implementation() const {
	return FString::Printf( TEXT( "%s" ) , *UEnum::GetDisplayValueAsText( GroundedEntryState ).ToString() );
}
