#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../LmStructs.h"
#include "LmControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI , Category = "Locomotion")
class ULmControllerInterface : public UInterface {
	GENERATED_BODY()
};

class LOCOMOTION_API ILmControllerInterface {
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion")
		FLmDebugInfo GetDebugInfo();
	virtual FLmDebugInfo GetDebugInfo_Implementation();
};
