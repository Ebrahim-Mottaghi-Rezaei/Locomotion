

#pragma once

#include "CoreMinimal.h"
#include "CALSv4/UI/ALSOverlayStateSwitcherWidget.h"
#include "GameFramework/PlayerController.h"
#include "ALSControllerInterface.h"
#include "ALSPlayerController.generated.h"

/**
 *
 */
UCLASS()
class CALSV4_API AALSPlayerController : public APlayerController, public IALSControllerInterface {
	GENERATED_BODY()
public:
	AALSPlayerController();
protected:
	//Changing this value requires UE to restart.
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Input")
		bool bBindDefaultInputEvents = true;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Input")
		USoundWave* ClickSound;
	UPROPERTY(BlueprintReadWrite, Category = "Advanced Locomotion System|HUD")
		bool bOverlayMenuOpen;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|HUD")
		UALSOverlayStateSwitcherWidget* OverlaySwitcher;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|HUD")
		TSubclassOf<UALSOverlayStateSwitcherWidget> ALSOverlayStateSwitcherTemplate;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|HUD")
		TSubclassOf<UUserWidget> ALSHudTemplate;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Debug")
		ACharacter* DebugFocusCharacter;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Debug")
		TArray<ACharacter*> AvailableDebugCharacters;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Debug")
		bool bShowHud;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Debug")
		bool bDebugView;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Debug")
		bool bShowTraces;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Debug")
		bool bShowDebugShapes;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Debug")
		bool bShowLayerColors;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Debug")
		bool bShowCharacterInfo;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Debug")
		bool bSlowMotion;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

	//Debug functions
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|HUD")
		virtual void ToggleShowHud();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Debug")
		virtual void ToggleDebugView();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Debug")
		virtual void ToggleShowTraces();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Debug")
		virtual void ToggleShowDebugShapes();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Debug")
		virtual void ToggleShowLayerColors();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Debug")
		virtual void ToggleShowCharacterInfo();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Debug")
		virtual void ToggleSlowMotion();

	virtual void SelectPrevALSCharacter();
	virtual void SelectNextALSCharacter();

	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|HUD")
		virtual void OpenOverlayMenu();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|HUD")
		virtual void CloseOverlayMenu();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|HUD")
		virtual void CycleOverlayUp();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|HUD")
		virtual void CycleOverlayDown();

	uint8 SelectedALSCharacterIndex;

public:
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Debug")
		virtual FALSDebugInfo GetDebugInfo_Implementation() override;
};
