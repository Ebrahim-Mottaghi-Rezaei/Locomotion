#include "ALSCameraShakeAnimNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequenceBase.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "../../ALSLogger.h"

void UALSCameraShakeAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	if (IsValid(MeshComp) && IsValid(MeshComp->GetOwner())) {
		auto pawn = Cast<APawn>(MeshComp->GetOwner());
		if (IsValid(pawn)) {
			Cast<APlayerController>(pawn->GetController())->ClientStartCameraShake(CameraShake, Scale);
		}
	}
	/*else {
		UALSLogger::LogError(TEXT("UALSCameraShake@Notify| Mesh Component or it's owner is null."));
	}*/
}

FString UALSCameraShakeAnimNotify::GetNotifyName_Implementation() const {
	return TEXT("#CameraShake");
}