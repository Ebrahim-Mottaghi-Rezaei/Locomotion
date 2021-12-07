#include "ALSPlayerCameraManager.h"
#include "ALSPlayerCameraBehaviour.h"
#include "CALSv4/Core/Interfaces/ALSCameraInterface.h"
#include "CALSv4/Core/Interfaces/ALSControllerInterface.h"
#include "CALSv4/Core/Player/ALSPlayerController.h"
#include "CALSv4/Core/Utilities/ALSHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AALSPlayerCameraManager::AALSPlayerCameraManager() {
	CameraBehaviour = CreateDefaultSubobject<USkeletalMeshComponent>(FName(TEXT("CameraBehavior")));
	CameraBehaviour->AttachToComponent(GetTransformComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	CameraBehaviour->SetHiddenInGame(true);
	CameraBehaviour->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	CameraBehaviour->SetAnimInstanceClass(UALSPlayerCameraBehaviour::StaticClass());

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CameraMesh(TEXT("SkeletalMesh'/Game/AdvancedLocomotionV4/Blueprints/CameraSystem/Camera.Camera'"));
	if (IsValid(CameraMesh.Object) && CameraMesh.Succeeded())
		CameraBehaviour->SetSkeletalMesh(CameraMesh.Object);
	else
		UALSLogger::LogError(FString(TEXT("SkeletalMesh not found: Camera")));

	AutoReceiveInput = EAutoReceiveInput::Player0;
}

void AALSPlayerCameraManager::OnPossess(APawn* ControlledPawn) {
	//Set "Controlled Pawn" when Player Controller Possesses new character. (called from Player Controller)
	PawnInControl = ControlledPawn;

	//Updated references in the Camera Behavior AnimBP.
	const auto cameraAnimInstance = Cast<UALSPlayerCameraBehaviour>(CameraBehaviour->GetAnimInstance());

	cameraAnimInstance->playerController = GetOwningPlayerController();
	cameraAnimInstance->controlledPawn = PawnInControl;
}

TEnumAsByte<EDrawDebugTrace::Type> AALSPlayerCameraManager::GetDebugTraceType(EDrawDebugTrace::Type ShowTraceType) {
	auto* pc = static_cast<AALSPlayerController*>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	const UALSControllerInterface* Interface = Cast<UALSControllerInterface>(pc);

	if (IsValid(pc) && IsValid(Interface))
		return pc->GetDebugInfo_Implementation().bShowTraces ? ShowTraceType : EDrawDebugTrace::None;

	return EDrawDebugTrace::None;
}

//Get an Anim Curve value from the Player Camera Behavior AnimBP to use as a parameter in the custom camera behavior calculations
float AALSPlayerCameraManager::GetCameraBehaviourParam(FName CurveName) {
	if (!CameraBehaviour) 	{
		UALSLogger::LogError(TEXT("Camera Manager - Camera Behaviour is null."));
		return 0.0f;
	}


	const auto* animInstance = CameraBehaviour->GetAnimInstance();
	return IsValid(animInstance) ? animInstance->GetCurveValue(CurveName) : 0.0f;
}

