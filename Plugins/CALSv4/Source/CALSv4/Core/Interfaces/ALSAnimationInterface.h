#pragma once

#include "CoreMinimal.h"
#include "CALSv4/Data/ALSEnums.h"
#include "UObject/Interface.h"
#include "ALSAnimationInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UALSAnimationInterface : public UInterface {
	GENERATED_BODY()
};

class CALSV4_API IALSAnimationInterface {
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Animations")
		void Jumped();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Animations")
		void SetGroundedEntryState(EALSGroundedEntryState GroundedEntryState);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Animations")
		void SetOverlayOverrideState(int OverlayOverrideState);
};