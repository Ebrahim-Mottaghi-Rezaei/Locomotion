


#include "ALSOverlayStateSwitcherWidget.h"
#include "../ALSEnums.h"
#include <GameFramework/Character.h>
#include "../Gameplay/ALSCharacterInterface.h"
#include "../Gameplay/ALSCameraInterface.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include <Misc/EnumRange.h>
#include <UObject/NoExportTypes.h>
#include <Components/CanvasPanelSlot.h>
#include "ALSOverlayStateButtonWidget.h"
#include <Blueprint/UserWidget.h>
#include <Components/TextBlock.h>

void UALSOverlayStateSwitcherWidget::NativeOnInitialized() {
	for (const EALSOverlayState value : TEnumRange<EALSOverlayState>())
		OverlayStates.Add(value);
}

void UALSOverlayStateSwitcherWidget::NativeConstruct() {
	Super::NativeConstruct();

	auto* Character = GetOwningPlayer()->GetCharacter();
	if (Character->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
		NewOverlayState = IALSCharacterInterface::Execute_GetCurrentState(Character).OverlayState;

		if (VerticalBox->GetChildrenCount() == 0)
			CreateButtons();

		UpdateButtonFocus();
	}
}

void UALSOverlayStateSwitcherWidget::NativeTick(const FGeometry& MovieSceneBlends, float InDeltaTime) {
	Super::NativeTick(MovieSceneBlends, InDeltaTime);

	//local player controller
	const auto pc = GetOwningPlayer()->GetPawn();

	if (pc->GetClass()->ImplementsInterface(UALSCameraInterface::StaticClass())) {
		const FTransform transform = IALSCameraInterface::Execute_Get3PPivotTarget(pc);

		FVector2D screenpos;
		UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetOwningPlayer(), transform.GetLocation() + FVector(0, 0, 100), screenpos, false);
		UWidgetLayoutLibrary::SlotAsCanvasSlot(MovablePanels)->SetPosition(screenpos);
	}
}

void UALSOverlayStateSwitcherWidget::SelectOverlayState() const {
	auto* character = GetOwningPlayer()->GetCharacter();
	if (character->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
		IALSCharacterInterface::Execute_SetOverlayState(character, NewOverlayState);
	}
}

void UALSOverlayStateSwitcherWidget::CreateButtons() {
	//ALS_Barrel is the last element in the EALSOverlayState enum. if any other states added
	for (EALSOverlayState value : TEnumRange<EALSOverlayState>()) {
		const auto button = static_cast<UALSOverlayStateButtonWidget*>(CreateWidget(GetOwningPlayer(), OverlayStateButtonTemplate));
		button->GetText()->SetText(FText::FromString(UEnum::GetDisplayValueAsText(value).ToString()));
		VerticalBox->AddChildToVerticalBox(button);
		OverlayStateButtons.Add(FALSOverlayStateParams(button, value));
	}
}

void UALSOverlayStateSwitcherWidget::UpdateButtonFocus() {
	for (const auto element : OverlayStateButtons) {
		if (IsValid(element.Widget)) {
			element.Widget->SetVisualParameters(element.State == NewOverlayState);
		}
	}
}

void UALSOverlayStateSwitcherWidget::SetUIElements(UCanvasPanel* movablePanel, UVerticalBox* verticalBox) {
	MovablePanels = movablePanel;
	VerticalBox = verticalBox;
}

void UALSOverlayStateSwitcherWidget::CycleState(bool bUp) {
	if (bUp)
		selectedIndex = selectedIndex + 1 < OverlayStates.Num() ? selectedIndex + 1 : 0;
	else
		selectedIndex = selectedIndex - 1 >= 0 ? selectedIndex - 1 : OverlayStates.Num() - 1;

	NewOverlayState = OverlayStates[selectedIndex];

	UpdateButtonFocus();
}
