#include "ALSCameraShake.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequenceBase.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

void UALSCameraShake::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	if (!::IsValid(MeshComp->GetOwner())) return;

	auto player = Cast<APawn>(MeshComp->GetOwner());
	if (!::IsValid(player))
		return;

	Cast<APlayerController>(player)->ClientStartCameraShake(CameraShake, Scale);
}