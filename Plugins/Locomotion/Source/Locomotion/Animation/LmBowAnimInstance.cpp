#include "LmBowAnimInstance.h"

void ULmBowAnimInstance::ChangeDraw(const float NewDraw) {
	Draw = NewDraw;
	OnBowDrawChanged.Broadcast(NewDraw);
}