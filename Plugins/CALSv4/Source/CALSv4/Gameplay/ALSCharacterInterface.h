

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../ALSStructs.h"
#include "ALSCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UALSCharacterInterface : public UInterface {
	GENERATED_BODY()
};

/**
 *
 */
class CALSV4_API IALSCharacterInterface {
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Advanced Locomotion System|Interfaces|Character")
		FALSCurrentState GetCurrentState();
	virtual FALSCurrentState GetCurrentState_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Advanced Locomotion System|Interfaces|Character")
		FALSEssentialValues GetEssentialValues();
	virtual FALSEssentialValues GetEssentialValues_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Character")
		void SetMovementState(EALSMovementState NewMovementState);
	virtual void SetMovementState_Implementation(EALSMovementState NewMovementState);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Character")
		void SetMovementAction(EALSMovementAction NewMovementAction);
	virtual void SetMovementAction_Implementations(EALSMovementAction NewMovementAction);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Character")
		void SetRotationMode(EALSRotationMode NewRotationMode);
	virtual void SetRotationMode_Implementations(EALSRotationMode NewRotationMode);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Character")
		void SetGait(EALSGait NewGait);
	virtual void SetGait_Implementations(EALSGait NewGait);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Character")
		void SetViewMode(EALSViewMode NewViewMode);
	virtual void SetViewMode_Implementations(EALSViewMode NewViewMode);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Character")
		void SetOverlayState(EALSOverlayState NewOverlayState);
	virtual void SetOverlayState_Implementations(EALSOverlayState NewOverlayState);
};
