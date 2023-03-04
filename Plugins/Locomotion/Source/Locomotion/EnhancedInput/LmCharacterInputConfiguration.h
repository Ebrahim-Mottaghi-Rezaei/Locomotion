#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "LmCharacterInputConfiguration.generated.h"

UCLASS()
class LOCOMOTION_API ULmCharacterInputConfiguration : public UDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Character")
		UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Character")
		UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Character")
		UInputAction* Aim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Character")
		UInputAction* Jump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Character")
		UInputAction* Stance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Character")
		UInputAction* Walk;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Character")
		UInputAction* Sprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Character")
		UInputAction* Roll;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Character")
		UInputAction* CameraSide;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Character")
		UInputAction* CameraMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Character")
		UInputAction* RotationMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Character")
		UInputAction* Ragdoll;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion|Character")
		UInputAction* ChangeCharacterMesh;
};