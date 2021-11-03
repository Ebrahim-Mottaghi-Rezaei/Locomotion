#include "ALSDebug.h"

void ALSDebug::LogInfo(const FString Message) {
	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, FString::Printf(TEXT("[C++ ALS v4] : %s"), *Message), true);*/

	UE_LOG(LogTemp, Display, TEXT("[C++ ALS v4] : %s"), *Message);
}

void ALSDebug::LogError(const FString Message) {
	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, FString::Printf(TEXT("[C++ ALS v4] : %s"), *Message), false);*/

	UE_LOG(LogTemp, Error, TEXT("[C++ ALS v4] : %s"), *Message);
}

void ALSDebug::LogWarning(const FString Message) {
	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, FString::Printf(TEXT("[C++ ALS v4] : %s"), *Message), false);*/

	UE_LOG(LogTemp, Warning, TEXT("[C++ ALS v4] : %s"), *Message);
}