FVector AALSPlayerCameraManager::CalculateAxisIndependentLag(FVector CurrentLocation, FVector TargetLocation, FRotator CameraRotation, FVector LagSpeed) {
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

FALSCameraBehaviourResult AALSPlayerCameraManager::CustomCameraBehaviour() {
	FTransform PivotTarget;
	FVector FPTarget;
	float TPFOV;
	float FPFOV;

	//Step 1: Get Camera Parameters from CharacterBP via the Camera Interface
	if (PawnInControl && PawnInControl->GetClass()->ImplementsInterface(UALSCameraInterface::StaticClass())) {
		PivotTarget = IALSCameraInterface::Execute_Get3PPivotTarget(PawnInControl);
		FPTarget = IALSCameraInterface::Execute_GetFPCameraTarget(PawnInControl);
		const auto cameraParams = IALSCameraInterface::Execute_GetCameraParameters(PawnInControl);
		TPFOV = cameraParams.TP_FOV;
		FPFOV = cameraParams.FP_FOV;
	}

	//Step 2: Calculate Target Camera Rotation. Use the Control Rotation and interpolate for smooth camera rotation.
	const FRotator rotation = FMath::RInterpTo(GetCameraRotation(), GetOwningPlayerController()->GetControlRotation(), GetWorld()->GetDeltaSeconds(), GetCameraBehaviourParam(FName(TEXT("RotationLagSpeed"))));
	TargetCameraRotation = UKismetMathLibrary::RLerp(rotation, DebugViewRotation, GetCameraBehaviourParam(FName(TEXT("Override_Debug"))), true);

	//Step 3: Calculate the Smoothed Pivot Target (Orange Sphere). Get the 3P Pivot Target (Green Sphere) and interpolate using axis independent lag for maximum control.
	const FVector LagSpeeds = FVector(GetCameraBehaviourParam(FName(TEXT("PivotLagSpeed_X"))), GetCameraBehaviourParam(FName(TEXT("PivotLagSpeed_Y"))), GetCameraBehaviourParam(FName(TEXT("PivotLagSpeed_Z"))));
	const FVector axisIndependentLag = CalculateAxisIndependentLag(SmoothedPivotTarget.GetLocation(), PivotTarget.GetLocation(), TargetCameraRotation, LagSpeeds);

	SmoothedPivotTarget = FTransform(PivotTarget.GetRotation().Rotator(), axisIndependentLag);

	//Step 4: Calculate Pivot Location (BlueSphere). Get the Smoothed Pivot Target and apply local offsets for further camera control.
	PivotLocation = SmoothedPivotTarget.GetLocation() +
		UKismetMathLibrary::GetForwardVector(SmoothedPivotTarget.Rotator()) * GetCameraBehaviourParam(FName(TEXT("PivotOffset_X"))) +
		UKismetMathLibrary::GetRightVector(SmoothedPivotTarget.Rotator()) * GetCameraBehaviourParam(FName(TEXT("PivotOffset_Y"))) +
		UKismetMathLibrary::GetUpVector(SmoothedPivotTarget.Rotator()) * GetCameraBehaviourParam(FName(TEXT("PivotOffset_Z")));

	//Step 5: Calculate Target Camera Location. Get the Pivot location and apply camera relative offsets.
	TargetCameraLocation = FMath::Lerp(
		GetCameraBehaviourParam(FName(TEXT("CameraOffset_X"))) * UKismetMathLibrary::GetForwardVector(TargetCameraRotation) +
		GetCameraBehaviourParam(FName(TEXT("CameraOffset_Y"))) * UKismetMathLibrary::GetRightVector(TargetCameraRotation) +
		GetCameraBehaviourParam(FName(TEXT("CameraOffset_Z"))) * UKismetMathLibrary::GetUpVector(TargetCameraRotation),
		PivotTarget.GetLocation() + DebugViewOffset,
		GetCameraBehaviourParam(FName(TEXT("Override_Debug")))
	);

	//Step 6: Trace for an object between the camera and character to apply a corrective offset. Trace origins are set within the Character BP via the Camera Interface. Functions like the normal spring arm, but can allow for different trace origins regardless of the pivot.
	if (PawnInControl && PawnInControl->GetClass()->ImplementsInterface(UALSCameraInterface::StaticClass())) {
		auto traceParams = IALSCameraInterface::Execute_Get3PTraceParameters(PawnInControl);
		FHitResult HitResult;
		UKismetSystemLibrary::SphereTraceSingle(GetWorld(), traceParams.TraceOrigin, TargetCameraLocation, traceParams.TraceRadius, traceParams.TraceChannel.GetValue(), false, ActorsToIgnore, EDrawDebugTrace::Type::ForOneFrame, HitResult, true);

		if (HitResult.bBlockingHit && !HitResult.bStartPenetrating) {
			TargetCameraLocation = HitResult.Location - HitResult.TraceEnd + TargetCameraLocation;
		}
	}

	//Step 7: Draw Debug Shapes.
	if (GetOwningPlayerController() && GetOwningPlayerController()->GetClass()->ImplementsInterface(UALSControllerInterface::StaticClass())) {
		if (IALSControllerInterface::Execute_GetDebugInfo(GetOwningPlayerController()).bShowDebugShapes) {
			UKismetSystemLibrary::DrawDebugSphere(this, PivotTarget.GetLocation(), 16.0f, 8, FColor::FromHex(FString(TEXT("00FF00FF"))), 0.f, 0.5f);

			UKismetSystemLibrary::DrawDebugSphere(this, SmoothedPivotTarget.GetLocation(), 16.0f, 8, FColor::FromHex(FString(TEXT("FF2A00FF"))), 0.f, 0.5f);

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

	return FALSCameraBehaviourResult(retValue.GetLocation(), retValue.Rotator(), FMath::Lerp(TPFOV, FPFOV, GetCameraBehaviourParam(FName(TEXT("Weight_FirstPerson")))));
}
