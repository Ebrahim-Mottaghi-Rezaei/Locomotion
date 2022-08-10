#include "LMLogger.h"

DEFINE_LOG_CATEGORY(LocomotionPlugin);

void ULmLogger::LogInfo(const FString Message, const float duration, const bool PrintOnScreen) {
	if (GEngine && PrintOnScreen)
		GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Cyan, *Message);

	UE_LOG(LocomotionPlugin, Display, TEXT("%s"), *Message);
}

void ULmLogger::LogWarning(const FString Message, const float duration, const bool PrintOnScreen) {
	if (GEngine && PrintOnScreen)
		GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Orange, *Message);

	UE_LOG(LocomotionPlugin, Warning, TEXT("%s"), *Message);
}

void ULmLogger::LogError(const FString Message, const float duration, const bool PrintOnScreen) {
	if (GEngine && PrintOnScreen)
		GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Red, *Message);

	UE_LOG(LocomotionPlugin, Error, TEXT("%s"), *Message);
}