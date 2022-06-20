

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../ALSEnums.h"
#include "ALSCharacterAnimationInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UALSCharacterAnimationInterface : public UInterface {
	GENERATED_BODY()
};

/**
 *
 */
class CALSV4_API IALSCharacterAnimationInterface {
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Animations")
		void Jumped();
	virtual void Jumped_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Animations")
		void SetGroundedEntryState(EALSGroundedEntryState GroundedEntryState);
	virtual void SetGroundedEntryState_Implementation(EALSGroundedEntryState GroundedEntryState);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Animations")
		void SetOverlayOverrideState(int OverlayOverrideState);
	virtual void SetOverlayOverrideState_Implementation(int OverlayOverrideState);
public:
};