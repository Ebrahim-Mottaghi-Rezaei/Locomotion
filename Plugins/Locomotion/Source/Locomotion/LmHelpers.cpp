


#include "LmHelpers.h"
#include <Kismet/KismetMathLibrary.h>
#include <Components/SkeletalMeshComponent.h>

FTransform ULmHelpers::AddTransform(const FTransform A, const FTransform B) {
	FRotator ARotator = A.Rotator();
	FRotator BRotator = B.Rotator();
	return FTransform(FRotator(ARotator.Pitch + BRotator.Pitch, ARotator.Yaw + BRotator.Yaw, ARotator.Roll + BRotator.Roll), A.GetLocation() + B.GetLocation(), A.GetScale3D() + B.GetScale3D());
}

FTransform ULmHelpers::SubtractTransform(const FTransform A, const FTransform B) {
	FRotator ARotator = A.Rotator();
	FRotator BRotator = B.Rotator();
	return FTransform(FRotator(ARotator.Pitch - BRotator.Pitch, ARotator.Yaw - BRotator.Yaw, ARotator.Roll - BRotator.Roll), A.GetLocation() - B.GetLocation(), A.GetScale3D() - B.GetScale3D());
}

FLmComponentAndTransform ULmHelpers::LocalSpaceToWorldSpace(const FLmComponentAndTransform LocalSpace) {
	return FLmComponentAndTransform(UKismetMathLibrary::ComposeTransforms(LocalSpace.Transform, LocalSpace.Component->GetComponentToWorld()), LocalSpace.Component);
}

FLmComponentAndTransform ULmHelpers::WorldSpaceToLocalSpace(const FLmComponentAndTransform WorldSpace) {
	return FLmComponentAndTransform(UKismetMathLibrary::ComposeTransforms(WorldSpace.Transform, WorldSpace.Component->GetComponentToWorld().Inverse()), WorldSpace.Component);
}

float ULmHelpers::GetDistanceBetweenTwoSocketsAndMapRange(const USkeletalMeshComponent* Component, const FName SocketOrBoneNameA, ERelativeTransformSpace SocketSpaceA, const FName SocketOrBoneNameB, const ERelativeTransformSpace SocketSpaceB, const bool bRemapRange, const float InRangeMin, const float InRangeMax, const float OutRangeMin, const float OutRangeMax) {
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

void ULmHelpers::SetFVectorByRef(FVector& Vector, FVector NewValue) {
	Vector.X = NewValue.X;
	Vector.Y = NewValue.Y;
	Vector.Z = NewValue.Z;
}

void ULmHelpers::SetFRotatorByRef(FRotator& Rotator, FRotator NewValue) {
	Rotator.Pitch = NewValue.Pitch;
	Rotator.Roll = NewValue.Roll;
	Rotator.Yaw = NewValue.Yaw;
}

FString ULmHelpers::Bool2String(bool bValue) {
	return bValue ? TEXT("Yes") : TEXT("No");
}

FString ULmHelpers::Bool2String(bool bValue, FString trueText, FString falseText) {
	return bValue ? trueText : falseText;
}