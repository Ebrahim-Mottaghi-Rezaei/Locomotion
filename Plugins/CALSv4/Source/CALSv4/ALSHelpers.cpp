


#include "ALSHelpers.h"
#include <Kismet/KismetMathLibrary.h>

FTransform UALSHelpers::SubtractTransform(const FTransform A, const FTransform B) {
	return FTransform(FRotator(A.Rotator().Pitch - B.Rotator().Pitch, A.Rotator().Yaw - B.Rotator().Yaw, A.Rotator().Roll - B.Rotator().Roll), A.GetLocation() - B.GetLocation(), A.GetScale3D() - B.GetScale3D());
}

FALSComponentAndTransform UALSHelpers::LocalSpaceToWorldSpace(const FALSComponentAndTransform LocalSpace) {
	return FALSComponentAndTransform(UKismetMathLibrary::ComposeTransforms(LocalSpace.Transform, LocalSpace.Component->GetComponentToWorld()), LocalSpace.Component);
}

FALSComponentAndTransform UALSHelpers::WorldSpaceToLocalSpace(const FALSComponentAndTransform WorldSpace) {
	return FALSComponentAndTransform(UKismetMathLibrary::ComposeTransforms(WorldSpace.Transform, WorldSpace.Component->GetComponentToWorld().Inverse()), WorldSpace.Component);
}

float UALSHelpers::GetDistanceBetweenTwoSocketsAndMapRange(const USkeletalMeshComponent* Component, const FName SocketOrBoneNameA, ERelativeTransformSpace SocketSpaceA, const FName SocketOrBoneNameB, const ERelativeTransformSpace SocketSpaceB, const bool bRemapRange, const float InRangeMin, const float InRangeMax, const float OutRangeMin, const float OutRangeMax) {
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

void UALSHelpers::SetFVectorByRef(FVector& Vector, FVector NewValue) {
	Vector.X = NewValue.X;
	Vector.Y = NewValue.Y;
	Vector.Z = NewValue.Z;
}

void UALSHelpers::SetFRotatorByRef(FRotator& Rotator, FRotator NewValue) {
	Rotator.Pitch = NewValue.Pitch;
	Rotator.Roll = NewValue.Roll;
	Rotator.Yaw = NewValue.Yaw;
}

FString UALSHelpers::Bool2String(bool bValue) {
	return bValue ? TEXT("Yes") : TEXT("No");
}

FString UALSHelpers::Bool2String(bool bValue, FString trueText, FString falseText) {
	return bValue ? trueText : falseText;
}