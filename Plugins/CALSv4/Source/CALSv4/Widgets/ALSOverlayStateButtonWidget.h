#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ALSOverlayStateButtonWidget.generated.h"

UCLASS()
class CALSV4_API UALSOverlayStateButtonWidget : public UUserWidget {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		UImage* Background;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		UTextBlock* Text;
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FLinearColor BackgroundSelectedColor;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FLinearColor BackgroundUnSelectedColor;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FLinearColor TextSelectedColor;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FLinearColor TextUnSelectedColor;
public:
	UFUNCTION(BlueprintCallable)
		void SetVisualParameters(bool bIsSelected);
};