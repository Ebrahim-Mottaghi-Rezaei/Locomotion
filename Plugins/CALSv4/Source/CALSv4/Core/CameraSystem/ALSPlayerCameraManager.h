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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USkeletalMeshComponent* CameraBehaviour;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Camera Manager")
		FVector DebugViewOffset = FVector(350.0f, 0.0f, 50.0f);;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Camera Manager")
		FRotator DebugViewRotation = FRotator(-5.0f, 180.0f, 0.0f);;
	UPROPERTY(BlueprintReadWrite, Category = "Advanced Locomotion System|Camera Manager")
		FVector RootLocation;
	UPROPERTY(BlueprintReadWrite, Category = "Advanced Locomotion System|Camera Manager")
		FVector PivotLocation;
	UPROPERTY(BlueprintReadWrite, Category = "Advanced Locomotion System|Camera Manager")
		FVector TargetCameraLocation;
	UPROPERTY(BlueprintReadWrite, Category = "Advanced Locomotion System|Camera Manager")
		FRotator TargetCameraRotation;
	UPROPERTY(BlueprintReadWrite, Category = "Advanced Locomotion System|Camera Manager")
		FTransform SmoothedPivotTarget;

	APawn* PawnInControl;

	TEnumAsByte<EDrawDebugTrace::Type> GetDebugTraceType(EDrawDebugTrace::Type ShowTraceType);

	float GetCameraBehaviourParam(FName CurveName);

	FVector CalculateAxisIndependentLag(FVector CurrentLocation, FVector TargetLocation, FRotator CameraRotation, FVector LagSpeed);
	
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Camera Manager")
		FALSCameraBehaviourResult CustomCameraBehaviour();

	TArray<AActor*> ActorsToIgnore;	
};
