


#include "ALSHUDWidget.h"
#include <Layout/Geometry.h>
#include "../Gameplay/ALSPlayerController.h"
#include "../Gameplay/ALSCameraInterface.h"
#include "../Gameplay/ALSControllerInterface.h"
#include <Blueprint/WidgetLayoutLibrary.h>
#include "../Gameplay/ALSCharacterInterface.h"
#include "Components/CanvasPanelSlot.h"
#include "../ALSHelpers.h"
#include "../ALSLogger.h"

void UALSHUDWidget::NativeTick(const FGeometry& MovieSceneBlends, float InDeltaTime) {
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
		bSlowMotion = info.bSlowMotion;
		bShowCharacterInfo = info.bShowCharacterInfo;
	}

	if (GetCharacterInfoVisibility() == ESlateVisibility::Visible) {
		if (IsValid(DebugFocusCharacter))
			if (DebugFocusCharacter->GetClass()->ImplementsInterface(UALSCameraInterface::StaticClass())) {
				const auto transform = IALSCameraInterface::Execute_Get3PPivotTarget(DebugFocusCharacter);

				FVector2D screenpos;
				UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(pc, transform.GetLocation() + FVector(0, 0, 100), screenpos, false);
				UWidgetLayoutLibrary::SlotAsCanvasSlot(MovingPanel)->SetPosition(screenpos);
			}
	}
}

void UALSHUDWidget::SetMovingPanel(UCanvasPanel* Panel) {
	MovingPanel = Panel;
}

ESlateVisibility UALSHUDWidget::GetHudVisibility() const {
	return bShowHUD ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
}

ESlateVisibility UALSHUDWidget::GetCharacterInfoVisibility() const {
	return (IsValid(DebugFocusCharacter) && bShowCharacterInfo) ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
}

FSlateColor UALSHUDWidget::GetShowHudColor() const {
	return bShowHUD ? EnabledColor : DisabledColor;
}

FSlateColor UALSHUDWidget::GetSlowMotionColor() const {
	return bSlowMotion ? EnabledColor : DisabledColor;
}

FSlateColor UALSHUDWidget::GetDebugViewColor() const {
	return bDebugView ? EnabledColor : DisabledColor;
}

FSlateColor UALSHUDWidget::GetShowTracesColor() const {
	return bShowTraces ? EnabledColor : DisabledColor;
}

FSlateColor UALSHUDWidget::GetShowDebugShapesColor() const {
	return bShowDebugShapes ? EnabledColor : DisabledColor;
}

FSlateColor UALSHUDWidget::GetShowLayerShapesColor() const {
	return bShowLayerColors ? EnabledColor : DisabledColor;
}

FSlateColor UALSHUDWidget::GetShowCharacterInfoColor() const {
	return bShowCharacterInfo ? EnabledColor : DisabledColor;
}

FString UALSHUDWidget::GetDebugCharacterName() const {
	return IsValid(DebugFocusCharacter) ? DebugFocusCharacter->GetName() : FString(TEXT("[C++ ALS v4] : No Valid Character Selected"));
}

FString UALSHUDWidget::GetCharacterStates() const {
	if (bShowCharacterInfo && IsValid(DebugFocusCharacter) && DebugFocusCharacter->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
		const auto State = IALSCharacterInterface::Execute_GetCurrentState(DebugFocusCharacter);

		return FString::Printf(TEXT("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s"),
			*UEnum::GetDisplayValueAsText(State.PawnMovementMode).ToString(),
			*UEnum::GetDisplayValueAsText(State.MovementState).ToString(),
			*UEnum::GetDisplayValueAsText(State.MovementAction).ToString(),
			*UEnum::GetDisplayValueAsText(State.RotationMode).ToString(),
			*UEnum::GetDisplayValueAsText(State.ActualGait).ToString(),
			*UEnum::GetDisplayValueAsText(State.ActualStance).ToString(),
			*UEnum::GetDisplayValueAsText(State.ViewMode).ToString(),
			*UEnum::GetDisplayValueAsText(State.OverlayState).ToString()
		);
	}

	return FString(TEXT(""));
}

FString UALSHUDWidget::GetAnimCurvesNames() const {
	if (!IsValid(DebugFocusCharacter))
		return FString("[C++ ALS v4] : DebugFocusCharacter is not valid");

	if (!IsValid(DebugFocusCharacter->GetMesh()->GetAnimInstance()))
		return FString("[C++ ALS v4] : AnimInstance is not valid");

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

FText UALSHUDWidget::GetAnimCurvesValues() const {
	if (!IsValid(DebugFocusCharacter))
		return FText::FromString(TEXT("[C++ ALS v4] : DebugFocusCharacter is not valid"));

	if (!IsValid(DebugFocusCharacter->GetMesh()->GetAnimInstance()))
		return FText::FromString("[C++ ALS v4] : AnimInstance is not valid");

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