#pragma once

#include "CoreMinimal.h"
#include "Locomotion/DataTypes/LmStructs.h"
#include "UObject/Interface.h"
#include "LmCameraManagerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE( MinimalAPI , Category = "Locomotion" )
class ULmCameraManagerInterface : public UInterface {
	GENERATED_BODY()
};

class LOCOMOTION_API ILmCameraManagerInterface {
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION( BlueprintCallable , BlueprintNativeEvent )
	void SetControlledPawn(APawn* ControlledPawn);
};
