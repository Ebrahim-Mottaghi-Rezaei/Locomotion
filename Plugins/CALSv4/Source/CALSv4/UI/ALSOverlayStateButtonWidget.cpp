


#include "ALSOverlayStateButtonWidget.h"
#include <Components/TextBlock.h>
#include <Components/Image.h>

void UALSOverlayStateButtonWidget::SetUIElements(UImage* background, UTextBlock* text) {
	Background = background;
	Text = text;
}

void UALSOverlayStateButtonWidget::SetVisualParameters(const bool bIsSelected) {
	Text->SetColorAndOpacity(bIsSelected ? TextSelectedColor : TextUnSelectedColor);
	Background->SetColorAndOpacity(bIsSelected ? BackgroundSelectedColor : BackgroundUnSelectedColor);
}

UImage* UALSOverlayStateButtonWidget::GetBackground() {
	return Background;
}

UTextBlock* UALSOverlayStateButtonWidget::GetText() {
	return Text;
}