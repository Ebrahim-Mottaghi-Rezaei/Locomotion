#include "LMLogger.h"

void ULmLogger::LogInfo(const FString Message, const float duration, const bool PrintOnScreen) {
	if (GEngine && PrintOnScreen)
		GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Cyan, FString::Printf(TEXT("Locomotion plugin| %s"), *Message));

	UE_LOG(LogTemp, Display, TEXT("Locomotion plugin| %s"), *Message);
}

void ULmLogger::LogWarning(const FString Message, const float duration, const bool PrintOnScreen) {
	if (GEngine && PrintOnScreen)
		GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Orange, FString::Printf(TEXT("Locomotion plugin| %s"), *Message));

	UE_LOG(LogTemp, Warning, TEXT("Locomotion plugin| %s"), *Message);
}

void ULmLogger::LogError(const FString Message, const float duration, const bool PrintOnScreen) {
	if (GEngine && PrintOnScreen)
		GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Red, FString::Printf(TEXT("Locomotion plugin| %s"), *Message));

	UE_LOG(LogTemp, Error, TEXT("Locomotion plugin| %s"), *Message);
}