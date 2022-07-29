#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/CanvasPanel.h>
#include <GameFramework/Character.h>
#include <Math/Color.h>
#include "LmWHuD.generated.h"

UCLASS(Category = "Locomotion|Widgets")
class LOCOMOTION_API ULmWHuD : public UUserWidget {
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Locomotion")
		ACharacter* DebugFocusCharacter;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Locomotion")
		bool bShowHUD;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Locomotion")
		bool bSlowMotion;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Locomotion")
		bool bDebugView;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Locomotion")
		bool bShowTraces;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Locomotion")
		bool bShowDebugShapes;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Locomotion")
		bool bShowLayerColors;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Locomotion")
		bool bShowCharacterInfo;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Locomotion")
		FLinearColor EnabledColor = FLinearColor::Green;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Locomotion")
		FLinearColor DisabledColor = FLinearColor(FVector4(1.0f, 1.0f, 1.0f, 0.5f));
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Locomotion")
		UCanvasPanel* MovingPanel;

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
protected:
	UFUNCTION(BlueprintCallable, Category = "Locomotion")
		void SetMovingPanel(UCanvasPanel* Panel);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Locomotion")
		ESlateVisibility GetHudVisibility() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Locomotion")
		ESlateVisibility GetCharacterInfoVisibility() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Locomotion")
		FSlateColor GetShowHudColor() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Locomotion")
		FSlateColor GetSlowMotionColor() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Locomotion")
		FSlateColor GetDebugViewColor() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Locomotion")
		FSlateColor GetShowTracesColor() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Locomotion")
		FSlateColor GetShowDebugShapesColor() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Locomotion")
		FSlateColor GetShowLayerShapesColor() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Locomotion")
		FSlateColor GetShowCharacterInfoColor() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Locomotion")
		FString GetDebugCharacterName() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Locomotion")
		FString GetCharacterStates() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Locomotion")
		FString GetAnimCurvesNames() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Locomotion")
		FText GetAnimCurvesValues() const;
};
