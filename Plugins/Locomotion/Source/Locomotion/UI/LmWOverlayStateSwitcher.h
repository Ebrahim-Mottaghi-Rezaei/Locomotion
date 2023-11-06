#pragma once

#include <Components/CanvasPanel.h>
#include <Components/VerticalBox.h>
#include <Misc/EnumRange.h>
#include "CoreMinimal.h"
#include "LmWOverlayStateButton.h"
#include "Blueprint/UserWidget.h"
#include "Locomotion/DataTypes/LmEnums.h"
#include "LmWOverlayStateSwitcher.generated.h"

USTRUCT( BlueprintType , Category = "Locomotion|DataTypes" )
struct FLmOverlayStateParams {
	GENERATED_BODY()
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Overlay State Params" )
	ULmWOverlayStateButton* Widget;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Overlay State Params" )
	ELmOverlayState State;


	FLmOverlayStateParams() {
		Widget = nullptr;
		State  = ELmOverlayState::Lm_Default;
	}


	FLmOverlayStateParams(ULmWOverlayStateButton* widget, const ELmOverlayState state) {
		Widget = widget;
		State  = state;
	}
};

ENUM_RANGE_BY_COUNT( ELmOverlayState , ELmOverlayState::Lm_Count );

UCLASS( Category="Locomotion|Widgets" )
class LOCOMOTION_API ULmWOverlayStateSwitcher : public UUserWidget {
	GENERATED_BODY()

protected:
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion" )
	ELmOverlayState NewOverlayState;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion" )
	UCanvasPanel* MovablePanels;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion" )
	TSubclassOf<ULmWOverlayStateButton> OverlayStateButtonTemplate;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion" )
	TArray<FLmOverlayStateParams> OverlayStateButtons;
	UPROPERTY( BlueprintReadOnly , meta=(BindWidget) )
	UVerticalBox* VerticalBox;

public:
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION( BlueprintCallable , Category = "Locomotion|Widget" )
	void SelectOverlayState() const;

	UFUNCTION( BlueprintCallable , Category = "Locomotion|Widget" )
	void CycleState(bool bUp);

protected:
	UFUNCTION( BlueprintCallable , Category = "Locomotion|Widget" )
	void CreateButtons();

	UFUNCTION( BlueprintCallable , Category = "Locomotion|Widget" )
	void UpdateButtonFocus();

	UFUNCTION( BlueprintCallable , Category = "Locomotion|Widget" )
	void SetUIElements(UCanvasPanel* MovablePanel, UVerticalBox* VBox);

	TArray<ELmOverlayState> OverlayStates;
	uint8                   SelectedIndex;
};
