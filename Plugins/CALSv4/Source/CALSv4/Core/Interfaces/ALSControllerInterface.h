#pragma once

#include "CoreMinimal.h"
#include "CALSv4/Data/ALSStructs.h"
#include "UObject/Interface.h"
#include "ALSControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UALSControllerInterface : public UInterface {
	GENERATED_BODY()
};

class CALSV4_API IALSControllerInterface {
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "C++ ALS|Debug")
		FDebugInfo GetDebugInfo();
};