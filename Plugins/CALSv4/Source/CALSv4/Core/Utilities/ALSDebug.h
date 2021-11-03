#pragma once
#include "CoreMinimal.h"

class ALSDebug {
public:
	static void LogInfo(FString Message);

	static void LogWarning(FString Message);

	static void LogError(FString Message);
};