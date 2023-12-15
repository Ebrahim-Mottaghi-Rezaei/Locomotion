#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/LmControllerInterface.h"
#include "Locomotion/DataTypes/LmEvents.h"
#include "Locomotion/EnhancedInput/LmControllerInputConfiguration.h"
#include "Locomotion/GameplayFramework/Camera/LmPlayerCameraManager.h"
#include "Locomotion/UI/LmWOverlayStateSwitcher.h"
#include "LmPlayerController.generated.h"

UCLASS()
class LOCOMOTION_API ALmPlayerController : public APlayerController, public ILmControllerInterface {
	GENERATED_BODY()

public:
	UPROPERTY( BlueprintCallable , BlueprintAssignable )
	FDebugViewChangedDelegate OnDebugViewChanged;

	ALmPlayerController();

protected:
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Enhanced Input" )
	bool bBindDefaultInputKeys = true;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Enhanced Input" , meta = (EditCondition = "bBindDefaultInputKeys") )
	bool bClearExistingKeyBindings = false;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Enhanced Input" , meta = (EditCondition = "bBindDefaultInputKeys") )
	UInputMappingContext* InputMappings;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Enhanced Input" , meta = (EditCondition = "bBindDefaultInputKeys") )
	ULmControllerInputConfiguration* InputActions;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Enhanced Input" , meta = (EditCondition = "bBindDefaultInputKeys") )
	class USoundWave* ClickSound;
	UPROPERTY( BlueprintReadWrite , Category = "Locomotion|HuD" )
	bool bOverlayMenuOpen;
	UPROPERTY( BlueprintReadOnly , Category = "Locomotion|HuD" )
	ULmWOverlayStateSwitcher* OverlaySwitcher;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|HuD" )
	TSubclassOf<ULmWOverlayStateSwitcher> OverlayStateSwitcherTemplate;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|HuD" )
	TSubclassOf<UUserWidget> HudTemplate;

	UPROPERTY( BlueprintReadOnly , VisibleInstanceOnly , Category = "Locomotion|Debug" )
	ACharacter* DebugFocusCharacter;
	UPROPERTY( BlueprintReadOnly , VisibleInstanceOnly , Category = "Locomotion|Debug" )
	TArray<ACharacter*> AvailableDebugCharacters;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Debug" )
	bool bShowHud;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Debug" )
	bool bDebugView;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Debug" )
	bool bShowTraces;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Debug" )
	bool bShowDebugShapes;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Debug" )
	bool bShowLayerColors;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Debug" )
	bool bShowCharacterInfo;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Debug" )
	bool bSlowMotion;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void SetupInputComponent() override;

	//Debug functions
	UFUNCTION( BlueprintCallable , Category = "Locomotion|HUD" )
	virtual void ToggleShowHud();

	UFUNCTION( BlueprintCallable , Category = "Locomotion|Debug" )
	virtual void ToggleDebugView();

	UFUNCTION( BlueprintCallable , Category = "Locomotion|Debug" )
	virtual void ToggleShowTraces();

	UFUNCTION( BlueprintCallable , Category = "Locomotion|Debug" )
	virtual void ToggleShowDebugShapes();

	UFUNCTION( BlueprintCallable , Category = "Locomotion|Debug" )
	virtual void ToggleShowLayerColors();

	UFUNCTION( BlueprintCallable , Category = "Locomotion|Debug" )
	virtual void ToggleShowCharacterInfo();

	UFUNCTION( BlueprintCallable , Category = "Locomotion|Debug" )
	virtual void ToggleSlowMotion();

	UFUNCTION( BlueprintCallable , Category = "Locomotion|HUD" )
	virtual void CycleDebugCharacter(bool bNext);

	UFUNCTION( BlueprintCallable , Category = "Locomotion|HUD" )
	virtual void SelectLmDebugCharacter(const FInputActionValue& Value);

	UFUNCTION( BlueprintCallable , Category = "Locomotion|HUD" )
	virtual void ToggleOverlayMenu(const FInputActionValue& Value);

	UFUNCTION( BlueprintCallable , Category = "Locomotion|HUD" )
	virtual void CycleOverlayItems(const FInputActionValue& Value);

	virtual void OpenOverlayMenu();

	UFUNCTION( BlueprintCallable , Category = "Locomotion|HUD" )
	virtual void CloseOverlayMenu();

	UFUNCTION( BlueprintCallable , Category = "Locomotion|HUD" )
	virtual void CycleOverlayUp();

	UFUNCTION( BlueprintCallable , Category = "Locomotion|HUD" )
	virtual void CycleOverlayDown();

	uint8 SelectedLmCharacterIndex;

public:
	UFUNCTION( BlueprintCallable , Category = "Locomotion|Debug" )
	virtual FLmDebugInfo GetDebugInfo_Implementation() override;
};
