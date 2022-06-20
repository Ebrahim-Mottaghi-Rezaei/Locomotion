

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ALSStructs.h"
#include "ALSHelpers.generated.h"

/**
 *
 */
UCLASS()
class CALSV4_API UALSHelpers : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Helpers|Math")
		static FTransform SubtractTransform(FTransform A, FTransform B);
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Helpers|Math")
		static FALSComponentAndTransform LocalSpaceToWorldSpace(FALSComponentAndTransform LocalSpace);
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Helpers|Math")
		static FALSComponentAndTransform WorldSpaceToLocalSpace(FALSComponentAndTransform WorldSpace);

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
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Helpers|Animation")
		static float GetDistanceBetweenTwoSocketsAndMapRange(const USkeletalMeshComponent* Component, const FName SocketOrBoneNameA, ERelativeTransformSpace SocketSpaceA, const FName SocketOrBoneNameB, ERelativeTransformSpace SocketSpaceB, bool bRemapRange, float InRangeMin, float InRangeMax, float OutRangeMin, float OutRangeMax);

	static void SetFVectorByRef(FVector& Vector, FVector NewValue);
	static void SetFRotatorByRef(FRotator& Rotator, FRotator NewValue);

	static FString Bool2String(bool bValue);
	static FString Bool2String(bool bValue, FString trueText, FString falseText);
};
