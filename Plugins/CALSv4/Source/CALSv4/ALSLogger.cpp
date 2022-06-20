


#include "ALSLogger.h"

void UALSLogger::LogInfo(const FString Message, const float duration) {
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Cyan, FString::Printf(TEXT("[C++ ALS v4] : %s"), *Message));

	UE_LOG(LogTemp, Display, TEXT("[C++ ALS v4] : %s"), *Message);
}

void UALSLogger::LogWarning(const FString Message, const float duration) {
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Orange, FString::Printf(TEXT("[C++ ALS v4] : %s"), *Message));

	UE_LOG(LogTemp, Warning, TEXT("[C++ ALS v4] : %s"), *Message);
}

void UALSLogger::LogError(const FString Message, const float duration) {
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Red, FString::Printf(TEXT("[C++ ALS v4] : %s"), *Message));

	UE_LOG(LogTemp, Error, TEXT("[C++ ALS v4] : %s"), *Message);
}