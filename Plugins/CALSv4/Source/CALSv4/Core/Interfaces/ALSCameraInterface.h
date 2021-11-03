#pragma once

#include "CoreMinimal.h"
#include <CALSv4/Data/ALSStructs.h>
#include "UObject/Interface.h"
#include "ALSCameraInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UALSCameraInterface : public UInterface {
	GENERATED_BODY()
};

/**
 *
 */
class CALSV4_API IALSCameraInterface {
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "C++ ALS|CameraSystem")
		FALSCameraParameters GetCameraParameters();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "C++ ALS|CameraSystem")
		FVector GetFPCameraTarget();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "C++ ALS|CameraSystem")
		FTransform Get3PPivotTarget();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "C++ ALS|CameraSystem")
		FALSTraceParams Get3PTraceParameters();
};