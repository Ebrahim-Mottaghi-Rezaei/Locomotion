#include "ALSCameraShakeAnimNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequenceBase.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

void UALSCameraShakeAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	if (!IsValid(MeshComp->GetOwner())) return;

	const auto player = Cast<APawn>(MeshComp->GetOwner());
	if (!IsValid(player))
		return;

	Cast<APlayerController>(player)->ClientStartCameraShake(CameraShake, Scale);
}