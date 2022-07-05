

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LmLogger.generated.h"

UCLASS()
class LOCOMOTION_API ULmLogger : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Logging")
		static void LogInfo(FString Message, const float duration = 5.0f);
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Logging")
		static void LogWarning(FString Message, const float duration = 5.0f);
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Logging")
		static void LogError(FString Message, const float duration = 5.0f);
};