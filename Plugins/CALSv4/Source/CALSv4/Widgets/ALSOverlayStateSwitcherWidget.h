#pragma once

#include "CoreMinimal.h"
#include "ALSOverlayStateButtonWidget.h"
#include "Blueprint/UserWidget.h"
#include "CALSv4/Data/ALSEnums.h"
#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "ALSOverlayStateSwitcherWidget.generated.h"

USTRUCT(BlueprintType, Category = "C++ ALS|DataStructures")
struct FALSOverlayStateParams {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UALSOverlayStateButtonWidget* Widget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EALSOverlayState State;

	FALSOverlayStateParams() {}
	FALSOverlayStateParams(UALSOverlayStateButtonWidget* widget, EALSOverlayState state) {
		Widget = widget;
		State = state;
	}
};

ENUM_RANGE_BY_COUNT(EALSOverlayState, EALSOverlayState::ALS_Barrel)
UCLASS()
class CALSV4_API UALSOverlayStateSwitcherWidget : public UUserWidget {
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		EALSOverlayState NewOverlayState;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		UCanvasPanel* MovablePanels;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		UVerticalBox* VerticalBox;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		TArray<FALSOverlayStateParams> OverlayStateButtons;

public:
	virtual void NativeConstruct() override;
	virtual  void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SelectOverlayState() const;
	void CycleState(bool bUp);

protected:
	void CreateButtons();
	void UpdateButtonFocus();
	uint8 selectedIndex;
};