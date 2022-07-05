

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LmWOverlayStateButton.generated.h"

UCLASS(Category = "Locomotion|Widgets")
class LOCOMOTION_API ULmWOverlayStateButton : public UUserWidget {
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		FLinearColor BackgroundSelectedColor = FLinearColor::White;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		FLinearColor BackgroundUnSelectedColor = FLinearColor::FromSRGBColor(FColor::FromHex("0000003F"));
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		FLinearColor TextSelectedColor = FLinearColor::FromSRGBColor(FColor::FromHex("404040FF"));
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		FLinearColor TextUnSelectedColor = FLinearColor::White;
public:
	UFUNCTION(BlueprintCallable, Category = "Locomotion")
		void SetUIElements(UImage* background, UTextBlock* text);
	UFUNCTION(BlueprintCallable, Category = "Locomotion")
		void SetVisualParameters(bool bIsSelected);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Locomotion")
		UImage* GetBackground();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Locomotion")
		UTextBlock* GetText();
private:
	UImage* Background;
	UTextBlock* Text;
};
