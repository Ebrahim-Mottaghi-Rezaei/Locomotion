#pragma once

#include "CoreMinimal.h"
#include "LmBaseCharacter.h"
#include "LmCharacter.generated.h"

UCLASS()
class LOCOMOTION_API ALmCharacter : public ALmBaseCharacter {
	GENERATED_BODY()

public:
	ALmCharacter();

protected:
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion" )
	UChildActorComponent* HoldingObject;

	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion" )
	FDataTableRowHandle HoldingActorsDataTable;

	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Mantle" )
	FLmMantleAsset Mantle2mDefault;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Mantle" )
	FLmMantleAsset Mantle1mDefault;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Mantle" )
	FLmMantleAsset Mantle1mRH;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Mantle" )
	FLmMantleAsset Mantle1mLH;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Mantle" )
	FLmMantleAsset Mantle1m2H;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Mantle" )
	FLmMantleAsset Mantle1mBox;

	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Roll" )
	UAnimMontage* LandRoll_Default;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Roll" )
	UAnimMontage* LandRoll_RH;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Roll" )
	UAnimMontage* LandRoll_LH;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|Roll" )
	UAnimMontage* LandRoll_2H;

	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|GetUp" )
	UAnimMontage* GetupFront_Default;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|GetUp" )
	UAnimMontage* GetupFront_RH;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|GetUp" )
	UAnimMontage* GetupFront_LH;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|GetUp" )
	UAnimMontage* GetupFront_2H;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|GetUp" )
	UAnimMontage* GetupBack_Default;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|GetUp" )
	UAnimMontage* GetupBack_RH;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|GetUp" )
	UAnimMontage* GetupBack_LH;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion|GetUp" )
	UAnimMontage* GetupBack_2H;

	UFUNCTION( BlueprintCallable , Category = "Locomotion|Held Object" )
	void UpdateHeldObject();

	UFUNCTION( BlueprintCallable , Category = "Locomotion|Held Object" )
	void SetHeldObject(const FLmHoldingInstance NewHoldingObject);

	UFUNCTION( BlueprintCallable , Category = "Locomotion|Held Object" )
	void ClearHeldObject();

	UFUNCTION( BlueprintCallable , Category = "Locomotion|Held Object" )
	virtual void AttachToHand(const FLmHoldingInstance NewHoldingObject);

	UFUNCTION( BlueprintCallable , Category = "Locomotion|State Changes" )
	virtual void SetOverlayState_Implementation(ELmOverlayState NewOverlayState) override;

	virtual FTransform Get3PPivotTarget_Implementation() override;

	virtual FLmTraceParams Get3PTraceParameters_Implementation() override;

	virtual UAnimMontage* GetRollAnimation() override;

	virtual FLmMantleAsset GetMantleAsset(ELmMantleType MantleType) override;

	virtual void MantleStart(float MantleHeight, FLmComponentAndTransform MantleLedgeWS, ELmMantleType MantleType) override;

	virtual void MantleEnd() override;

	virtual UAnimMontage* GetGetupAnimation(const bool bIsRagdollFacedUp) override;

	virtual void RagdollStart() override;

	virtual void RagdollEnd() override;
};
