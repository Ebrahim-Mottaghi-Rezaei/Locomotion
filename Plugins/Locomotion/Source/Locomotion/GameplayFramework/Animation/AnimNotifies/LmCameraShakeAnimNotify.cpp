#include "LmCameraShakeAnimNotify.h"
#include "Animation/AnimSequenceBase.h"
#include "Components/ActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Math/Color.h"


ULmCameraShakeAnimNotify::ULmCameraShakeAnimNotify() {
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor::White;
#endif
}


void ULmCameraShakeAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	if ( !IsValid( MeshComp ) || !IsValid( MeshComp->GetOwner() ) )
		return;

	const auto Pawn = Cast<APawn>( MeshComp->GetOwner() );
	if ( !IsValid( Pawn ) )
		return;

	const auto Controller = Cast<APlayerController>( Pawn->GetController() );
	if ( !IsValid( Controller ) )
		return;

	Controller->ClientStartCameraShake( CameraShake , Scale );
}


FString ULmCameraShakeAnimNotify::GetNotifyName_Implementation() const {
	return TEXT( "CameraShake" );
}
