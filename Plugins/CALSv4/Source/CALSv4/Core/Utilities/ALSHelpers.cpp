#include "ALSHelpers.h"
#include "Kismet/KismetMathLibrary.h"

void UALSLogger::LogInfo(const FString Message) {
	UE_LOG(LogTemp, Display, TEXT("[C++ ALS v4] : %s"), *Message);
}

void UALSLogger::LogWarning(const FString Message) {
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("[C++ ALS v4] : %s"), *Message));

	UE_LOG(LogTemp, Warning, TEXT("[C++ ALS v4] : %s"), *Message);
}

void UALSLogger::LogError(const FString Message) {
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("[C++ ALS v4] : %s"), *Message));

	UE_LOG(LogTemp, Error, TEXT("[C++ ALS v4] : %s"), *Message);
}

FTransform UALSHelpers::SubtractTransform(const FTransform A, const FTransform B) {
	return FTransform(FRotator(A.Rotator().Pitch - B.Rotator().Pitch, A.Rotator().Yaw - B.Rotator().Yaw, A.Rotator().Roll - B.Rotator().Roll), A.GetLocation() - B.GetLocation(), A.GetScale3D() - B.GetScale3D());
}

FALSComponentAndTransform UALSHelpers::LocalSpaceToWorldSpace(const FALSComponentAndTransform LocalSpace) {
	return FALSComponentAndTransform(UKismetMathLibrary::ComposeTransforms(LocalSpace.Transform, LocalSpace.Component->GetComponentTransform()), LocalSpace.Component);
}

FALSComponentAndTransform UALSHelpers::WorldSpaceToLocalSpace(const FALSComponentAndTransform WorldSpace) {
	return FALSComponentAndTransform(UKismetMathLibrary::ComposeTransforms(WorldSpace.Transform, WorldSpace.Component->GetComponentTransform().Inverse()), WorldSpace.Component);
}

float UALSHelpers::GetDistanceBetweenTwoSocketsAndMapRange(const USkeletalMeshComponent * Component, const FName SocketOrBoneNameA, ERelativeTransformSpace SocketSpaceA, const FName SocketOrBoneNameB, const ERelativeTransformSpace SocketSpaceB, const bool bRemapRange, const float InRangeMin, const float InRangeMax, const float OutRangeMin, const float OutRangeMax) {
	if (Component && SocketOrBoneNameA != NAME_None && SocketOrBoneNameB != NAME_None) {
		const FTransform SocketTransformA = Component->GetSocketTransform(SocketOrBoneNameA, SocketSpaceA);
		const FTransform SocketTransformB = Component->GetSocketTransform(SocketOrBoneNameB, SocketSpaceB);
		const float Distance = (SocketTransformB.GetLocation() - SocketTransformA.GetLocation()).Size();

		if (bRemapRange)
			return FMath::GetMappedRangeValueClamped(FVector2D(InRangeMin, InRangeMax), FVector2D(OutRangeMin, OutRangeMax), Distance);

		return Distance;
	}

	return 0.f;
}

void UALSHelpers::SetFVectorByRef(FVector & Vector, FVector NewValue) {
	Vector.X = NewValue.X;
	Vector.Y = NewValue.Y;
	Vector.Z = NewValue.Z;
}

void UALSHelpers::SetFRotatorByRef(FRotator & Rotator, FRotator NewValue) {
	Rotator.Pitch = NewValue.Pitch;
	Rotator.Roll = NewValue.Roll;
	Rotator.Yaw = NewValue.Yaw;
}