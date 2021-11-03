#include "ALSHudWidget.h"

#include <Blueprint/WidgetLayoutLibrary.h>
#include <CALSv4/Core/Interfaces/ALSCameraInterface.h>
#include <CALSv4/Core/Interfaces/ALSCharacterInterface.h>
#include <CALSv4/Core/Interfaces/ALSControllerInterface.h>
#include <Components/CanvasPanelSlot.h>
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>

void UALSHudWidget::NativeTick(const FGeometry& MovieSceneBlends, float InDeltaTime) {
	Super::NativeTick(MovieSceneBlends, InDeltaTime);

	const auto pc = GetOwningPlayer();
	if (pc->GetClass()->ImplementsInterface(UALSControllerInterface::StaticClass())) {
		const auto info = IALSControllerInterface::Execute_GetDebugInfo(pc);
		DebugFocusCharacter = info.DebugFocusCharacter;
		bDebugView = info.bDebugView;
		bShowHUD = info.bShowHUD;
		bShowTraces = info.bShowTraces;
		bShowDebugShapes = info.bShowDebugShapes;
		bShowLayerColors = info.bShowLayerColors;
		bSlowMotion = info.bSlomo;
		bShowCharacterInfo = info.bShowCharacterInfo;
	}

	if (GetCharacterInfoVisibility() == ESlateVisibility::Visible) {

		if (IsValid(DebugFocusCharacter) && DebugFocusCharacter->GetClass()->ImplementsInterface(UALSCameraInterface::StaticClass())) {
			const auto transform = IALSCameraInterface::Execute_Get3PPivotTarget(DebugFocusCharacter);

			FVector2D screenpos;
			UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(pc, transform.GetLocation() + FVector(0, 0, 100), screenpos, false);
			UWidgetLayoutLibrary::SlotAsCanvasSlot(MovablePanels)->SetPosition(screenpos);
		}
	}
}

ESlateVisibility UALSHudWidget::GetHudVisibility() const {
	return bShowHUD ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
}

ESlateVisibility UALSHudWidget::GetCharacterInfoVisibility() const {
	return IsValid(DebugFocusCharacter) || !bShowCharacterInfo ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
}

FSlateColor UALSHudWidget::GetShowHudColor() {
	return  bShowHUD ? EnabledColor : DisabledColor;
}

FSlateColor UALSHudWidget::GetSlowMotionColor() {
	return  bSlowMotion ? EnabledColor : DisabledColor;
}

FSlateColor UALSHudWidget::GetDebugViewColor() {
	return  bDebugView ? EnabledColor : DisabledColor;
}

FSlateColor UALSHudWidget::GetShowTracesColor() {
	return  bShowTraces ? EnabledColor : DisabledColor;
}

FSlateColor UALSHudWidget::GetShowDebugShapesColor() {
	return bShowDebugShapes ? EnabledColor : DisabledColor;
}

FSlateColor UALSHudWidget::GetShowLayerShapesColor() {
	return bShowLayerColors ? EnabledColor : DisabledColor;
}

FSlateColor UALSHudWidget::GetCharacterInfoColor() {
	return bShowCharacterInfo ? EnabledColor : DisabledColor;
}

FString UALSHudWidget::GetDebugCharacterName() const {
	return IsValid(DebugFocusCharacter) ? DebugFocusCharacter->GetName() : FString(TEXT("[C++ ALS] No Valid Character Selected"));
}

FString UALSHudWidget::GetCharacterStates() const {
	if (bShowCharacterInfo && IsValid(DebugFocusCharacter) && DebugFocusCharacter->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
		const auto State = IALSCharacterInterface::Execute_GetCurrentState(DebugFocusCharacter);
		return FString::Printf(TEXT("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s"),
			*UEnum::GetValueAsString(State.PawnMovementMode),
			*UEnum::GetValueAsString(State.MovementState),
			*UEnum::GetValueAsString(State.MovementAction),
			*UEnum::GetValueAsString(State.RotationMode),
			*UEnum::GetValueAsString(State.ActualGait),
			*UEnum::GetValueAsString(State.ActualStance),
			*UEnum::GetValueAsString(State.ViewMode),
			*UEnum::GetValueAsString(State.OverlayState)
		);
	}
	return FString(TEXT(""));
}

FString UALSHudWidget::GetAnimCurvesNames() const {
	if (!IsValid(DebugFocusCharacter))
		return FString("[C++ ALS] DebugFocusCharacter is not valid");

	if (!IsValid(DebugFocusCharacter->GetMesh()->GetAnimInstance()))
		return FString("[C++ ALS] AnimInstance is not valid");

	const auto* animInstance = DebugFocusCharacter->GetMesh()->GetAnimInstance();
	TArray<FName> CurveNames;
	animInstance->GetActiveCurveNames(EAnimCurveType::AttributeCurve, CurveNames);
	FString value;

	for (FName name : CurveNames) {
		value.Append(name.ToString());
		value.Append(FString(TEXT("\n")));
	}

	return value;
}

FText UALSHudWidget::GetAnimCurvesValues() const {
	if (!IsValid(DebugFocusCharacter))
		return FText::FromString(TEXT("[C++ ALS] DebugFocusCharacter is not valid"));

	if (!IsValid(DebugFocusCharacter->GetMesh()->GetAnimInstance()))
		return FText::FromString("[C++ ALS] AnimInstance is not valid");

	const auto* animInstance = DebugFocusCharacter->GetMesh()->GetAnimInstance();
	if (!IsValid(animInstance))
		return FText();

	FString value;
	TArray<FName> CurveNames;
	animInstance->GetActiveCurveNames(EAnimCurveType::AttributeCurve, CurveNames);
	for (const FName name : CurveNames) {
		value.Append(FString::SanitizeFloat(animInstance->GetCurveValue(name)));
		value.Append(TEXT("\n"));
	}

	return FText::FromString(value);
}