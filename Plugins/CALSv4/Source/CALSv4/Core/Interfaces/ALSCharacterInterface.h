#pragma once

#include "CoreMinimal.h"

#include <CALSv4/Data/ALSStructs.h>
#include "UObject/Interface.h"

#include "ALSCharacterInterface.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class UALSCharacterInterface : public UInterface {
	GENERATED_BODY()
};

class CALSV4_API IALSCharacterInterface {
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Advanced Locomotion System|Interfaces|Character")
		FALSCurrentState GetCurrentState();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Advanced Locomotion System|Interfaces|Character")
		FALSEssentialValues GetEssentialValues();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Character")
		void SetMovementState(EALSMovementState NewMovementState);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Character")
		void SetMovementAction(EALSMovementAction NewMovementAction);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Character")
		void SetRotationMode(EALSRotationMode NewRotationMode);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Character")
		void SetGait(EALSGait NewGait);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Character")
		void SetViewMode(EALSViewMode NewViewMode);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Character")
		void SetOverlayState(EALSOverlayState NewOverlayState);
};