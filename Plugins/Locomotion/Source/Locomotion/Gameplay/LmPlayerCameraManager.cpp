#include "LmPlayerCameraManager.h"
#include "../Animation/LmCameraAnimInstance.h"
#include "../LmLogger.h"
#include "LmPlayerController.h"
#include "LmControllerInterface.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include "LmCameraInterface.h"
#include <Camera/PlayerCameraManager.h>

ALmPlayerCameraManager::ALmPlayerCameraManager() {
	CameraBehaviour = CreateDefaultSubobject<USkeletalMeshComponent>(FName(TEXT("CameraBehavior")));
	CameraBehaviour->AttachToComponent(GetTransformComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	CameraBehaviour->SetHiddenInGame(true);
	CameraBehaviour->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	CameraBehaviour->SetAnimInstanceClass(ULmCameraAnimInstance::StaticClass());

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CameraMesh(TEXT("SkeletalMesh'/Game/AdvancedLocomotionV4/Blueprints/CameraSystem/Camera.Camera'"));

	if (IsValid(CameraMesh.Object) && CameraMesh.Succeeded())
		CameraBehaviour->SetSkeletalMesh(CameraMesh.Object);
	else
		ULmLogger::LogError(FString(TEXT("ALmPlayerCameraManager::ALmPlayerCameraManager Camera mesh not found")));

	AutoReceiveInput = EAutoReceiveInput::Player0;
	static ConstructorHelpers::FObjectFinder<UCurveFloat> cameraRepositionCurve(TEXT("CurveFloat'/Locomotion/Curves/CV_CameraReposition.CV_CameraReposition'"));
	if (IsValid(cameraRepositionCurve.Object) && cameraRepositionCurve.Succeeded())
		RepositionCurve = cameraRepositionCurve.Object;
	else
		ULmLogger::LogError(FString(TEXT("ALmPlayerCameraManager::ALmPlayerCameraManager CameraRepositionCurve not found")));
}

void ALmPlayerCameraManager::OnPossess(APawn* controlledPawn) {
	//Set "Controlled Pawn" when Player Controller Possesses new character. (called from Player Controller)
	ControlledPawn = controlledPawn;

	//Updated references in the Camera Behavior AnimBP.
	const auto cameraAnimInstance = Cast<ULmCameraAnimInstance>(CameraBehaviour->GetAnimInstance());

	cameraAnimInstance->playerController = GetOwningPlayerController();
	cameraAnimInstance->controlledPawn = ControlledPawn;
}

void ALmPlayerCameraManager::SetDoCollisionTest(const bool bNewDoCollisionTest) {
	//TODO Do some security checkups to make sure that the calling is from valid sources. [Cheat check from clipping]
	bDoCollisionTest = bNewDoCollisionTest;
}

TEnumAsByte<EDrawDebugTrace::Type> ALmPlayerCameraManager::GetDebugTraceType(const EDrawDebugTrace::Type ShowTraceType) const {
	const auto playerController = static_cast<ALmPlayerController*>(UGameplayStatics::GetPlayerController(this, 0));
	if (playerController && playerController->GetClass()->ImplementsInterface(ULmControllerInterface::StaticClass())) {
		const bool bShowTraces = ILmControllerInterface::Execute_GetDebugInfo(playerController).bShowTraces;
		return bShowTraces ? ShowTraceType : EDrawDebugTrace::None;
	}

	return EDrawDebugTrace::None;
}

//Get an Anim Curve value from the Player Camera Behavior AnimBP to use as a parameter in the custom camera behavior calculations
float ALmPlayerCameraManager::GetCameraBehaviourParam(const FName CurveName) const {
	if (!CameraBehaviour) {
		ULmLogger::LogError(TEXT("ALmPlayerCameraManager::GetCameraBehaviourParam | Camera Behaviour is null."));
		return 0.0f;
	}

	const auto* animInstance = CameraBehaviour->GetAnimInstance();
	return animInstance ? animInstance->GetCurveValue(CurveName) : 0.0f;
}

FVector ALmPlayerCameraManager::CalculateAxisIndependentLag(const FVector CurrentLocation, const FVector TargetLocation, FRotator CameraRotation, const FVector LagSpeed) const {
	CameraRotation.Pitch = 0.0f;
	CameraRotation.Roll = 0.0f;

	const FVector uv1 = CameraRotation.UnrotateVector(CurrentLocation);
	const FVector uv2 = CameraRotation.UnrotateVector(TargetLocation);

	const float deltatime = GetWorld()->GetDeltaSeconds();

	const float x = UKismetMathLibrary::FInterpTo(uv1.X, uv2.X, deltatime, LagSpeed.X);
	const float y = UKismetMathLibrary::FInterpTo(uv1.Y, uv2.Y, deltatime, LagSpeed.Y);
	const float z = UKismetMathLibrary::FInterpTo(uv1.Z, uv2.Z, deltatime, LagSpeed.Z);

	return  CameraRotation.RotateVector(FVector(x, y, z));
}

FLmCameraResult ALmPlayerCameraManager::CustomCameraBehaviour() {
	FTransform PivotTarget;
	FVector FPTarget;
	float TPFOV;
	float FPFOV;

	//Step 1: Get Camera Parameters from CharacterBP via the Camera Interface
	if (ControlledPawn && ControlledPawn->GetClass()->ImplementsInterface(ULmCameraInterface::StaticClass())) {
		PivotTarget = ILmCameraInterface::Execute_Get3PPivotTarget(ControlledPawn);
		FPTarget = ILmCameraInterface::Execute_GetFPCameraTarget(ControlledPawn);
		const auto cameraParams = ILmCameraInterface::Execute_GetCameraParameters(ControlledPawn);
		TPFOV = cameraParams.TP_FOV;
		FPFOV = cameraParams.FP_FOV;
	}

	//Step 2: Calculate Target Camera Rotation. Use the Control Rotation and interpolate for smooth camera rotation.
	const FRotator rotation = FMath::RInterpTo(GetCameraRotation(), GetOwningPlayerController()->GetControlRotation(), UGameplayStatics::GetWorldDeltaSeconds(this), GetCameraBehaviourParam(FName(TEXT("RotationLagSpeed"))));
	TargetCameraRotation = UKismetMathLibrary::RLerp(rotation, DebugViewRotation, GetCameraBehaviourParam(FName(TEXT("Override_Debug"))), true);

	//Step 3: Calculate the Smoothed Pivot Target (Orange Sphere). Get the 3P Pivot Target (Green Sphere) and interpolate using axis independent lag for maximum control.
	const FVector LagSpeeds = FVector(GetCameraBehaviourParam(FName(TEXT("PivotLagSpeed_X"))), GetCameraBehaviourParam(FName(TEXT("PivotLagSpeed_Y"))), GetCameraBehaviourParam(FName(TEXT("PivotLagSpeed_Z"))));
	const FVector axisIndependentLag = CalculateAxisIndependentLag(SmoothedPivotTarget.GetLocation(), PivotTarget.GetLocation(), TargetCameraRotation, LagSpeeds);

	SmoothedPivotTarget = FTransform(PivotTarget.GetRotation().Rotator(), axisIndependentLag);

	//Step 4: Calculate Pivot Location (BlueSphere). Get the Smoothed Pivot Target and apply local offsets for further camera control.
	const auto tmpRotation = SmoothedPivotTarget.GetRotation().Rotator();

	PivotLocation = SmoothedPivotTarget.GetLocation() +
		UKismetMathLibrary::GetForwardVector(tmpRotation) * GetCameraBehaviourParam(FName(TEXT("PivotOffset_X"))) +
		UKismetMathLibrary::GetRightVector(tmpRotation) * GetCameraBehaviourParam(FName(TEXT("PivotOffset_Y"))) +
		UKismetMathLibrary::GetUpVector(tmpRotation) * GetCameraBehaviourParam(FName(TEXT("PivotOffset_Z")));

	//Step 5: Calculate Target Camera Location. Get the Pivot location and apply camera relative offsets.
	TargetCameraLocation = UKismetMathLibrary::VLerp(
		PivotLocation +
		GetCameraBehaviourParam(FName(TEXT("CameraOffset_X"))) * UKismetMathLibrary::GetForwardVector(TargetCameraRotation) +
		GetCameraBehaviourParam(FName(TEXT("CameraOffset_Y"))) * UKismetMathLibrary::GetRightVector(TargetCameraRotation) +
		GetCameraBehaviourParam(FName(TEXT("CameraOffset_Z"))) * UKismetMathLibrary::GetUpVector(TargetCameraRotation),
		PivotTarget.GetLocation() + DebugViewOffset,
		GetCameraBehaviourParam(FName(TEXT("Override_Debug")))
	);

	//Step 6: Trace for an object between the camera and character to apply a corrective offset. Trace origins are set within the Character BP via the Camera Interface. Functions like the normal spring arm, but can allow for different trace origins regardless of the pivot.
	if (bDoCollisionTest && IsValid(ControlledPawn)) {
		if (ControlledPawn->GetClass()->ImplementsInterface(ULmCameraInterface::StaticClass())) {

			auto traceParams = ILmCameraInterface::Execute_Get3PTraceParameters(ControlledPawn);

			FHitResult HitResult;

			UKismetSystemLibrary::SphereTraceSingle(this, traceParams.TraceOrigin, TargetCameraLocation, traceParams.TraceRadius, traceParams.TraceChannel, false, ActorsToIgnore, GetDebugTraceType(EDrawDebugTrace::ForOneFrame), HitResult, true);

			if (HitResult.bBlockingHit) {
				repositionAlpha += GetWorld()->GetDeltaSeconds();
				TargetCameraLocation = UKismetMathLibrary::VLerp(TargetCameraLocation, HitResult.Location - HitResult.TraceEnd + TargetCameraLocation, RepositionCurve->GetFloatValue(repositionAlpha));
			} else {
				repositionAlpha = 0.0f;
			}
		}
	}

	//Step 7: Draw Debug Shapes.
	if (GetOwningPlayerController() && GetOwningPlayerController()->GetClass()->ImplementsInterface(ULmControllerInterface::StaticClass())) {
		if (ILmControllerInterface::Execute_GetDebugInfo(GetOwningPlayerController()).bShowDebugShapes) {
			UKismetSystemLibrary::DrawDebugSphere(this, PivotTarget.GetLocation(), 16.0f, 8, FColor::Green, 0.f, 0.5f);

			UKismetSystemLibrary::DrawDebugSphere(this, SmoothedPivotTarget.GetLocation(), 16.0f, 8, FColor::Orange, 0.f, 0.5f);

			UKismetSystemLibrary::DrawDebugSphere(this, PivotLocation, 16.0f, 8, FColor::FromHex(FString(TEXT("00AAFFFF"))), 0.f, 0.5f);

			UKismetSystemLibrary::DrawDebugLine(this, SmoothedPivotTarget.GetLocation(), PivotTarget.GetLocation(), FColor::FromHex(FString(TEXT("00AAFFFF"))), 0.f, 1.0f);

			UKismetSystemLibrary::DrawDebugLine(this, PivotLocation, SmoothedPivotTarget.GetLocation(), FColor::Cyan, 0.f, 1.0f);
		}
	}

	//Step 8: Lerp First Person Override and return target camera parameters.
	FTransform aTransform = FTransform(TargetCameraRotation, TargetCameraLocation);
	FTransform bTransform = FTransform(TargetCameraRotation, FPTarget);
	FTransform cTransform = FTransform(DebugViewRotation, TargetCameraLocation);

	FTransform retValue = UKismetMathLibrary::TLerp(UKismetMathLibrary::TLerp(aTransform, bTransform, GetCameraBehaviourParam(FName(TEXT("Weight_FirstPerson")))),
		cTransform, GetCameraBehaviourParam(FName(TEXT("Override_Debug"))));

	return FLmCameraResult(retValue.GetLocation(), retValue.Rotator(), FMath::Lerp(TPFOV, FPFOV, GetCameraBehaviourParam(FName(TEXT("Weight_FirstPerson")))));
}