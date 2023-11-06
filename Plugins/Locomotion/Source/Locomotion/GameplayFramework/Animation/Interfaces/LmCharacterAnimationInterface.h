#pragma once

#include "CoreMinimal.h"
#include "Locomotion/DataTypes/LmEnums.h"
#include "UObject/Interface.h"
#include "LmCharacterAnimationInterface.generated.h"

// This class does not need to be modified.
UINTERFACE( MinimalAPI )
class ULmCharacterAnimationInterface : public UInterface {
	GENERATED_BODY()
};

class LOCOMOTION_API ILmCharacterAnimationInterface {
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "Locomotion" )
	void Jumped();

	virtual void Jumped_Implementation();

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "Locomotion" )
	void SetGroundedEntryState(ELmGroundedEntryState GroundedEntryState);

	virtual void SetGroundedEntryState_Implementation(ELmGroundedEntryState GroundedEntryState);

	UFUNCTION( BlueprintCallable , BlueprintNativeEvent , Category = "Locomotion" )
	void SetOverlayOverrideState(int OverlayOverrideState);

	virtual void SetOverlayOverrideState_Implementation(int OverlayOverrideState);
};
