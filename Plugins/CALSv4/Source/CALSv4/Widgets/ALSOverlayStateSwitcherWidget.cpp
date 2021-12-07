#include "ALSOverlayStateSwitcherWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "CALSv4/Core/Interfaces/ALSCameraInterface.h"
#include "CALSv4/Core/Interfaces/ALSCharacterInterface.h"
#include "Components/CanvasPanelSlot.h"

void UALSOverlayStateSwitcherWidget::NativeConstruct() {
	Super::NativeConstruct();

	if (GetOwningPlayer()->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
		NewOverlayState = IALSCharacterInterface::Execute_GetCurrentState(GetOwningPlayer()).OverlayState;
		CreateButtons();
		UpdateButtonFocus();
	}
}

void UALSOverlayStateSwitcherWidget::NativeTick(const FGeometry& MovieSceneBlends, float InDeltaTime) {
	Super::NativeTick(MovieSceneBlends, InDeltaTime);

	//local player controller
	const auto pc = GetOwningPlayer();

	if (GetOwningPlayer()->GetClass()->ImplementsInterface(UALSCameraInterface::StaticClass())) {
		const FTransform transform = IALSCameraInterface::Execute_Get3PPivotTarget(GetOwningPlayer());

		FVector2D screenpos;
		UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(pc, transform.GetLocation() + FVector(0, 0, 100), screenpos, false);
		UWidgetLayoutLibrary::SlotAsCanvasSlot(MovablePanels)->SetPosition(screenpos);
	}

}

void UALSOverlayStateSwitcherWidget::SelectOverlayState() const {
	if (GetOwningPlayer()->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
		IALSCharacterInterface::Execute_SetOverlayState(GetOwningPlayer(), NewOverlayState);
	}
}

void UALSOverlayStateSwitcherWidget::CreateButtons() {
	//ALS_Barrel is the last element in the EALSOverlayState enum. if any other states added
	for (const EALSOverlayState value : TEnumRange<EALSOverlayState>()) {
		const auto button = static_cast<UALSOverlayStateButtonWidget*>(CreateWidget(GetOwningPlayer(), UALSOverlayStateButtonWidget::StaticClass()));
		button->GetText()->SetText(FText::FromString(*UEnum::GetValueAsString(value)));
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

void UALSOverlayStateSwitcherWidget::SetVerticalBox(UVerticalBox* verticalBox) {
	VerticalBox = verticalBox;
}

void UALSOverlayStateSwitcherWidget::CycleState(bool bUp) {
	TArray<EALSOverlayState> tmp;

	for (const EALSOverlayState value : TEnumRange<EALSOverlayState>())
		tmp.Add(value);

	if (bUp)
		selectedIndex = selectedIndex + 1 < tmp.Num() ? selectedIndex + 1 : 0;
	else
		selectedIndex = selectedIndex - 1 >= 0 ? selectedIndex - 1 : tmp.Num();

	NewOverlayState = tmp[selectedIndex];
}
