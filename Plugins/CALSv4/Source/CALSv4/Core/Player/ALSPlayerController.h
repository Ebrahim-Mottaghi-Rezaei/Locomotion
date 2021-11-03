#pragma once

#include "CoreMinimal.h"
#include "CALSv4/Core/Interfaces/ALSControllerInterface.h"
#include "CALSv4/Widgets/ALSHudWidget.h"
#include "CALSv4/Widgets/ALSOverlayStateSwitcherWidget.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "ALSPlayerController.generated.h"

//This controller is responsible for managing the debug settings, displaying the Debug HUD, and managing the Overlay State menu. All other character relevant input can be found within the ALS_Base_CharacterBP.
UCLASS()
class CALSV4_API AALSPlayerController : public APlayerController, public IALSControllerInterface {
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|HUD")
		TSubclassOf<UALSHudWidget> ALSHudWidget;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Debug")
		ACharacter* DebugFocusCharacter;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Debug")
		TArray<ACharacter*> AvailableDebugCharacters;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Debug")
		bool bShowHud;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Debug")
		bool bDebugView;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Debug")
		bool bShowTraces;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Debug")
		bool bShowDebugShapes;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Debug")
		bool bShowLayerColors;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Debug")
		bool bShowCharacterInfo;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Debug")
		bool bSlowMotion;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Debug")
		USoundBase* ClickSound;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|HUD")
		UALSHudWidget* ALSHud;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|HUD")
		UALSOverlayStateSwitcherWidget* OverlaySwitcher;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|HUD")
		bool bOverlayMenuOpen;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

	//Debug functions
	UFUNCTION()
		virtual void ToggleShowHud();
	UFUNCTION()
		virtual void ToggleDebugView();
	UFUNCTION()
		virtual void ToggleShowTraces();
	UFUNCTION()
		virtual void ToggleShowDebugShapes();
	UFUNCTION()
		virtual void ToggleShowLayerColors();
	UFUNCTION()
		virtual void ToggleShowCharacterInfo();
	UFUNCTION()
		virtual void ToggleSlowMotion();
	UFUNCTION()
		virtual void SelectPrevItem();
	UFUNCTION()
		virtual void SelectNextItem();
	UFUNCTION()
		virtual void OpenOverlayMenu();
	UFUNCTION()
		virtual void CloseOverlayMenu();
	UFUNCTION()
		virtual void CycleOverlayUp();
	UFUNCTION()
		virtual void CycleOverlayDown();
};