#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "LmControllerInputConfiguration.generated.h"

UCLASS()
class LOCOMOTION_API  ULmControllerInputConfiguration : public UDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Controller")
		UInputAction* ToggleHUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Controller")
		UInputAction* ToggleDebugView;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Controller")
		UInputAction* ToggleShowTraces;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Controller")
		UInputAction* ToggleDebugShapes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Controller")
		UInputAction* ToggleLayerColors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Controller")
		UInputAction* ToggleCharacterInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Controller")
		UInputAction* ToggleSlowMotion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Controller")
		UInputAction* ToggleOverlayMenu;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Controller")
		UInputAction* CycleDebugCharacters;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Controller")
		UInputAction* CycleOverlayMenuItems;
};