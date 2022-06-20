#include "ALSBowAnimInstance.h"

void UALSBowAnimInstance::ChangeDraw(const float NewDraw) {
	Draw = NewDraw;
	OnBowDrawChanged.Broadcast(NewDraw);
}