#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "ALSHudWidget.generated.h"

UCLASS()
class CALSV4_API UALSHudWidget : public UUserWidget {
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		ACharacter* DebugFocusCharacter;

	bool bShowHUD;
	bool bSlowMotion;
	bool bDebugView;
	bool bShowTraces;
	bool bShowDebugShapes;
	bool bShowLayerColors;
	bool bShowCharacterInfo;
	FLinearColor EnabledColor;
	FLinearColor DisabledColor;
	UImage* Arrow;
	UCanvasPanel* MovablePanels;

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
protected:
	ESlateVisibility GetHudVisibility() const;
	ESlateVisibility GetCharacterInfoVisibility() const;
	FSlateColor GetShowHudColor();
	FSlateColor GetSlowMotionColor();
	FSlateColor GetDebugViewColor();
	FSlateColor GetShowTracesColor();
	FSlateColor GetShowDebugShapesColor();
	FSlateColor GetShowLayerShapesColor();
	FSlateColor GetCharacterInfoColor();
	FString GetDebugCharacterName() const;
	FString GetCharacterStates() const;
	FString GetAnimCurvesNames() const;
	FText GetAnimCurvesValues() const;
};