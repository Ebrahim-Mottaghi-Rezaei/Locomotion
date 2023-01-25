#include "LmWHuD.h"

#include "../LmLogger.h"
#include "../LmHelpers.h"
#include "../Gameplay/LmPlayerController.h"
#include "../Gameplay/LmCameraInterface.h"
#include "../Gameplay/LmControllerInterface.h"
#include "../Gameplay/LmCharacterInterface.h"

#include <Blueprint/WidgetLayoutLibrary.h>
#include <Layout/Geometry.h>
#include "Components/CanvasPanelSlot.h"

void ULmWHuD::NativeTick(const FGeometry& MovieSceneBlends, float InDeltaTime) {
	Super::NativeTick(MovieSceneBlends, InDeltaTime);

	dt = InDeltaTime;

	const auto pc = GetOwningPlayer();
	if (pc->GetClass()->ImplementsInterface(ULmControllerInterface::StaticClass())) {
		const auto info = ILmControllerInterface::Execute_GetDebugInfo(pc);
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
			if (DebugFocusCharacter->GetClass()->ImplementsInterface(ULmCameraInterface::StaticClass())) {
				const auto transform = ILmCameraInterface::Execute_Get3PPivotTarget(DebugFocusCharacter);

				FVector2D screenpos;
				UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(pc, transform.GetLocation() + FVector(0, 0, 100), screenpos, false);
				UWidgetLayoutLibrary::SlotAsCanvasSlot(MovingPanel)->SetPosition(screenpos);
			}
	}
}

void ULmWHuD::SetMovingPanel(UCanvasPanel* Panel) {
	MovingPanel = Panel;
}

ESlateVisibility ULmWHuD::GetHudVisibility() const {
	return bShowHUD ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
}

ESlateVisibility ULmWHuD::GetCharacterInfoVisibility() const {
	return (IsValid(DebugFocusCharacter) && bShowCharacterInfo) ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
}

FSlateColor ULmWHuD::GetShowHudColor() const {
	return bShowHUD ? EnabledColor : DisabledColor;
}

FSlateColor ULmWHuD::GetSlowMotionColor() const {
	return bSlowMotion ? EnabledColor : DisabledColor;
}

FSlateColor ULmWHuD::GetDebugViewColor() const {
	return bDebugView ? EnabledColor : DisabledColor;
}

FSlateColor ULmWHuD::GetShowTracesColor() const {
	return bShowTraces ? EnabledColor : DisabledColor;
}

FSlateColor ULmWHuD::GetShowDebugShapesColor() const {
	return bShowDebugShapes ? EnabledColor : DisabledColor;
}

FSlateColor ULmWHuD::GetShowLayerShapesColor() const {
	return bShowLayerColors ? EnabledColor : DisabledColor;
}

FSlateColor ULmWHuD::GetShowCharacterInfoColor() const {
	return bShowCharacterInfo ? EnabledColor : DisabledColor;
}

FString ULmWHuD::GetDebugCharacterName() const {
	return IsValid(DebugFocusCharacter) ? DebugFocusCharacter->GetName() : FString(TEXT("ULmWHuD::GetDebugCharacterName | No Valid Character Selected"));
}

FString ULmWHuD::GetCharacterStates() const {
	if (bShowCharacterInfo && IsValid(DebugFocusCharacter) && DebugFocusCharacter->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass())) {
		const auto State = ILmCharacterInterface::Execute_GetCurrentState(DebugFocusCharacter);

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

FString ULmWHuD::GetAnimCurvesNames() const {
	if (!IsValid(DebugFocusCharacter))
		return FString("ULmWHuD::GetAnimCurvesNames::DebugFocusCharacter is not valid");

	if (!IsValid(DebugFocusCharacter->GetMesh()->GetAnimInstance()))
		return FString("ULmWHuD::GetAnimCurvesNames::AnimInstance is not valid");

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

FText ULmWHuD::GetAnimCurvesValues() const {
	if (!IsValid(DebugFocusCharacter))
		return FText::FromString(TEXT("ULmWHuD::GetAnimCurvesValues::DebugFocusCharacter is not valid"));

	if (!IsValid(DebugFocusCharacter->GetMesh()->GetAnimInstance()))
		return FText::FromString("ULmWHuD::GetAnimCurvesValues::AnimInstance is not valid");

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

FText ULmWHuD::GetFrameRate() const {
	return FText::FromString(FString::SanitizeFloat(FMath::Floor(1.0f / dt)));
}
