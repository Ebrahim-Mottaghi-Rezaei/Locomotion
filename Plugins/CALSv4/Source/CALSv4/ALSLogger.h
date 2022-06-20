

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ALSLogger.generated.h"

/**
 *
 */
UCLASS()
class CALSV4_API UALSLogger : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Helpers|Logging")
		static void LogInfo(FString Message, const float duration = 5.0f);
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Helpers|Logging")
		static void LogWarning(FString Message, const float duration = 5.0f);
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Helpers|Logging")
		static void LogError(FString Message, const float duration = 5.0f);
};
