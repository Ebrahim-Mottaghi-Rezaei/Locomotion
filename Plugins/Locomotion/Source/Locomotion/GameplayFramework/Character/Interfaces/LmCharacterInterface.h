#pragma once

#include "CoreMinimal.h"
#include "Locomotion/DataTypes/LmStructs.h"
#include "UObject/Interface.h"
#include "LmCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE( MinimalAPI , Category = "Locomotion" )
class ULmCharacterInterface : public UInterface {
	GENERATED_BODY()
};

class LOCOMOTION_API ILmCharacterInterface {
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION( BlueprintCallable , BlueprintImplementableEvent , Category = "Locomotion" )
	FLmCurrentState GetCurrentState();

	virtual FLmCurrentState GetCurrentState_Implementation();

	UFUNCTION( BlueprintCallable , BlueprintImplementableEvent , Category = "Locomotion" )
	FLmEssentialValues GetEssentialValues();

	virtual FLmEssentialValues GetEssentialValues_Implementation();

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "Locomotion" )
	void SetMovementState(ELmMovementState NewMovementState);

	virtual void SetMovementState_Implementation(ELmMovementState NewMovementState);

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "Locomotion" )
	void SetMovementAction(ELmMovementAction NewMovementAction);

	virtual void SetMovementAction_Implementation(ELmMovementAction NewMovementAction);

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "Locomotion" )
	void SetRotationMode(ELmRotationMode NewRotationMode);

	virtual void SetRotationMode_Implementation(ELmRotationMode NewRotationMode);

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "Locomotion" )
	void SetGait(ELmGait NewGait);

	virtual void SetGait_Implementation(ELmGait NewGait);

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "Locomotion" )
	void SetViewMode(ELmViewMode NewViewMode);

	virtual void SetViewMode_Implementation(ELmViewMode NewViewMode);

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "Locomotion" )
	void SetOverlayState(ELmOverlayState NewOverlayState);

	virtual void SetOverlayState_Implementation(ELmOverlayState NewOverlayState);
};
