#include "LmWOverlayStateSwitcher.h"
#include "../LmEnums.h"
#include "LmWOverlayStateButton.h"
#include "../Gameplay/LmCameraInterface.h"
#include "../Gameplay/LmCharacterInterface.h"

#include <Misc/EnumRange.h>
#include <Blueprint/UserWidget.h>
#include <Components/TextBlock.h>
#include <UObject/NoExportTypes.h>
#include <GameFramework/Character.h>
#include <Components/CanvasPanelSlot.h>
#include "Blueprint/WidgetLayoutLibrary.h"

void ULmWOverlayStateSwitcher::NativeOnInitialized() {
	for (const ELmOverlayState value : TEnumRange<ELmOverlayState>())
		OverlayStates.Add(value);
}

void ULmWOverlayStateSwitcher::NativeConstruct() {
	Super::NativeConstruct();

	auto* Character = GetOwningPlayer()->GetCharacter();
	if (Character->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass())) {
		NewOverlayState = ILmCharacterInterface::Execute_GetCurrentState(Character).OverlayState;

		if (VerticalBox->GetChildrenCount() == 0)
			CreateButtons();

		UpdateButtonFocus();
	}
}

void ULmWOverlayStateSwitcher::NativeTick(const FGeometry& MovieSceneBlends, const float InDeltaTime) {
	Super::NativeTick(MovieSceneBlends, InDeltaTime);

	//local player controller
	const auto pc = GetOwningPlayer()->GetPawn();

	if (pc->GetClass()->ImplementsInterface(ULmCameraInterface::StaticClass())) {
		const FTransform transform = ILmCameraInterface::Execute_Get3PPivotTarget(pc);

		FVector2D screenpos;
		UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetOwningPlayer(), transform.GetLocation() + FVector(0, 0, 100), screenpos, false);
		UWidgetLayoutLibrary::SlotAsCanvasSlot(MovablePanels)->SetPosition(screenpos);
	}
}

void ULmWOverlayStateSwitcher::SelectOverlayState() const {
	auto* character = GetOwningPlayer()->GetCharacter();
	if (character->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass())) {
		ILmCharacterInterface::Execute_SetOverlayState(character, NewOverlayState);
	}
}

void ULmWOverlayStateSwitcher::CreateButtons() {
	//Lm_Barrel is the last element in the ELmOverlayState enum. if any other states added
	for ( const ELmOverlayState value : TEnumRange<ELmOverlayState>()) {
		const auto button = static_cast<ULmWOverlayStateButton*>(CreateWidget(GetOwningPlayer(), OverlayStateButtonTemplate));
		button->GetText()->SetText(FText::FromString(UEnum::GetDisplayValueAsText(value).ToString()));
		VerticalBox->AddChildToVerticalBox(button);
		OverlayStateButtons.Add(FLmOverlayStateParams(button, value));
	}
}

void ULmWOverlayStateSwitcher::UpdateButtonFocus() {
	for (const auto element : OverlayStateButtons) {
		if (IsValid(element.Widget)) {
			element.Widget->SetVisualParameters(element.State == NewOverlayState);
		}
	}
}

void ULmWOverlayStateSwitcher::SetUIElements(UCanvasPanel* movablePanel, UVerticalBox* verticalBox) {
	MovablePanels = movablePanel;
	VerticalBox = verticalBox;
}

void ULmWOverlayStateSwitcher::CycleState(const bool bUp) {
	if (bUp)
		selectedIndex = selectedIndex + 1 < OverlayStates.Num() ? selectedIndex + 1 : 0;
	else
		selectedIndex = selectedIndex - 1 >= 0 ? selectedIndex - 1 : OverlayStates.Num() - 1;

	NewOverlayState = OverlayStates[selectedIndex];

	UpdateButtonFocus();
}
