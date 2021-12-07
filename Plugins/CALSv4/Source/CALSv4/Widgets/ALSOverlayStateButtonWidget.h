#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ALSOverlayStateButtonWidget.generated.h"

UCLASS()
class CALSV4_API UALSOverlayStateButtonWidget : public UUserWidget {
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Overlay State Button")
		FLinearColor BackgroundSelectedColor = FLinearColor::White;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Overlay State Button")
		FLinearColor BackgroundUnSelectedColor = FLinearColor::FromSRGBColor(FColor::FromHex("0000003F"));
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Overlay State Button")
		FLinearColor TextSelectedColor = FLinearColor::FromSRGBColor(FColor::FromHex("404040FF"));
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Overlay State Button")
		FLinearColor TextUnSelectedColor = FLinearColor::White;
public:
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Overlay State Button")
		void SetUIElements(UImage* background, UTextBlock* text);
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Overlay State Button")
		void SetVisualParameters(bool bIsSelected);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Advanced Locomotion System|Overlay State Button")
		UImage* GetBackground();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Advanced Locomotion System|Overlay State Button")
		UTextBlock* GetText();
private:
	UImage* Background;
	UTextBlock* Text;
};