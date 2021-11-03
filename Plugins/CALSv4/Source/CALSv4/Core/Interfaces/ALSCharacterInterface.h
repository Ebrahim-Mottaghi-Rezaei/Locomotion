#pragma once

#include "CoreMinimal.h"
#include "CALSv4/Data/ALSStructs.h"
#include "UObject/Interface.h"
#include "ALSCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, MinimalAPI)
class UALSCharacterInterface : public UInterface {
	GENERATED_BODY()
};

class CALSV4_API IALSCharacterInterface {
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "C++ ALS|Character Information")
		FALSCurrentState GetCurrentState();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "C++ ALS|Character Information")
		FALSEssentialValues GetEssentialValues();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "C++ ALS|Character States")
		void SetMovementState(EALSMovementState NewMovementState);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "C++ ALS|Character States")
		void SetMovementAction(EALSMovementAction NewMovementAction);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "C++ ALS|Character States")
		void SetRotationMode(EALSRotationMode NewRotationMode);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "C++ ALS|Character States")
		void SetGait(EALSGait NewGait);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "C++ ALS|Character States")
		void SetViewMode(EALSViewMode NewViewMode);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "C++ ALS|Character States")
		void SetOverlayState(EALSOverlayState NewOverlayState);
};