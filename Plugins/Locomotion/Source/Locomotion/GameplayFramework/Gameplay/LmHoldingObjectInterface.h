#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LmHoldingObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULmHoldingObjectInterface : public UInterface {
	GENERATED_BODY()
};

class LOCOMOTION_API ILmHoldingObjectInterface {
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Locomotion|Interfaces|Hold Objects")
		void SetHoldingActor(AActor* owner);
	virtual void SetHoldingActor_Implementation(AActor* owner);
};