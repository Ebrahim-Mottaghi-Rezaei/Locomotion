#include "LmWOverlayStateButton.h"
#include <Components/TextBlock.h>
#include <Components/Image.h>

void ULmWOverlayStateButton::SetUIElements(UImage* background, UTextBlock* text) {
	Background = background;
	Text = text;
}

void ULmWOverlayStateButton::SetVisualParameters(const bool bIsSelected) {
	Text->SetColorAndOpacity(bIsSelected ? TextSelectedColor : TextUnSelectedColor);
	Background->SetColorAndOpacity(bIsSelected ? BackgroundSelectedColor : BackgroundUnSelectedColor);
}

UImage* ULmWOverlayStateButton::GetBackground() {
	return Background;
}

UTextBlock* ULmWOverlayStateButton::GetText() {
	return Text;
}