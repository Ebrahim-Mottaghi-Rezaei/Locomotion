#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LmControllerInterface.h"
#include "../UI/LmWOverlayStateSwitcher.h"
#include "LmPlayerController.generated.h"

UCLASS()
class LOCOMOTION_API ALmPlayerController : public APlayerController, public ILmControllerInterface {
	GENERATED_BODY()
public:
	ALmPlayerController();
protected:
	//Changing this value requires UE to restart.
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Input")
		bool bBindDefaultInputEvents = true;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Input")
		USoundWave* ClickSound;
	UPROPERTY(BlueprintReadWrite, Category = "Locomotion|HuD")
		bool bOverlayMenuOpen;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|HuD")
		ULmWOverlayStateSwitcher* OverlaySwitcher;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|HuD")
		TSubclassOf<ULmWOverlayStateSwitcher> OverlayStateSwitcherTemplate;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|HuD")
		TSubclassOf<UUserWidget> HudTemplate;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Locomotion|Debug")
		ACharacter* DebugFocusCharacter;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Locomotion|Debug")
		TArray<ACharacter*> AvailableDebugCharacters;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Debug")
		bool bShowHud;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Debug")
		bool bDebugView;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Debug")
		bool bShowTraces;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Debug")
		bool bShowDebugShapes;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Debug")
		bool bShowLayerColors;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Debug")
		bool bShowCharacterInfo;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Debug")
		bool bSlowMotion;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

	//Debug functions
	UFUNCTION(BlueprintCallable, Category = "Locomotion|HUD")
		virtual void ToggleShowHud();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Debug")
		virtual void ToggleDebugView();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Debug")
		virtual void ToggleShowTraces();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Debug")
		virtual void ToggleShowDebugShapes();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Debug")
		virtual void ToggleShowLayerColors();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Debug")
		virtual void ToggleShowCharacterInfo();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Debug")
		virtual void ToggleSlowMotion();

	virtual void SelectPrevLmDebugCharacter();
	virtual void SelectNextLmDebugCharacter();

	UFUNCTION(BlueprintCallable, Category = "Locomotion|HUD")
		virtual void OpenOverlayMenu();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|HUD")
		virtual void CloseOverlayMenu();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|HUD")
		virtual void CycleOverlayUp();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|HUD")
		virtual void CycleOverlayDown();

	uint8 SelectedLmCharacterIndex;

public:
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Debug")
		virtual FLmDebugInfo GetDebugInfo_Implementation() override;
};
