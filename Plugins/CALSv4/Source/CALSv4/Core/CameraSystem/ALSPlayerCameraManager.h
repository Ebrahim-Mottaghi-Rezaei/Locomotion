#pragma once

#include "CoreMinimal.h"
#include "CALSv4/Data/ALSStructs.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ALSPlayerCameraManager.generated.h"

UCLASS()
class CALSV4_API AALSPlayerCameraManager : public APlayerCameraManager {
	GENERATED_BODY()

		AALSPlayerCameraManager();
public:
	virtual void OnPossess(APawn* ControlledPawn);
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		USkeletalMeshComponent* CameraBehaviour;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FVector DebugViewOffset;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FRotator DebugViewRotation;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FVector RootLocation;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FVector PivotLocation;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FVector TargetCameraLocation;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FRotator TargetCameraRotation;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FTransform SmoothedPivotTarget;

	APawn* PawnInControl;

	TEnumAsByte<EDrawDebugTrace::Type> GetDebugTraceType(EDrawDebugTrace::Type ShowTraceType);

	float GetCameraBehaviourParam(FName CurveName);

	FVector CalculateAxisIndependentLag(FVector CurrentLocation, FVector TargetLocation, FRotator CameraRotation, FVector LagSpeed);

	FALSCameraBehaviourResult CustomCameraBehaviour();
private:
	TArray<AActor*> _actorsToIgnore;
};
