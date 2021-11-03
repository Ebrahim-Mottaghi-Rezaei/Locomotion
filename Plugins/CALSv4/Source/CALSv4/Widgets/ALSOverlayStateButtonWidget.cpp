#include "ALSOverlayStateButtonWidget.h"

void UALSOverlayStateButtonWidget::SetVisualParameters(bool bIsSelected) {
	Text->SetColorAndOpacity(bIsSelected ? TextSelectedColor : TextUnSelectedColor);
	Background->SetColorAndOpacity(bIsSelected ? BackgroundSelectedColor : BackgroundUnSelectedColor);
}