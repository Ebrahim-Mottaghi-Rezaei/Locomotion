

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../ALSStructs.h"
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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Camera System")
		FALSCameraParameters GetCameraParameters();
	virtual FALSCameraParameters GetCameraParameters_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Camera System")
		FVector GetFPCameraTarget();
	virtual FVector GetFPCameraTarget_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Camera System")
		FTransform Get3PPivotTarget();
	virtual FTransform Get3PPivotTarget_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Interfaces|Camera System")
		FALSTraceParams Get3PTraceParameters();
	virtual FALSTraceParams Get3PTraceParameters_Implementation();
};
