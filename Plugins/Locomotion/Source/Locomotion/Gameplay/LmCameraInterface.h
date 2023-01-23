#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../LmStructs.h"
#include "LmCameraInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Category = "Locomotion")
class ULmCameraInterface : public UInterface {
	GENERATED_BODY()
};

class LOCOMOTION_API ILmCameraInterface {
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Interfaces|Camera System")
		FLmCameraParameters GetCameraParameters();
	virtual FLmCameraParameters GetCameraParameters_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Interfaces|Camera System")
		FVector GetFPCameraTarget();
	virtual FVector GetFPCameraTarget_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Interfaces|Camera System")
		FTransform Get3PPivotTarget();
	virtual FTransform Get3PPivotTarget_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Interfaces|Camera System")
		FLmTraceParams Get3PTraceParameters();
	virtual FLmTraceParams Get3PTraceParameters_Implementation();
};
