#pragma once

#include <Curves/CurveFloat.h>
#include <Kismet/KismetSystemLibrary.h>
#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "Locomotion/DataTypes/LmStructs.h"
#include "LmPlayerCameraManager.generated.h"

UCLASS( Category = "Locomotion" )
class LOCOMOTION_API ALmPlayerCameraManager : public APlayerCameraManager {
	GENERATED_BODY()

public:
	ALmPlayerCameraManager();

	virtual void OnPossess(APawn* ControlledPawn);

protected:
	UPROPERTY( BlueprintReadOnly , EditInstanceOnly , Category = "Locomotion" )
	bool bDoCollisionTest = true;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Locomotion" )
	USkeletalMeshComponent* CameraBehaviour;
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Locomotion" )
	UCurveFloat* RepositionCurve;

	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion" )
	FVector DebugViewOffset = FVector( 350.0f , 0.0f , 50.0f );;
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Locomotion" )
	FRotator DebugViewRotation = FRotator( -5.0f , 180.0f , 0.0f );;
	UPROPERTY( BlueprintReadWrite , Category = "Locomotion" )
	FVector RootLocation;
	UPROPERTY( BlueprintReadWrite , Category = "Locomotion" )
	FVector PivotLocation;
	UPROPERTY( BlueprintReadWrite , Category = "Locomotion" )
	FVector TargetCameraLocation;
	UPROPERTY( BlueprintReadWrite , Category = "Locomotion" )
	FRotator TargetCameraRotation;
	UPROPERTY( BlueprintReadWrite , Category = "Locomotion" )
	FTransform SmoothedPivotTarget;

	UFUNCTION( BlueprintCallable , Category = "Locomotion" )
	FLmCameraResult CustomCameraBehaviour();

	FVector CalculateAxisIndependentLag(const FVector& CurrentLocation, const FVector& TargetLocation, FRotator CameraRotation, const FVector& LagSpeed) const;

	float GetCameraBehaviourParam(FName CurveName) const;

	TEnumAsByte<EDrawDebugTrace::Type> GetDebugTraceType(EDrawDebugTrace::Type ShowTraceType) const;

	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;
	UPROPERTY()
	APawn* ControlledPawn;

public:
	UFUNCTION( BlueprintCallable , Category = "Locomotion" )
	void SetDoCollisionTest(const bool bNewDoCollisionTest);

private:
	float RepositionAlpha;
};
