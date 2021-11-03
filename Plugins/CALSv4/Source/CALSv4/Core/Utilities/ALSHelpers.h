#pragma once
#include "CoreMinimal.h"
#include "CALSv4/Data/ALSStructs.h"

template<class T>
class ALSGeneralHelpers {
public:
	static T GetItemInArray(TArray<T>Items, const uint8 SelectedIndex, const bool bNext);
	static T GetItemInArray(TArray<T>Items, const T selectedItem, const bool bNext);
};

class ALSHelpers {
public:
	static FTransform SubtractTransform(FTransform A, FTransform B);
	static FALSComponentAndTransform LocalSpaceToWorldSpace(FALSComponentAndTransform localSpace);
	static FALSComponentAndTransform WorldSpaceToLocalSpace(FALSComponentAndTransform localSpace);

	/**
	 *	Computes the distance between two bones / sockets and can remap the range.
	 *
	 *	@param Component The skeletal component to look for the sockets / bones within
	 *	@param SocketOrBoneNameA The name of the first socket / bone
	 *	@param SocketSpaceA The space for the first socket / bone
	 *	@param SocketOrBoneNameB The name of the second socket / bone
	 *	@param SocketSpaceB The space for the second socket / bone
	 *	@param bRemapRange If set to true, the distance will be remapped using the range parameters
	 *	@param InRangeMin The minimum for the input range (commonly == 0.0)
	 *	@param InRangeMax The maximum for the input range (the max expected distance)
	 *	@param OutRangeMin The minimum for the output range (commonly == 0.0)
	 *	@param OutRangeMax The maximum for the output range (commonly == 1.0)
	 */
	static float GetDistanceBetweenTwoSocketsAndMapRange(const USkeletalMeshComponent* Component, const FName SocketOrBoneNameA, ERelativeTransformSpace SocketSpaceA, const FName SocketOrBoneNameB, ERelativeTransformSpace SocketSpaceB, bool bRemapRange, float InRangeMin, float InRangeMax, float OutRangeMin, float OutRangeMax);
};