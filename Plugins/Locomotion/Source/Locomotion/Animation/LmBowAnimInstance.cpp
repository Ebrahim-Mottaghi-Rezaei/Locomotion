#include "LmBowAnimInstance.h"
#include <GameFramework/Character.h>

void ULmBowAnimInstance::ChangeDraw(const float NewDraw) {
	Draw = NewDraw;
	OnBowDrawChanged.Broadcast(NewDraw);
}