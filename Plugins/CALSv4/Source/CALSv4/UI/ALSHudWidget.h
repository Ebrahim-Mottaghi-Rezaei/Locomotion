

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/CanvasPanel.h>
#include <GameFramework/Character.h>
#include <Math/Color.h>
#include "ALSHUDWidget.generated.h"

/**
 *
 */
UCLASS()
class CALSV4_API UALSHUDWidget : public UUserWidget {
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Advanced Locomotion System|HUD Widget")
		ACharacter* DebugFocusCharacter;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Advanced Locomotion System|HUD Widget")
		bool bShowHUD;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Advanced Locomotion System|HUD Widget")
		bool bSlowMotion;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Advanced Locomotion System|HUD Widget")
		bool bDebugView;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Advanced Locomotion System|HUD Widget")
		bool bShowTraces;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Advanced Locomotion System|HUD Widget")
		bool bShowDebugShapes;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Advanced Locomotion System|HUD Widget")
		bool bShowLayerColors;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Advanced Locomotion System|HUD Widget")
		bool bShowCharacterInfo;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Advanced Locomotion System|HUD Widget")
		FLinearColor EnabledColor = FLinearColor::Green;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Advanced Locomotion System|HUD Widget")
		FLinearColor DisabledColor = FLinearColor(FVector4d(1.0f, 1.0f, 1.0f, 0.5f));
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Advanced Locomotion System|HUD Widget")
		UCanvasPanel* MovingPanel;

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
protected:
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|HUD Widget")
		void SetMovingPanel(UCanvasPanel* Panel);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Advanced Locomotion System|HUD Widget")
		ESlateVisibility GetHudVisibility() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Advanced Locomotion System|HUD Widget")
		ESlateVisibility GetCharacterInfoVisibility() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Advanced Locomotion System|HUD Widget")
		FSlateColor GetShowHudColor() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Advanced Locomotion System|HUD Widget")
		FSlateColor GetSlowMotionColor() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Advanced Locomotion System|HUD Widget")
		FSlateColor GetDebugViewColor() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Advanced Locomotion System|HUD Widget")
		FSlateColor GetShowTracesColor() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Advanced Locomotion System|HUD Widget")
		FSlateColor GetShowDebugShapesColor() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Advanced Locomotion System|HUD Widget")
		FSlateColor GetShowLayerShapesColor() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Advanced Locomotion System|HUD Widget")
		FSlateColor GetShowCharacterInfoColor() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Advanced Locomotion System|HUD Widget")
		FString GetDebugCharacterName() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Advanced Locomotion System|HUD Widget")
		FString GetCharacterStates() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Advanced Locomotion System|HUD Widget")
		FString GetAnimCurvesNames() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Advanced Locomotion System|HUD Widget")
		FText GetAnimCurvesValues() const;
};
