#include "LmEarlyBlendOut.h"
#include "Locomotion/GameplayFramework/Character/Interfaces/LmCharacterInterface.h"


FString ULmEarlyBlendOut::GetNotifyName_Implementation() const {
	return TEXT( "Early Blend Out" );
}


ULmEarlyBlendOut::ULmEarlyBlendOut() {
	NotifyColor = FColor::FromHex( TEXT( "24FF25FF" ) );
}


void ULmEarlyBlendOut::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) {
	if ( !IsValid( MeshComp ) )
		return;

	const auto OwningActor  = MeshComp->GetOwner();
	const auto AnimInstance = MeshComp->GetAnimInstance();

	if ( !IsValid( OwningActor ) || !IsValid( AnimInstance ) || !MeshComp->GetAnimInstance()->GetClass()->ImplementsInterface( ULmCharacterInterface::StaticClass() ) )
		return;

	const auto CurrentState    = ILmCharacterInterface::Execute_GetCurrentState( OwningActor );
	const auto EssentialValues = ILmCharacterInterface::Execute_GetEssentialValues( OwningActor );

	if ( bCheckMovementInput && EssentialValues.bHasMovementInput || bCheckMovementState && MovementState == CurrentState.MovementState || bCheckStance && CurrentState.ActualStance == Stance )
		AnimInstance->Montage_Stop( BlendOutTime , Montage );
}
