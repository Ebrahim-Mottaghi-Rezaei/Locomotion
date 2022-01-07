#pragma once

#include "CoreMinimal.h"
#include "ALSOverlayStateButtonWidget.h"
#include "Blueprint/UserWidget.h"
#include "CALSv4/Data/ALSEnums.h"
#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "ALSOverlayStateSwitcherWidget.generated.h"

USTRUCT(BlueprintType, Category = "Advanced Locomotion System|DataStructures")
struct FALSOverlayStateParams {
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UALSOverlayStateButtonWidget* Widget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EALSOverlayState State;

	FALSOverlayStateParams() {
		Widget = nullptr;
		State = EALSOverlayState::ALS_Default;
	}
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
		TSubclassOf<UALSOverlayStateButtonWidget> OverlayStateButtonTemplate;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		TArray<FALSOverlayStateParams> OverlayStateButtons;
	UVerticalBox* VerticalBox;
	public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Widget")
		void SelectOverlayState() const;
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Widget")
		void CycleState(bool bUp);

	protected:
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Widget")
		void CreateButtons();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Widget")
		void UpdateButtonFocus();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Widget")
		void SetUIElements(UCanvasPanel* movablePanel, UVerticalBox* verticalBox);

	TArray<EALSOverlayState> OverlayStates;
	uint8 selectedIndex;
};