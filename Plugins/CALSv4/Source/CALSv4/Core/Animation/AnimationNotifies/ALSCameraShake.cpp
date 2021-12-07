#include "ALSCameraShake.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequenceBase.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

void UALSCameraShake::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	if (!MeshComp->GetOwner())
		return;

	const auto player = Cast<APawn>(MeshComp->GetOwner());
	if (player)
		Cast<APlayerController>(player)->ClientStartCameraShake(CameraShake, Scale);
}