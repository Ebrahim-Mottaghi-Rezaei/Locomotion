#include "LmBowAnimInstance.h"
#include <GameFramework/Character.h>


ULmBowAnimInstance::ULmBowAnimInstance() {
	RootMotionMode = ERootMotionMode::NoRootMotionExtraction;
}


void ULmBowAnimInstance::ChangeDraw(const float NewDraw) {
	Draw = NewDraw;
	OnBowDrawChanged.Broadcast( NewDraw );
}
