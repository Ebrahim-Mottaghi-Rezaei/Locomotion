#include "LmMovementAction.h"
#include <Animation/AnimNotifyQueue.h>
#include <Animation/AnimSequenceBase.h>
#include "Locomotion/GameplayFramework/Character/Interfaces/LmCharacterInterface.h"


FString ULmMovementAction::GetNotifyName_Implementation() const {
	return FString::Printf( TEXT( "Movement Action: %s" ) , *UEnum::GetDisplayValueAsText( MovementAction ).ToString() );
}


ULmMovementAction::ULmMovementAction() {
	NotifyColor = FColor::FromHex( TEXT( "FFCC16FF" ) );
}


void ULmMovementAction::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) {
	Super::NotifyBegin( MeshComp , Animation , TotalDuration , EventReference );
	if ( !IsValid( MeshComp ) || !IsValid( MeshComp->GetOwner() ) || !MeshComp->GetAnimInstance()->GetClass()->ImplementsInterface( ULmCharacterInterface::StaticClass() ) )
		return;

	ILmCharacterInterface::Execute_SetMovementAction( MeshComp->GetOwner() , MovementAction );
}


void ULmMovementAction::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	Super::NotifyEnd( MeshComp , Animation , EventReference );

	if ( !IsValid( MeshComp ) || !IsValid( MeshComp->GetOwner() ) || !MeshComp->GetAnimInstance()->GetClass()->ImplementsInterface( ULmCharacterInterface::StaticClass() ) )
		return;

	const auto MeshOwner = MeshComp->GetOwner();
	if ( ILmCharacterInterface::Execute_GetCurrentState( MeshOwner ).MovementAction == MovementAction )
		ILmCharacterInterface::Execute_SetMovementAction( MeshOwner , ELmMovementAction::Lm_None );
}
