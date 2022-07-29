#include "LmCameraShakeAnimNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequenceBase.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "../../LmLogger.h"
#include <Components/ActorComponent.h>
#include <GameFramework/Controller.h>

void ULmCameraShakeAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	if (IsValid(MeshComp) && IsValid(MeshComp->GetOwner())) {
		auto pawn = Cast<APawn>(MeshComp->GetOwner());
		if (IsValid(pawn)) {
			const auto controller = Cast<APlayerController>(pawn->GetController());
			if (IsValid(controller)) {
				controller->ClientStartCameraShake(CameraShake, Scale);;
			}
		}
	}
}

FString ULmCameraShakeAnimNotify::GetNotifyName_Implementation() const {
	return TEXT("#CameraShake");
}