#include "ALSHelpers.h"
#include "Kismet/KismetMathLibrary.h"

template <class T>
T ALSGeneralHelpers<T>::GetItemInArray(TArray<T> Items, const uint8 SelectedIndex, const bool bNext) {
	int Index;

	if (bNext)
		Index = SelectedIndex + 1 < Items.Num() ? SelectedIndex + 1 : 0;
	else
		Index = SelectedIndex - 1 >= 0 ? SelectedIndex - 1 : Items.Num();

	return Items[Index];
}

template <class T>
T ALSGeneralHelpers<T>::GetItemInArray(TArray<T> Items, const T selectedItem, const bool bNext) {
	return GetItemInArray(Items, Items.Find(selectedItem), bNext);
}

FTransform ALSHelpers::SubtractTransform(const FTransform A, const FTransform B) {
	return FTransform(FRotator(A.Rotator().Pitch - B.Rotator().Pitch, A.Rotator().Yaw - B.Rotator().Yaw, A.Rotator().Roll - B.Rotator().Roll), A.GetLocation() - B.GetLocation(), A.GetScale3D() - B.GetScale3D());
}

FALSComponentAndTransform ALSHelpers::LocalSpaceToWorldSpace(FALSComponentAndTransform localSpace) {
	return FALSComponentAndTransform(UKismetMathLibrary::ComposeTransforms(localSpace.Transform, localSpace.Component->GetComponentTransform()), localSpace.Component);
}

FALSComponentAndTransform ALSHelpers::WorldSpaceToLocalSpace(FALSComponentAndTransform worldSpace) {
	return FALSComponentAndTransform(UKismetMathLibrary::ComposeTransforms(worldSpace.Transform, worldSpace.Component->GetComponentTransform().Inverse()), worldSpace.Component);
}

float ALSHelpers::GetDistanceBetweenTwoSocketsAndMapRange(const USkeletalMeshComponent* Component,
	const FName SocketOrBoneNameA, const ERelativeTransformSpace SocketSpaceA, const FName SocketOrBoneNameB,
	const ERelativeTransformSpace SocketSpaceB, const bool bRemapRange, const float InRangeMin, const float InRangeMax, const float OutRangeMin,
	const float OutRangeMax) {
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
