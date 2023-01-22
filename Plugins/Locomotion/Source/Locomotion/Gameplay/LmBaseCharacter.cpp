#include "LmBaseCharacter.h"
#include <Components/CapsuleComponent.h>
#include <AI/NavigationSystemBase.h>
#include "../LmLogger.h"
#include <ClothingSystemRuntimeNv/Public/ClothingSimulationFactoryNv.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/Character.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "../LmHelpers.h"
#include "../Animation/LmCharacterAnimationInterface.h"
#include <Curves/CurveVector.h>
#include "../LmStructs.h"
#include "LmControllerInterface.h"
#include <GameFramework/Pawn.h>
#include <GameFramework/Actor.h>

ALmBaseCharacter::ALmBaseCharacter() {
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	Tags.Add(TEXT("ALS_Character"));

	mantleTimeline = CreateDefaultSubobject<UTimelineComponent>(FName("MantleTimeline"));
	mantleTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
	mantleTimeline->SetTickGroup(ETickingGroup::TG_PrePhysics);

	const auto capsule = GetCapsuleComponent();
	capsule->SetCapsuleHalfHeight(90.0f);
	capsule->SetCapsuleRadius(30.0f);
	capsule->SetAreaClassOverride(FNavigationSystem::GetDefaultObstacleArea());
	capsule->SetCollisionProfileName(TEXT("ALS_Character"));

	const auto mesh = GetMesh();
	mesh->SetWorldLocation(FVector(0.0f, 0.0f, -92.0f));
	mesh->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> proxyMesh(TEXT("SkeletalMesh'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/Meshes/Proxy.Proxy'"));
	if (proxyMesh.Succeeded())
		mesh->SetSkeletalMesh(proxyMesh.Object);
	else
		ULmLogger::LogError("ProxyMesh not found.");

	mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mesh->SetCollisionResponseToAllChannels(ECR_Block);
	mesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	mesh->SetCollisionResponseToChannel(ECC_Climbable, ECR_Ignore);
	mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	mesh->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Ignore);
	mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

	const auto cmc = GetCharacterMovement();
	cmc->MaxAcceleration = 1500.0f;
	cmc->BrakingFrictionFactor = 0.0f;
	cmc->SetCrouchedHalfHeight(60.0f);
	cmc->MinAnalogWalkSpeed = 25.0f;
	cmc->bCanWalkOffLedgesWhenCrouching = true;
	cmc->AirControl = 0.15f;
	cmc->GetNavAgentPropertiesRef().bCanCrouch = true;
	cmc->GetNavAgentPropertiesRef().bCanFly = true;
	cmc->bRequestedMoveUseAcceleration = false;
	cmc->bRequestedMoveUseAcceleration = true;
	cmc->bRunPhysicsWithNoController = true;
	cmc->PerchRadiusThreshold = 20.0f;
	cmc->PerchAdditionalHeight = 0.0f;
	cmc->LedgeCheckThreshold = 4.0f;

	static ConstructorHelpers::FObjectFinder<UDataTable> MovementDataModel(TEXT("DataTable'/Locomotion/Data/DT_MovementModel.DT_MovementModel'"));
	if (MovementDataModel.Succeeded()) {
		MovementModel.DataTable = MovementDataModel.Object;
		MovementModel.RowName = FName("Normal");
	} else
		ULmLogger::LogError("MovementModelTable not found.");

	CurrentMovementSettings.WalkSpeed = 165.0f;
	CurrentMovementSettings.RunSpeed = 350.0f;
	CurrentMovementSettings.SprintSpeed = 600.0f;
	static ConstructorHelpers::FObjectFinder<UCurveVector> NormalMovementCurve(TEXT("CurveVector'/Game/AdvancedLocomotionV4/Data/Curves/CharacterMovementCurves/NormalMovement.NormalMovement'"));
	if (MovementDataModel.Succeeded()) {
		CurrentMovementSettings.MovementCurve = NormalMovementCurve.Object;
	} else
		ULmLogger::LogError("Normal Movement Curve not found.");

	GroundedTraceSettings.MaxLedgeHeight = 250.0f;
	GroundedTraceSettings.MinLedgeHeight = 50.0f;
	GroundedTraceSettings.ReachDistance = 75.0f;
	GroundedTraceSettings.ForwardTraceRadius = 30.0f;
	GroundedTraceSettings.DownwardTraceRadius = 30.0f;

	AutomaticTraceSettings.MaxLedgeHeight = 80.0f;
	AutomaticTraceSettings.MinLedgeHeight = 40.0f;
	AutomaticTraceSettings.ReachDistance = 50.0f;
	AutomaticTraceSettings.ForwardTraceRadius = 30.0f;
	AutomaticTraceSettings.DownwardTraceRadius = 30.0f;

	FallingTraceSettings.MaxLedgeHeight = 150.0f;
	FallingTraceSettings.MinLedgeHeight = 50.0f;
	FallingTraceSettings.ReachDistance = 70.0f;
	FallingTraceSettings.ForwardTraceRadius = 30.0f;
	FallingTraceSettings.DownwardTraceRadius = 30.0f;

	CurrentMovementSettings.WalkSpeed = 165.0;
	CurrentMovementSettings.RunSpeed = 350.0;
	CurrentMovementSettings.SprintSpeed = 600.0;
	static ConstructorHelpers::FObjectFinder<UCurveVector> MovementCurve(TEXT("CurveVector'/Game/AdvancedLocomotionV4/Data/Curves/CharacterMovementCurves/NormalMovement.NormalMovement'"));
	if (MovementCurve.Succeeded())
		CurrentMovementSettings.MovementCurve = MovementCurve.Object;
	else
		ULmLogger::LogError("Mantle_1m not found.");

	static ConstructorHelpers::FObjectFinder<UCurveVector> highMantle(TEXT("CurveVector'/Game/AdvancedLocomotionV4/Data/Curves/MantleCurves/Mantle_1m.Mantle_1m'"));
	if (highMantle.Succeeded())
		HighMantle = highMantle.Object;
	else
		ULmLogger::LogError("Mantle_1m not found.");

	static ConstructorHelpers::FObjectFinder<UCurveVector> lowMantle(TEXT("CurveVector'/Game/AdvancedLocomotionV4/Data/Curves/MantleCurves/Mantle_2m.Mantle_2m'"));
	if (lowMantle.Succeeded())
		LowMantle = lowMantle.Object;
	else
		ULmLogger::LogError("Mantle_2m not found.");

	static ConstructorHelpers::FObjectFinder<UCurveFloat> mantleTimelineCurve(TEXT("CurveFloat'/Locomotion/Data/Curves/MantleTimelineCurve.MantleTimelineCurve'"));
	if (mantleTimelineCurve.Succeeded())
		MantleTimelineCurve = mantleTimelineCurve.Object;
	else
		ULmLogger::LogError("MantleTimelineCurve not found.");
}

void ALmBaseCharacter::BeginPlay() {
	Super::BeginPlay();

	ETT_Climbable = UEngineTypes::ConvertToTraceType(ECC_Climbable);
	ETT_CameraCollisionChannel = UEngineTypes::ConvertToTraceType(CameraCollisionCheckChannel);

	//Make sure the mesh and animInstance update after the CharacterBP to ensure it gets the most recent values.
	GetMesh()->AddTickPrerequisiteActor(this);

	//Set Reference to the Main Anim Instance.
	if (IsValid(GetMesh()->GetAnimInstance()))
		animInstance = GetMesh()->GetAnimInstance();

	//Set the Movement Model
	SetMovementModel();

	//Update states to use the initial desired values.
	OnGaitChanged(DesiredGait);
	OnRotationModeChanged(DesiredRotationMode);
	OnViewModeChanged(ViewMode);
	OnOverlayStateChanged(OverlayState);
	if (DesiredStance == ELmStance::Lm_Standing) {
		UnCrouch();
	} else {
		Crouch();
	}

	//Set default rotation values.
	const FRotator rotation = GetActorRotation();
	TargetRotation = rotation;
	LastVelocityRotation = rotation;
	LastMovementInputRotation = rotation;

	//Setting up the mantle time-line
	if (MantleTimelineCurve == nullptr) {
		ULmLogger::LogError(TEXT("MantleTimelineCurve in LmBaseCharacter is null"));
	} else {
		FOnTimelineFloat MantleUpdate;
		MantleUpdate.BindUFunction(this, FName("MantleUpdate"));
		mantleTimeline->AddInterpFloat(MantleTimelineCurve, MantleUpdate);

		FOnTimelineEvent mantleTimelineFinished;
		mantleTimelineFinished.BindUFunction(this, FName("MantleEnd"));
		mantleTimeline->SetTimelineFinishedFunc(mantleTimelineFinished);
	}
}

void ALmBaseCharacter::Tick(const float DeltaTime) {
	Super::Tick(DeltaTime);

	SetEssentialValues();
	switch (MovementState) {
	case ELmMovementState::Lm_Grounded:
		//Do While On Ground
		UpdateCharacterMovement();
		UpdateGroundedRotation();
		break;
	case ELmMovementState::Lm_Mantling:
		break;
	case ELmMovementState::Lm_InAir:
		//Do while In Air
		UpdateInAirRotation();
		//Perform a mantle check if falling while movement input is pressed.
		if (bHasMovementInput)
			MantleCheck(FallingTraceSettings, EDrawDebugTrace::ForOneFrame);
		break;
	case ELmMovementState::Lm_Ragdoll:
		//Do while in Rag-doll
		RagdollUpdate();
		break;
	case ELmMovementState::Lm_None:
	default:;
		break;
	}

	CacheValues();
	DrawDebugShapes();
}

void ALmBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Checking the player input validity
	if (!IsValid(PlayerInputComponent))
		return;

	//Movement Input
	PlayerInputComponent->BindAxis(FName(TEXT("MoveForward/Backwards")), this, &ALmBaseCharacter::ReceiveMoveForwardBackwards);
	PlayerInputComponent->BindAxis(FName(TEXT("MoveRight/Left")), this, &ALmBaseCharacter::ReceiveMoveRightLeft);

	//Camera Input
	PlayerInputComponent->BindAxis(FName(TEXT("LookUp/Down")), this, &ALmBaseCharacter::PlayerCameraPitchInput);
	PlayerInputComponent->BindAxis(FName(TEXT("LookLeft/Right")), this, &ALmBaseCharacter::PlayerCameraYawInput);

	//Jump Action: Press "Jump Action" to capsuleTraceEnd the rag-doll if rag-dolling, check for a mantle if grounded or in air, stand up if crouching, or jump if standing.
	PlayerInputComponent->BindAction(FName(TEXT("JumpAction")), IE_Pressed, this, &ALmBaseCharacter::PlayerJumpPressedInput);
	PlayerInputComponent->BindAction(FName(TEXT("JumpAction")), IE_Released, this, &ALmBaseCharacter::StopJumping);

	//Stance Action: Press "Stance Action" to toggle Standing / Crouching, double tap to Roll.
	PlayerInputComponent->BindAction(FName(TEXT("StanceAction")), IE_Pressed, this, &ALmBaseCharacter::PlayerStanceActionInput);

	//Gait Actions Type 1: Press "Walk Action" to toggle walking/running, hold "Sprint Action" to sprint.
	PlayerInputComponent->BindAction(FName(TEXT("WalkAction")), IE_Pressed, this, &ALmBaseCharacter::PlayerWalkBegin);
	PlayerInputComponent->BindAction(FName(TEXT("WalkAction")), IE_Released, this, &ALmBaseCharacter::PlayerWalkEnd);

	//Gait Action Type 2 (Unused): Hold "Sprint Action" to run, double tap and hold to sprint.
	PlayerInputComponent->BindAction(FName(TEXT("SprintAction")), IE_Pressed, this, &ALmBaseCharacter::PlayerSprintBegin);
	PlayerInputComponent->BindAction(FName(TEXT("SprintAction")), IE_Released, this, &ALmBaseCharacter::PlayerSprintEnd);

	//Select Rotation Mode: Switch the desired (default) rotation mode to Velocity or Looking Direction. This will be the mode the character reverts back to when unaiming
	PlayerInputComponent->BindAction(FName(TEXT("ToggleRotationMode")), IE_Pressed, this, &ALmBaseCharacter::ToggleRotationMode);

	//AimAction: Hold "AimAction" to enter the aiming mode, release to revert back the desired rotation mode.
	PlayerInputComponent->BindAction(FName(TEXT("AimAction")), IE_Pressed, this, &ALmBaseCharacter::AimActionBegin);
	PlayerInputComponent->BindAction(FName(TEXT("AimAction")), IE_Released, this, &ALmBaseCharacter::AimActionEnd);

	//Camera Action: Hold "Camera Action" to toggle Third / First Person, tap to swap shoulders.
	PlayerInputComponent->BindAction(FName(TEXT("CameraAction")), IE_Pressed, this, &ALmBaseCharacter::CameraActionBegin);
	PlayerInputComponent->BindAction(FName(TEXT("CameraAction")), IE_Released, this, &ALmBaseCharacter::CameraActionEnd);

	//Ragdoll Action: Press "Ragdoll Action" to toggle the ragdoll state on or off.
	PlayerInputComponent->BindAction(FName(TEXT("RagdollAction")), IE_Pressed, this, &ALmBaseCharacter::ToggleRagdollMode);
}

void ALmBaseCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) {
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
	OnCharacterMovementModeChanged(PrevMovementMode, GetCharacterMovement()->MovementMode, PreviousCustomMode, GetCharacterMovement()->CustomMovementMode);
}

void ALmBaseCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) {
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);

	OnStanceChanged(ELmStance::Lm_Crouching);
}

void ALmBaseCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) {
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);

	OnStanceChanged(ELmStance::Lm_Standing);
}

void ALmBaseCharacter::Landed(const FHitResult& Hit) {
	Super::Landed(Hit);

	if (bBreakFall) {
		BreakFall();
	} else {
		GetCharacterMovement()->BrakingFrictionFactor = bHasMovementInput ? 0.5f : 3.0f;

		FTimerDelegate timerDel;

		//Retriggering Delay
		if (GetWorldTimerManager().IsTimerActive(timerHandle_Landing))
			GetWorldTimerManager().ClearTimer(timerHandle_Landing);

		timerDel.BindLambda([this] {
			GetCharacterMovement()->BrakingFrictionFactor = 0.0f;
			});

		GetWorldTimerManager().SetTimer(timerHandle_Landing, timerDel, 0.5f, false);
	}
}

void ALmBaseCharacter::OnJumped_Implementation() {
	Super::OnJumped_Implementation();

	//On Jumped: Set the new In Air Rotation to the velocity rotation if speed is greater than 100.
	InAirRotation = Speed > 100.0f ? LastVelocityRotation : GetActorRotation();
	if (IsValid(animInstance) && animInstance->GetClass()->ImplementsInterface(ULmCharacterAnimationInterface::StaticClass())) {
		ILmCharacterAnimationInterface::Execute_Jumped(animInstance);
	}
}

FLmControlVectors ALmBaseCharacter::GetControlVectors() {
	FLmControlVectors ControlVectors;

	const FRotator yaw = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);

	ControlVectors.Forward = UKismetMathLibrary::GetForwardVector(yaw);
	ControlVectors.Right = UKismetMathLibrary::GetRightVector(yaw);

	return ControlVectors;
}

FVector ALmBaseCharacter::GetCapsuleBaseLocation(float ZOffset) {
	const auto cc = GetCapsuleComponent();
	return cc->GetComponentLocation() - (cc->GetUpVector() * (ZOffset + cc->GetScaledCapsuleHalfHeight()));
}

FVector ALmBaseCharacter::GetCapsuleLocationFromBase(FVector baseLocation, float zOffset) {
	return baseLocation + FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + zOffset);
}

float ALmBaseCharacter::GetAnimCurveValue(const FName curveName) {
	return IsValid(animInstance) ? animInstance->GetCurveValue(curveName == NAME_None ? TEXT("") : curveName) : 0.0f;
}

void ALmBaseCharacter::ReceiveMoveForwardBackwards(const float value) {
	forwardInputValue = value;
	PlayerMovementInput(true);
}

void ALmBaseCharacter::ReceiveMoveRightLeft(const float value) {
	rightInputValue = value;
	PlayerMovementInput(false);
}

void ALmBaseCharacter::PlayerMovementInput(const bool bIsForwardAxis) {
	if (MovementState != ELmMovementState::Lm_Grounded && MovementState != ELmMovementState::Lm_InAir)
		return;

	const auto gamepadValues = FixDiagonalGamePadValues(rightInputValue, forwardInputValue);
	const auto controlVectors = GetControlVectors();

	if (bIsForwardAxis) {
		AddMovementInput(controlVectors.Forward, gamepadValues.Y);
	} else {
		AddMovementInput(controlVectors.Right, gamepadValues.X);
	}
}

void ALmBaseCharacter::PlayerCameraYawInput(const float value) {
	AddControllerYawInput(LookLeftRightRate * value);
}

void ALmBaseCharacter::PlayerCameraPitchInput(const float value) {
	AddControllerPitchInput(LookUpDownRate * value);
}

void ALmBaseCharacter::PlayerJumpPressedInput() {
	if (MovementAction != ELmMovementAction::Lm_None)
		return;

	if (MovementState == ELmMovementState::Lm_Ragdoll) {

		RagdollEnd();

	} else if (MovementState != ELmMovementState::Lm_Mantling) {

		if (MovementState == ELmMovementState::Lm_Grounded) {

			if (bHasMovementInput) {
				const bool MantleCheckResult = MantleCheck(GroundedTraceSettings, EDrawDebugTrace::ForDuration);
				if (!MantleCheckResult) {
					if (Stance == ELmStance::Lm_Standing)
						Jump();
					else
						UnCrouch();
				}
			} else {
				if (Stance == ELmStance::Lm_Standing)
					Jump();
				else
					UnCrouch();
			}

		} else if (MovementState == ELmMovementState::Lm_InAir) {
			MantleCheck(FallingTraceSettings, EDrawDebugTrace::ForDuration);
		}
	}
}

void ALmBaseCharacter::PlayerStanceActionInput(FKey key) {
	if (MovementAction != ELmMovementAction::Lm_None)
		return;

	StanceActionInputCounter++;

	GetWorldTimerManager().ClearTimer(StanceAction_th);

	FTimerDelegate timerDel;
	timerDel.BindLambda([this] {
		GetWorldTimerManager().ClearTimer(StanceAction_th);

		if (StanceActionInputCounter == 1) {
			if (MovementState == ELmMovementState::Lm_Grounded) {
				if (Stance == ELmStance::Lm_Standing) {
					DesiredStance = ELmStance::Lm_Crouching;
					Crouch();
				} else {
					DesiredStance = ELmStance::Lm_Standing;
					UnCrouch();
				}
			} else if (MovementState == ELmMovementState::Lm_InAir) {
				bBreakFall = true;

				FTimerDelegate resetBreakFallDel;
				resetBreakFallDel.BindLambda([this] {
					if (GetWorldTimerManager().IsTimerActive(ResetBreakFall_th))
						GetWorldTimerManager().ClearTimer(ResetBreakFall_th);

					bBreakFall = false;
					});

				if (GetWorldTimerManager().IsTimerActive(ResetBreakFall_th))
					GetWorldTimerManager().ClearTimer(ResetBreakFall_th);

				GetWorldTimerManager().SetTimer(ResetBreakFall_th, resetBreakFallDel, 0.4f, true);
			}
		} else {
			//multi-pressed
			Roll();
			DesiredStance = Stance == ELmStance::Lm_Standing ? ELmStance::Lm_Crouching : ELmStance::Lm_Standing;
		}

		this->StanceActionInputCounter = 0;
		});

	GetWorldTimerManager().SetTimer(StanceAction_th, timerDel, 0.3f, false);
}

void ALmBaseCharacter::PlayerWalkBegin() {
	DesiredGait = ELmGait::Lm_Walking;
}

void ALmBaseCharacter::PlayerWalkEnd() {
	DesiredGait = ELmGait::Lm_Running;
}

void ALmBaseCharacter::PlayerSprintBegin() {
	//Implementing the dual mode functionality on "Sprint Action" input event, 'double tap' or 'hold to sprint'

	if (SprintProcessingMode == ELmInputProcessingMode::Lm_PressAndHold) {
		DesiredGait = ELmGait::Lm_Sprinting;
	} else {
		//ULmLogger::LogInfo(TEXT("Sprint Pressed"));
		bSprintHeld = true;
		SprintTapCounter++;

		DesiredGait = ELmGait::Lm_Running;

		FTimerDelegate del;
		del.BindLambda([this]() {
			if (SprintTapCounter > 1) {
				GetWorldTimerManager().ClearTimer(Sprint_Handle);

				//ULmLogger::LogInfo(TEXT("Sprinting"));
				DesiredGait = ELmGait::Lm_Sprinting;
			} else if (SprintTapCounter == 1) {
				GetWorldTimerManager().ClearTimer(Sprint_Handle);

				//ULmLogger::LogInfo(TEXT("Walking"));
				DesiredGait = ELmGait::Lm_Walking;
			}
			});

		GetWorldTimerManager().SetTimer(Sprint_Handle, del, DoubleTapTime, false);
	}
}

void ALmBaseCharacter::PlayerSprintEnd() {
	if (SprintProcessingMode == ELmInputProcessingMode::Lm_PressAndHold) {
		DesiredGait = ELmGait::Lm_Running;
	} else {
		//ULmLogger::LogError(TEXT("Sprint Released"));

		bSprintHeld = true;

		FTimerDelegate del;
		del.BindLambda([this]() {
			GetWorldTimerManager().ClearTimer(Sprint_Handle);
			//ULmLogger::LogError(TEXT("Running"));

			SprintTapCounter = 0;
			DesiredGait = ELmGait::Lm_Running;
			});

		GetWorldTimerManager().SetTimer(Sprint_Handle, del, DoubleTapTime, false);
	}
}

void ALmBaseCharacter::ToggleRotationMode() {
	if (DesiredRotationMode == ELmRotationMode::Lm_LookingDirection) {
		ChangeRotationMode(ELmRotationMode::Lm_VelocityDirection);
	} else if (DesiredRotationMode == ELmRotationMode::Lm_VelocityDirection) {
		ChangeRotationMode(ELmRotationMode::Lm_LookingDirection);
	}
}

void ALmBaseCharacter::ChangeRotationMode(ELmRotationMode newMode) {
	DesiredRotationMode = newMode;
	if (this->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass())) {
		ILmCharacterInterface::Execute_SetRotationMode(this, newMode);
	}
}

void ALmBaseCharacter::AimActionBegin() {
	if (this->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass())) {
		ILmCharacterInterface::Execute_SetRotationMode(this, ELmRotationMode::Lm_Aiming);
	}
}

void ALmBaseCharacter::AimActionEnd() {
	//AimAction: Hold "AimAction" to enter the aiming mode, release to revert back the desired rotation mode.
	if (this->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass())) {
		ILmCharacterInterface::Execute_SetRotationMode(this, ViewMode == ELmViewMode::Lm_TPS ? DesiredRotationMode : ELmRotationMode::Lm_LookingDirection);
	}
}

void ALmBaseCharacter::CameraActionBegin() {
	//Camera Action: Hold "Camera Action" to toggle Third / First Person, tap to swap shoulders.
	GetWorldTimerManager().ClearTimer(cameraAction_th);

	CameraActionPressType = ELmButtonPressType::Lm_Tapping;

	FTimerDelegate holdAction;
	holdAction.BindLambda([this] {
		if (CameraActionPressType == ELmButtonPressType::Lm_Tapping) {
			CameraActionPressType = ELmButtonPressType::Lm_Holding;
			if (this->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass())) {
				ILmCharacterInterface::Execute_SetViewMode(this, ViewMode == ELmViewMode::Lm_TPS ? ELmViewMode::Lm_FPS : ELmViewMode::Lm_TPS);
			}
		}
		});

	GetWorldTimerManager().SetTimer(cameraAction_th, holdAction, 0.2f, false);
}

void ALmBaseCharacter::CameraActionEnd() {
	if (CameraActionPressType == ELmButtonPressType::Lm_Tapping) {
		bRightShoulder = !bRightShoulder;
	} else {
		GetWorldTimerManager().ClearTimer(cameraAction_th);
	}

	CameraActionPressType = ELmButtonPressType::Lm_Released;
}

void ALmBaseCharacter::RagdollActionBegin() {
	//Ragdoll Action: Press "Ragdoll Action" to toggle the ragdoll state on or off.
	if (MovementState == ELmMovementState::Lm_Ragdoll) {
		RagdollEnd();
	} else {
		RagdollStart();
	}
}

FVector ALmBaseCharacter::GetPlayerMovementInput() {
	const auto Vectors = GetControlVectors();
	const auto tmp = forwardInputValue * Vectors.Forward + rightInputValue * Vectors.Right;
	return tmp.GetSafeNormal();
}

FVector2D ALmBaseCharacter::FixDiagonalGamePadValues(const float inX, const float inY) {
	FVector2D Retvalue;

	Retvalue.Y = UKismetMathLibrary::Clamp(inY * UKismetMathLibrary::MapRangeClamped(FMath::Abs(inX), 0.0f, 0.6f, 1.0f, 1.2f), -1.0f, 1.0f);
	Retvalue.X = UKismetMathLibrary::Clamp(inX * UKismetMathLibrary::MapRangeClamped(FMath::Abs(inY), 0.0f, 0.6f, 1.0f, 1.2f), -1.0f, 1.0f);

	return Retvalue;
}

void ALmBaseCharacter::SetEssentialValues() {
	//These values represent how the capsule is moving as well as how it wants to move, and therefore are essential for any data driven animation system. They are also used throughout the system for various functions, so I found it is easiest to manage them all in one place.

	//Set the amount of Acceleration.
	Acceleration = CalculateAcceleration();

	//Determine if the character is moving by getting it's speed. The Speed equals the length of the horizontal (x y) velocity, so it does not take vertical movement into account. If the character is moving, update the last velocity rotation. This value is saved because it might be useful to know the last orientation of movement even after the character has stopped.
	FVector nonZvelocity = FVector(GetVelocity().X, GetVelocity().Y, 0.0f);
	Speed = nonZvelocity.Size();
	bIsMoving = Speed > 1.0f;
	if (bIsMoving)
		LastVelocityRotation = GetVelocity().ToOrientationRotator();

	//Determine if the character has movement input by getting its movement input amount. The Movement Input Amount is equal to the current acceleration divided by the max acceleration so that it has a range of 0-1, 1 being the maximum possible amount of input, and 0 being none. If the character has movement input, update the Last Movement Input Rotation.
	const auto* characterMovement = GetCharacterMovement();
	MovementInputAmount = characterMovement->GetCurrentAcceleration().Size() / characterMovement->GetMaxAcceleration();

	bHasMovementInput = MovementInputAmount > 0.0f;
	if (bHasMovementInput)
		LastMovementInputRotation = characterMovement->GetCurrentAcceleration().ToOrientationRotator();

	//Set the Aim Yaw rate by comparing the current and previous Aim Yaw value, divided by Delta Seconds. This represents the speed the camera is rotating left to right.
	AimYawRate = FMath::Abs((GetControlRotation().Yaw - PreviousAimYaw) / GetWorld()->GetDeltaSeconds());
}

void ALmBaseCharacter::CacheValues() {
	//Cache certain values to be used in calculations on the next frame
	PreviousVelocity = GetVelocity();
	PreviousAimYaw = GetControlRotation().Yaw;
}

FVector ALmBaseCharacter::CalculateAcceleration() {
	//Calculate the Acceleration by comparing the current and previous velocity. The Current Acceleration returned by the movement component equals the input acceleration, and does not represent the actual physical acceleration of the character.
	return (GetVelocity() - PreviousVelocity) / GetWorld()->GetDeltaSeconds();
}

void ALmBaseCharacter::OnCharacterMovementModeChanged(EMovementMode PrevMovementMode, EMovementMode NewMovementMode, uint8 PrevCustomMode, uint8 NewCustomMode) {
	Super::OnMovementModeChanged(PrevMovementMode, PrevCustomMode);

	if (this->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass()))
		if (NewMovementMode == MOVE_Walking || NewMovementMode == MOVE_NavWalking) {
			ILmCharacterInterface::Execute_SetMovementState(this, ELmMovementState::Lm_Grounded);
		} else if (NewMovementMode == MOVE_Falling) {
			ILmCharacterInterface::Execute_SetMovementState(this, ELmMovementState::Lm_InAir);
		}
}

void ALmBaseCharacter::OnMovementStateChanged(const ELmMovementState NewMovementState) {
	if (NewMovementState == MovementState) {
		return;
	}

	PrevMovementState = MovementState;
	MovementState = NewMovementState;

	if (MovementState == ELmMovementState::Lm_InAir) {
		//If the character enters the air, set the In Air Rotation and uncrouch if crouched. If the character is currently rolling, enable the Ragdoll.
		if (MovementAction == ELmMovementAction::Lm_None) {
			InAirRotation = GetActorRotation();
			if (Stance == ELmStance::Lm_Crouching)
				UnCrouch();

		} else if (MovementAction == ELmMovementAction::Lm_Rolling) {
			RagdollStart();
		}
	} else if (MovementState == ELmMovementState::Lm_Ragdoll) {
		//Stop the Mantle Timeline if transitioning to the Ragdoll state while mantling.
		if (PrevMovementState == ELmMovementState::Lm_Mantling)
			mantleTimeline->Stop();
	}
}

void ALmBaseCharacter::OnMovementActionChanged(const ELmMovementAction NewMovementAction) {
	if (NewMovementAction == MovementAction) {
		return;
	}

	PrevMovementAction = MovementAction;
	MovementAction = NewMovementAction;
	//Make the character crouch if performing a roll.
	if (MovementAction == ELmMovementAction::Lm_Rolling) {
		Crouch();
	}

	//Upon ending a roll, reset the stance back to its desired value.
	if (PrevMovementAction == ELmMovementAction::Lm_Rolling) {
		DesiredStance == ELmStance::Lm_Standing ? UnCrouch() : Crouch();
	}
}

void ALmBaseCharacter::OnStanceChanged(const ELmStance NewStance) {
	prevStance = Stance;
	Stance = NewStance;
}

void ALmBaseCharacter::OnRotationModeChanged(const ELmRotationMode NewRotationMode) {
	prevRotationMode = RotationMode;
	RotationMode = NewRotationMode;

	if (RotationMode == ELmRotationMode::Lm_VelocityDirection && ViewMode == ELmViewMode::Lm_FPS) {
		if (this->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass())) {
			ILmCharacterInterface::Execute_SetViewMode(this, ELmViewMode::Lm_TPS);
		}
	}
}

void ALmBaseCharacter::OnGaitChanged(const ELmGait NewActualGait) {
	prevGait = Gait;
	Gait = NewActualGait;
}

void ALmBaseCharacter::OnViewModeChanged(const ELmViewMode NewViewMode) {
	prevViewMode = ViewMode;
	ViewMode = NewViewMode;

	if (ViewMode == ELmViewMode::Lm_TPS) {
		//If Third Person, set the rotation mode back to the desired mode.
		if (RotationMode != ELmRotationMode::Lm_Aiming) {
			if (this->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass())) {
				ILmCharacterInterface::Execute_SetRotationMode(this, DesiredRotationMode);
			}
		}
	} else {
		//If First Person, set the rotation mode to looking direction if currently in the velocity direction mode.
		if (RotationMode == ELmRotationMode::Lm_VelocityDirection) {
			if (this->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass())) {
				ILmCharacterInterface::Execute_SetRotationMode(this, ELmRotationMode::Lm_LookingDirection);
			}
		}
	}
}

void ALmBaseCharacter::OnOverlayStateChanged(const ELmOverlayState NewOverlayState) {
	prevOverlayState = OverlayState;
	OverlayState = NewOverlayState;
}

void ALmBaseCharacter::SetMovementModel() {
	// Search using FindRow. It returns a handle to the row.
	// Access the variables like GOLookupRow->Blueprint_Class, GOLookupRow->UseCode
	MovementData = *MovementModel.DataTable->FindRow<FLmMovementSettingsState>(MovementModel.RowName, nullptr);
}

void ALmBaseCharacter::UpdateCharacterMovement() {
	//Set the Allowed Gait
	const ELmGait allowedGait = GetAllowedGait();

	//Determine the Actual Gait. If it is different from the current Gait, Set the new Gait Event.
	const auto actualGait = GetActualGait(allowedGait);
	if (Gait != actualGait) {
		if (this->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass())) {
			ILmCharacterInterface::Execute_SetGait(this, actualGait);
		}
	}

	//Use the allowed gait to update the movement settings.
	UpdateDynamicMovementSettings(allowedGait);
}

void ALmBaseCharacter::UpdateDynamicMovementSettings(ELmGait AllowedGait) {
	CurrentMovementSettings = GetTargetMovementSettings();
	const auto cm = GetCharacterMovement();

	//Update the Character Max Walk Speed to the configured speeds based on the currently Allowed Gait.
	if (AllowedGait == ELmGait::Lm_Walking) {
		cm->MaxWalkSpeed = CurrentMovementSettings.WalkSpeed;
	} else if (AllowedGait == ELmGait::Lm_Running) {
		cm->MaxWalkSpeed = CurrentMovementSettings.RunSpeed;
	} else {
		cm->MaxWalkSpeed = CurrentMovementSettings.SprintSpeed;
	}

	cm->MaxWalkSpeedCrouched = GetCharacterMovement()->MaxWalkSpeed;

	//Update the Acceleration, Deceleration, and Ground Friction using the Movement Curve. This allows for fine control over movement behavior at each speed (May not be suitable for replication).
	const FVector value = CurrentMovementSettings.MovementCurve->GetVectorValue(GetMappedSpeed());
	cm->MaxAcceleration = value.X;
	cm->BrakingDecelerationWalking = value.Y;
	cm->GroundFriction = value.Z;
}

FLmMovementSettings ALmBaseCharacter::GetTargetMovementSettings() {
	if (RotationMode == ELmRotationMode::Lm_VelocityDirection) {
		if (Stance == ELmStance::Lm_Standing)
			return MovementData.VelocityDirection.Standing;
		return MovementData.VelocityDirection.Crouching;
	}

	if (RotationMode == ELmRotationMode::Lm_LookingDirection) {
		if (Stance == ELmStance::Lm_Standing)
			return MovementData.LookingDirection.Standing;
		return MovementData.LookingDirection.Crouching;
	}

	// since this is not those 2 cases above, this is Aiming mode for sure
	if (Stance == ELmStance::Lm_Standing)
		return MovementData.Aiming.Standing;
	return MovementData.Aiming.Crouching;
}

ELmGait ALmBaseCharacter::GetAllowedGait() {
	//Calculate the Allowed Gait. This represents the maximum Gait the character is currently allowed to be in, and can be determined by the desired gait, the rotation mode, the stance, etc. For example, if you wanted to force the character into a walking state while indoors, this could be done here.
	if (Stance == ELmStance::Lm_Standing) {
		if (RotationMode != ELmRotationMode::Lm_Aiming) {
			if (DesiredGait == ELmGait::Lm_Walking || DesiredGait == ELmGait::Lm_Running)
				return  DesiredGait;

			return CanSprint() ? ELmGait::Lm_Sprinting : ELmGait::Lm_Running;
		}
	}

	return DesiredGait == ELmGait::Lm_Walking ? ELmGait::Lm_Walking : ELmGait::Lm_Running;

}

ELmGait ALmBaseCharacter::GetActualGait(ELmGait AllowedGait) {
	if (Speed >= CurrentMovementSettings.RunSpeed + 10)
		return AllowedGait == ELmGait::Lm_Sprinting ? ELmGait::Lm_Sprinting : ELmGait::Lm_Running;

	return  Speed >= CurrentMovementSettings.WalkSpeed + 10 ? ELmGait::Lm_Running : ELmGait::Lm_Walking;
}

bool ALmBaseCharacter::CanSprint() {
	if (!bHasMovementInput || RotationMode == ELmRotationMode::Lm_Aiming)
		return false;

	if (RotationMode == ELmRotationMode::Lm_VelocityDirection)
		return  MovementInputAmount > 0.9f;

	float yaw = UKismetMathLibrary::NormalizedDeltaRotator(GetCharacterMovement()->GetCurrentAcceleration().ToOrientationRotator(), GetControlRotation()).Yaw;

	yaw = FMath::Abs(yaw);
	return MovementInputAmount > 0.9f && yaw < 50.0f;
}

float ALmBaseCharacter::GetMappedSpeed() {
	//Map the character's current speed to the configured movement speeds with a range of 0-3, with 0 = stopped, 1 = the Walk Speed, 2 = the Run Speed, and 3 = the Sprint Speed. This allows you to vary the movement speeds but still use the mapped range in calculations for consistent results.
	const float localWalkSpeed = CurrentMovementSettings.WalkSpeed;
	const float localRunSpeed = CurrentMovementSettings.RunSpeed;
	const float localSprintSpeed = CurrentMovementSettings.SprintSpeed;

	const float speed1 = UKismetMathLibrary::MapRangeClamped(Speed, 0.0f, localWalkSpeed, 0.0f, 1.0f);

	const float speed2 = UKismetMathLibrary::MapRangeClamped(Speed, localWalkSpeed, localRunSpeed, 1.0f, 2.0f);

	const float speed3 = UKismetMathLibrary::MapRangeClamped(Speed, localRunSpeed, localSprintSpeed, 2.0f, 3.0f);

	if (Speed > localRunSpeed)
		return speed3;
	if (Speed > localWalkSpeed)
		return speed2;
	return speed1;
}

UAnimMontage* ALmBaseCharacter::GetRollAnimation() {
	//This gets overridden in the AnimMan Child character to select the appropriate animation based on the overlay state.
	return nullptr;
}

void ALmBaseCharacter::UpdateGroundedRotation() {
	switch (MovementAction) {
	case ELmMovementAction::Lm_None:
		if (CanUpdateMovingRotation()) {
			switch (RotationMode) {
			case ELmRotationMode::Lm_VelocityDirection:
				//Velocity Direction Rotation
				SmoothCharacterRotation(FRotator(0.0f, LastVelocityRotation.Yaw, 0.0f), 800.0f, CalculateGroundedRotationRate());
				break;
			case ELmRotationMode::Lm_LookingDirection:
				//Looking Direction Rotation
				switch (Gait) {
				case ELmGait::Lm_Walking:
				case ELmGait::Lm_Running:
					SmoothCharacterRotation(FRotator(0.0f, GetControlRotation().Yaw + GetAnimCurveValue(FName(TEXT("YawOffset"))), 0.0f), 500.0f, CalculateGroundedRotationRate());
					break;
				case ELmGait::Lm_Sprinting:
					SmoothCharacterRotation(FRotator(0.0f, LastVelocityRotation.Yaw, 0.0f), 500.0f, CalculateGroundedRotationRate());
					break;
				default:;
				}
				break;
			case ELmRotationMode::Lm_Aiming:
				//Aiming Rotation
				SmoothCharacterRotation(FRotator(0.0f, GetControlRotation().Yaw, 0.0f), 1000.0f, 20.0f);
				break;
			default:;
			}
		} else {
			//Not Moving
			if (ViewMode == ELmViewMode::Lm_FPS || RotationMode == ELmRotationMode::Lm_Aiming)
				LimitRotation(-100.0f, 100.0f, 20.0f);

			//Apply the RotationAmount curve from Turn In Place Animations. The Rotation Amount curve defines how much rotation should be applied each frame, and is calculated for animations that are animated at 30fps.
			const float curveAmount = GetAnimCurveValue(FName(TEXT("RotationAmount")));
			if (FMath::Abs(curveAmount) > 0.001f) {
				AddActorWorldRotation(FRotator(0.0f, curveAmount * GetWorld()->GetDeltaSeconds() / 0.0334f, 0.0f));
				TargetRotation = GetActorRotation();
			}
		}
		break;
	case ELmMovementAction::Lm_Rolling:
		if (bHasMovementInput)
			SmoothCharacterRotation(FRotator(0.f, LastMovementInputRotation.Yaw, 0.f), 0.0f, 2.0f);
		break;
	case ELmMovementAction::Lm_LowMantle:
	case ELmMovementAction::Lm_HighMantle:
	case ELmMovementAction::Lm_GettingUp:
	default:;
	}
}

void ALmBaseCharacter::UpdateInAirRotation() {
	if (RotationMode == ELmRotationMode::Lm_Aiming) {
		SmoothCharacterRotation(FRotator(0.0f, GetControlRotation().Yaw, 0.0f), 0.0f, 15.0f);
		InAirRotation = GetActorRotation();
	} else {
		SmoothCharacterRotation(FRotator(0.0f, InAirRotation.Yaw, 0.0f), 0.0f, 5.0f);
	}
}

void ALmBaseCharacter::SmoothCharacterRotation(FRotator Target, float TargetInterpSpeedConst, float ActorInterpSpeedSmooth) {
	//Interpolate the Target Rotation for extra smooth rotation behavior
	TargetRotation = UKismetMathLibrary::RInterpTo_Constant(TargetRotation, Target, GetWorld()->GetDeltaSeconds(), TargetInterpSpeedConst);

	SetActorRotation(UKismetMathLibrary::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), ActorInterpSpeedSmooth));
}

void ALmBaseCharacter::LimitRotation(float AimYawMin, float AimYawMax, float InterpSpeed) {
	const float deltaYaw = UKismetMathLibrary::NormalizedDeltaRotator(GetControlRotation(), GetActorRotation()).Yaw;

	const float controlYaw = GetControlRotation().Yaw;
	if (UKismetMathLibrary::InRange_FloatFloat(deltaYaw, AimYawMin, AimYawMax))
		return;

	SmoothCharacterRotation(FRotator(0.0f, controlYaw + deltaYaw > 0 ? AimYawMin : AimYawMax, 0.0f), 0.0f, InterpSpeed);
}

FLmHitResult ALmBaseCharacter::SetActorLocationRotationUpdateTarget(FVector NewLocation, FRotator NewRotation, bool bSweep, bool bTeleport) {
	TargetRotation = NewRotation;

	//ULmLogger::LogInfo(*TargetRotation.ToString(), 0.0f);

	FLmHitResult HitResult;

	const bool result = SetActorLocationAndRotation(NewLocation, TargetRotation, bSweep, &HitResult.SweepHitResult);
	HitResult.bHit = result;

	return HitResult;
}

float ALmBaseCharacter::CalculateGroundedRotationRate() {
	//Calculate the rotation rate by using the current Rotation Rate Curve in the Movement Settings. Using the curve in conjunction with the mapped speed gives you a high level of control over the rotation rates for each speed. Increase the speed if the camera is rotating quickly for more responsive rotation.
	return CurrentMovementSettings.RotationRateCurve->GetFloatValue(GetMappedSpeed()) * UKismetMathLibrary::MapRangeClamped(AimYawRate, 0.0, 300.0f, 1.0f, 3.0f);
}

bool ALmBaseCharacter::CanUpdateMovingRotation() {
	return !HasAnyRootMotion() && (bIsMoving && bHasMovementInput || Speed > 150.0f);
}

bool ALmBaseCharacter::MantleCheck(FLmMantleTraceSettings TraceSettings, TEnumAsByte<EDrawDebugTrace::Type> DebugType) {

	//Step 1: Trace forward to find a wall / object the character cannot walk on.

	const auto playerMovementInput = GetPlayerMovementInput();

	const FVector capsuleTraceStart = GetCapsuleBaseLocation(2.0f) - (30.0f * playerMovementInput) + (FVector::UpVector * (TraceSettings.MaxLedgeHeight + TraceSettings.MinLedgeHeight) / 2.0f);

	const FVector capsuleTraceEnd = capsuleTraceStart + (playerMovementInput * TraceSettings.ReachDistance);

	const float halfHeight = 1.0f + (TraceSettings.MaxLedgeHeight - TraceSettings.MinLedgeHeight) / 2.0f;

	FHitResult capsuleTraceHitResult;

	UKismetSystemLibrary::CapsuleTraceSingle(this, capsuleTraceStart, capsuleTraceEnd, TraceSettings.ForwardTraceRadius, halfHeight, ETT_Climbable, false, IgnoredActors, GetTraceDebugType(DebugType), capsuleTraceHitResult, true, FLinearColor::Black, FLinearColor::White, 1.0f);

	if (!(capsuleTraceHitResult.bBlockingHit && !capsuleTraceHitResult.bStartPenetrating && !GetCharacterMovement()->IsWalkable(capsuleTraceHitResult)))
		return false;

	const auto impactPoint = capsuleTraceHitResult.ImpactPoint;
	const auto impactNormal = capsuleTraceHitResult.ImpactNormal;

	//Step 2: Trace downward from the first trace's Impact Point and determine if the hit location is walkable.
	const auto sphereTraceEnd = FVector(impactPoint.X, impactPoint.Y, GetCapsuleBaseLocation(2.0f).Z) - (15.0f * impactNormal);
	const FVector sphereTraceStart = sphereTraceEnd + FVector(0.0f, 0.0f, TraceSettings.MaxLedgeHeight + TraceSettings.DownwardTraceRadius + 1.0f);

	FHitResult sphereTraceHitResult;
	UKismetSystemLibrary::SphereTraceSingle(this, sphereTraceStart, sphereTraceEnd, TraceSettings.DownwardTraceRadius, ETT_Climbable, false, IgnoredActors, GetTraceDebugType(DebugType), sphereTraceHitResult, true, FLinearColor(0.896269f, 0.388383f, 0.0f), FLinearColor(1.0f, 0.0f, 0.049349f), 1.0f);

	if (!(sphereTraceHitResult.bBlockingHit && GetCharacterMovement()->IsWalkable(sphereTraceHitResult)))
		return false;

	const auto DownTraceLocation = FVector(sphereTraceHitResult.Location.X, sphereTraceHitResult.Location.Y, sphereTraceHitResult.ImpactPoint.Z);
	UPrimitiveComponent* HitComponent = sphereTraceHitResult.Component.Get();

	//Step 3: Check if the capsule has room to stand at the downward trace's location. If so, set that location as the Target Transform and calculate the mantle height.
	const auto tmpLocation = GetCapsuleLocationFromBase(DownTraceLocation, 2.0f);

	if (!CapsuleHasRoomCheck(GetCapsuleComponent(), tmpLocation, 0.0f, 0.0f, GetTraceDebugType(DebugType)))
		return false;

	if (OverlayState == ELmOverlayState::Lm_HandsTied) {
		ULmLogger::LogInfo(TEXT("Can not mantle while hands are tied!"), 0.0f);
		return false;
	}

	const FTransform TargetTransform = FTransform((impactNormal * FVector(-1.0f, -1.0f, 0.0f)).ToOrientationRotator(), tmpLocation);
	const float mantleHeight = (TargetTransform.GetLocation() - GetActorLocation()).Z;

	//Step 4: Determine the Mantle Type by checking the movement mode and Mantle Height.
	ELmMantleType mantleType;
	if (MovementState == ELmMovementState::Lm_InAir) {
		mantleType = ELmMantleType::Lm_FallingCatch;
	} else {
		mantleType = mantleHeight > 125.0f ? ELmMantleType::Lm_HighMantle : ELmMantleType::Lm_LowMantle;
	}

	//Step 5: If everything checks out, capsuleTraceStart the Mantle
	MantleStart(mantleHeight, FLmComponentAndTransform(TargetTransform, HitComponent), mantleType);

	return true;
}

void ALmBaseCharacter::MantleStart(float MantleHeight, FLmComponentAndTransform MantleLedgeWS, ELmMantleType MantleType) {
	//Step 2: Convert the world space target to the mantle component's local space for use in moving objects.
	MantleLedgeLS = ULmHelpers::WorldSpaceToLocalSpace(MantleLedgeWS);

	//Step 1: Get the Mantle Asset and use it to set the new Mantle Params.
	const auto mantleAsset = GetMantleAsset(MantleType);
	const float playRate = UKismetMathLibrary::MapRangeClamped(MantleHeight, mantleAsset.LowHeight, mantleAsset.HighHeight, mantleAsset.LowPlayRate, mantleAsset.HighPlayRate);
	const float startingPosition = UKismetMathLibrary::MapRangeClamped(MantleHeight, mantleAsset.LowHeight, mantleAsset.HighHeight, mantleAsset.LowStartPosition, mantleAsset.HighStartPosition);
	MantleParams = FLmMantleParams(mantleAsset.AnimMontage, mantleAsset.PositionCorrectionCurve, startingPosition, mantleAsset.StartingOffset, playRate);

	//Step 3: Set the Mantle Target and calculate the Starting Offset(offset amount between the actor and target transform).
	MantleTarget = MantleLedgeWS.Transform;

	MantleActualStartOffset = ULmHelpers::SubtractTransform(GetActorTransform(), MantleTarget);

	//Step 4: Calculate the Animated Start Offset from the Target Location. This would be the location the actual animation starts at relative to the Target Transform.
	const FVector t1 = MantleTarget.GetRotation().Vector() * MantleParams.StartingOffset.Y;
	FVector LocationA = MantleTarget.GetLocation() - FVector(t1.X, t1.Y, MantleParams.StartingOffset.Z);
	FTransform TransformA = FTransform(MantleTarget.GetRotation(), LocationA);
	MantleAnimatedStartOffset = ULmHelpers::SubtractTransform(TransformA, MantleTarget);

	//Step 5: Clear the Character Movement Mode and set the Movement State to Mantling
	GetCharacterMovement()->SetMovementMode(MOVE_None, 0);

	if (this->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass()))
		ILmCharacterInterface::Execute_SetMovementState(this, ELmMovementState::Lm_Mantling);

	//Step 6: Configure the Mantle Timeline so that it is the same length as the Lerp/Correction curve minus the starting position, and plays at the same speed as the animation. Then capsuleTraceStart the time-line.
	float timelineMin, timelineMax;
	MantleParams.PositionCorrectionCurve->GetTimeRange(timelineMin, timelineMax);

	mantleTimeline->SetPlayRate(MantleParams.PlayRate);
	mantleTimeline->SetTimelineLength(timelineMax - MantleParams.StartingPosition);
	mantleTimeline->SetNewTime(0.0);
	mantleTimeline->PlayFromStart();

	//Step 7: Play the Anim Montage if valid.
	if (MantleParams.AnimMontage && animInstance) {
		animInstance->Montage_Play(MantleParams.AnimMontage, MantleParams.PlayRate, EMontagePlayReturnType::MontageLength, MantleParams.StartingPosition, false);
	}

}

void ALmBaseCharacter::MantleUpdate(const float BlendIn) {
	/*Step 1: Continually update the mantle target from the stored local transform to follow along with moving objects.*/
	auto mantle_target = ULmHelpers::LocalSpaceToWorldSpace(MantleLedgeLS).Transform;

	//ULmLogger::LogWarning(FString::Printf(TEXT("mantle_target: %s"), *mantle_target.ToString()), 0.0f, false);

	/*Step 2: Update the Position and Correction Alphas using the Position/Correction curve set for each Mantle.*/
	FVector alphas = MantleParams.PositionCorrectionCurve->GetVectorValue(MantleParams.StartingPosition + mantleTimeline->GetPlaybackPosition());
	const float position_alpha = alphas.X;
	const float xy_correction_alpha = alphas.Y;
	const float z_correction_alpha = alphas.Z;

	//ULmLogger::LogWarning(FString::Printf(TEXT("alphas: %s"), *alphas.ToString()), 0.0f, false);

	/*Step 3: Lerp multiple transforms together for independent control over the horizontal and vertical blend to the animated start position, as well as the target position.*/
	//	/*Blend into the animated horizontal and rotation offset using the Y value of the Position/Correction Curve.*/
	auto horizontal_transform = FTransform();
	horizontal_transform.SetLocation(FVector(MantleAnimatedStartOffset.GetLocation().X, MantleAnimatedStartOffset.GetLocation().Y, MantleActualStartOffset.GetLocation().Z));
	horizontal_transform.SetRotation(MantleAnimatedStartOffset.GetRotation());
	horizontal_transform.SetScale3D(FVector::OneVector);

	FTransform horizontal_lerp = UKismetMathLibrary::TLerp(MantleActualStartOffset, horizontal_transform, xy_correction_alpha);
	//ULmLogger::LogWarning(FString::Printf(TEXT("hLerp: %s"), *horizontal_lerp.ToString()), 0.0f, false);


	//	/*Blend into the animated vertical offset using the Z value of the Position/Correction Curve.*/
	auto vertical_transform = FTransform();
	vertical_transform.SetLocation(FVector(MantleActualStartOffset.GetLocation().X, MantleActualStartOffset.GetLocation().Y, MantleAnimatedStartOffset.GetLocation().Z));
	vertical_transform.SetRotation(MantleActualStartOffset.GetRotation());
	vertical_transform.SetScale3D(FVector::OneVector);

	FTransform vertical_lerp = UKismetMathLibrary::TLerp(MantleActualStartOffset, vertical_transform, z_correction_alpha);
	//ULmLogger::LogWarning(FString::Printf(TEXT("vLerp: %s"), *vertical_lerp.ToString()), 0.0f, false);

	//creating the mix transform
	FTransform horizontal_vertical_mix = FTransform();
	horizontal_vertical_mix.SetLocation(FVector(horizontal_lerp.GetLocation().X, horizontal_lerp.GetLocation().Y, vertical_lerp.GetLocation().Z));
	horizontal_vertical_mix.SetRotation(horizontal_lerp.GetRotation());
	horizontal_vertical_mix.SetScale3D(FVector::OneVector);

	//	/*Blend from the currently blending transforms into the final mantle target using the X value of the Position/Correction Curve.*/
	FTransform semi_final_lerp = UKismetMathLibrary::TLerp(ULmHelpers::AddTransform(mantle_target, horizontal_vertical_mix), mantle_target, position_alpha);
	//ULmLogger::LogWarning(FString::Printf(TEXT("semi-final lerp: %s"), *semi_final_lerp.ToString()), 0.0f, false);

	//	/*Initial Blend In (controlled in the timeline curve) to allow the actor to blend into the Position/Correction curve at the midoint. This prevents pops when mantling an object lower than the animated mantle.*/
	FTransform lerped_target = UKismetMathLibrary::TLerp(ULmHelpers::AddTransform(mantle_target, MantleActualStartOffset), semi_final_lerp, BlendIn);

	/*Step 4: Set the actors location and rotation to the Lerped Target.*/
	SetActorLocationRotationUpdateTarget(lerped_target.GetLocation(), lerped_target.Rotator(), false, false);
}

void ALmBaseCharacter::MantleEnd() {
	GetCharacterMovement()->SetMovementMode(MOVE_Walking, 0);
}

bool ALmBaseCharacter::CapsuleHasRoomCheck(UCapsuleComponent* Capsule, const FVector TargetLocation, const float HeightOffset, const float RadiusOffset, const TEnumAsByte<EDrawDebugTrace::Type> DebugType) {

	const auto zUp = FVector(0.0f, 0.0f, Capsule->GetScaledCapsuleHalfHeight_WithoutHemisphere() - RadiusOffset + HeightOffset);

	FHitResult HitResult;
	UKismetSystemLibrary::SphereTraceSingleByProfile(this, TargetLocation + zUp, TargetLocation - zUp, Capsule->GetUnscaledCapsuleRadius() + RadiusOffset, ProfileName, false, IgnoredActors, GetTraceDebugType(DebugType), HitResult, true, FLinearColor(0.130706f, 0.896269f, 0.144582f), FLinearColor(0.932733f, 0.29136f, 1.0f), 1.0f);

	return !(HitResult.bBlockingHit || HitResult.bStartPenetrating);
}

FLmMantleAsset ALmBaseCharacter::GetMantleAsset(ELmMantleType MantleType) {
	//Get the Default Mantle Asset values.These will be overridden in the AnimMan Child Character
	if (MantleType == ELmMantleType::Lm_HighMantle) {
		return FLmMantleAsset(nullptr, HighMantle, FVector(0.0f, 65.0f, 200.0f), 50.0f, 1.0f, 0.5f, 100.0f, 1.0f, 0.0f);
	}

	if (MantleType == ELmMantleType::Lm_LowMantle) {
		return FLmMantleAsset(nullptr, LowMantle, FVector(0.0f, 65.0f, 200.0f), 125.0f, 1.2f, 0.6f, 200.0f, 1.2f, 0.0f);
	}

	return FLmMantleAsset(nullptr, LowMantle, FVector(0.0f, 65.0f, 200.0f), 125.0f, 1.2f, 0.6f, 200.0f, 1.2f, 0.0f);
}

void ALmBaseCharacter::RagdollStart() {

	//Step 1: Clear the Character Movement Mode and set the Movement State to Ragdoll
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	if (this->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass()))
		ILmCharacterInterface::Execute_SetMovementState(this, ELmMovementState::Lm_Ragdoll);

	//Step 2: Disable capsule collision and enable mesh physics simulation starting from the pelvis.
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionObjectType(ECC_PhysicsBody);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetAllBodiesBelowSimulatePhysics(FName(TEXT("pelvis")), true, true);

	//Step 3: Stop any active montages
	animInstance->Montage_Stop(0.2f);
}

void ALmBaseCharacter::RagdollEnd() {
	//Step 1: Save a snapshot of the current Ragdoll Pose for use in AnimGraph to blend out of the Ragdoll
	if (IsValid(animInstance))
		animInstance->SavePoseSnapshot(FName(TEXT("RagdollPose")));

	//Step 2: If the ragdoll is on the ground, set the movement mode to walking and play a Get Up animation. If not, set the movement mode to falling and update teh character movement velocity to match the last ragdoll velocity.
	if (bRagdollOnGround) {
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		animInstance->Montage_Play(GetGetupAnimation(bRagdollFaceUp));
	} else {
		GetCharacterMovement()->SetMovementMode(MOVE_Falling);
		GetCharacterMovement()->Velocity = LastRagdollVelocity;
	}

	//Step 3: Re-Enable capsule collision, and disable physics simulation on the mesh
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetMesh()->SetAllBodiesSimulatePhysics(false);
}

void ALmBaseCharacter::RagdollUpdate() {
	//Set the Last Ragdoll Velocity
	LastRagdollVelocity = GetMesh()->GetPhysicsLinearVelocity(FName(TEXT("root")));

	//Use the Ragdoll Velocity to scale the ragdoll's joint strength for physical animation
	GetMesh()->SetAllMotorsAngularDriveParams(UKismetMathLibrary::MapRangeClamped(LastRagdollVelocity.Size(), 0.0f, 1000.0f, 0.0f, 25000.0f), 0.0f, 0.0f);

	//Disable Gravity if falling faster than -4000 to prevent continual acceleration. This also prevents the ragdoll from going through the floor.
	GetMesh()->SetEnableGravity(LastRagdollVelocity.Z > -4000.0f);

	//Update the Actor location to follow the ragdoll.
	SetActorLocationDuringRagdoll();
}

void ALmBaseCharacter::ToggleRagdollMode() {
	if (MovementState == ELmMovementState::Lm_Ragdoll) {
		RagdollEnd();
	} else {
		RagdollStart();
	}
}

void ALmBaseCharacter::SetActorLocationDuringRagdoll() {
	//Set the pelvis as the target location.
	FVector targetRagdollLocation = GetMesh()->GetSocketLocation(FName(TEXT("pelvis")));

	//Determine wether the ragdoll is facing up or down and set the target rotation accordingly.
	FRotator socketRotation = GetMesh()->GetSocketRotation(FName(TEXT("pelvis")));
	bRagdollFaceUp = socketRotation.Roll < 0;
	FRotator targetRagdollRotation = FRotator(0, bRagdollFaceUp ? socketRotation.Yaw - 180 : socketRotation.Yaw, 0);

	//Trace downward from the target location to offset the target location, preventing the lower half of the capsule from going through the floor when the ragdoll is laying on the ground
	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);

	bRagdollOnGround = GetWorld()->LineTraceSingleByChannel(HitResult, targetRagdollLocation, FVector(targetRagdollLocation.X, targetRagdollLocation.Y, targetRagdollLocation.Z - GetCapsuleComponent()->GetScaledCapsuleHalfHeight()), ECC_Visibility, CollisionQueryParams);

	if (bRagdollOnGround) {
		float Z = targetRagdollLocation.Z + GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - FMath::Abs(HitResult.ImpactPoint.Z - HitResult.TraceStart.Z) + 2;
		SetActorLocationRotationUpdateTarget(FVector(targetRagdollLocation.X, targetRagdollLocation.Y, Z), targetRagdollRotation, false, false);
	} else {
		SetActorLocationRotationUpdateTarget(targetRagdollLocation, targetRagdollRotation, false, false);
	}
}

UAnimMontage* ALmBaseCharacter::GetGetupAnimation(const bool bIsRagdollFacedUp) {
	//This gets overriden in the AnimMan Child character to select the appropriate animation based on the overlay state.

	return nullptr;
}

void ALmBaseCharacter::DrawDebugShapes() {
	const auto pc = UGameplayStatics::GetPlayerController(this, 0);
	if (!pc || !pc->GetClass()->ImplementsInterface(ULmControllerInterface::StaticClass()) || !ILmControllerInterface::Execute_GetDebugInfo(pc).bShowDebugShapes)
		return;

	const auto characterMovement = GetCharacterMovement();

	//Velocity Arrow
	const FVector velocityArrowStart = GetActorLocation() - FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	const bool bIsVelocityZero = GetVelocity() == FVector::ZeroVector;
	const FVector velocityArrowEnd = velocityArrowStart + (bIsVelocityZero ? LastVelocityRotation.Vector() : GetVelocity()).GetUnsafeNormal() * UKismetMathLibrary::MapRangeClamped(GetVelocity().Size(), 0.0f, characterMovement->MaxWalkSpeed, 50.0f, 75.0f);

	UKismetSystemLibrary::DrawDebugArrow(this, velocityArrowStart, velocityArrowEnd, 60.0f,
		bIsVelocityZero ? FLinearColor(0.25f, 0.0f, 0.25f, 1.0f) : FLinearColor(1.0f, 0.0f, 1.0f, 1.0f), 0.0f, 5.0f);

	//Movement Input Arrow
	const FVector movementInputArrowStart = GetActorLocation() - FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - 3.5f);
	const bool bIsAccelerationZero = characterMovement->GetCurrentAcceleration() == FVector::ZeroVector;

	const FVector movementInputArrowEnd = movementInputArrowStart + UKismetMathLibrary::MapRangeClamped(characterMovement->GetCurrentAcceleration().Size() / characterMovement->GetMaxAcceleration(), 0.0f, 1.0f, 50.0f, 75.0f) * (bIsAccelerationZero ? LastMovementInputRotation.Vector() : characterMovement->GetCurrentAcceleration()).GetUnsafeNormal();

	UKismetSystemLibrary::DrawDebugArrow(this, movementInputArrowStart, movementInputArrowEnd, 50.0f,
		bIsAccelerationZero ? FLinearColor(0.25f, 0.125f, 0.0f, 1.0f) : FLinearColor(1.0f, 0.5f, 0.0f, 1.0f), 0.0f, 3.0f);

	//Target Rotation Arrow
	const FVector targetRotationArrowStart = GetActorLocation() - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - 7.0f);
	const FVector targetRotationArrowEnd = targetRotationArrowStart + TargetRotation.Vector().GetUnsafeNormal() * 50.0f;

	UKismetSystemLibrary::DrawDebugArrow(this, targetRotationArrowStart, targetRotationArrowEnd, 50.0f, FLinearColor(0.0f, 0.33f, 1.0f, 1.0f), 0.0f, 3.0f);

	//Aiming Rotation Cone
	UKismetSystemLibrary::DrawDebugConeInDegrees(this, GetMesh()->GetSocketLocation(TEXT("FP_Camera")), GetControlRotation().Vector().GetUnsafeNormal(), 200.0f, 30.0f, 30.0f, 32, FLinearColor(0.0f, 0.5f, 1.0f), 0.0f, 0.5f);

	//Capsule 
	UKismetSystemLibrary::DrawDebugCapsule(this, GetActorLocation(), GetCapsuleComponent()->GetScaledCapsuleHalfHeight(), GetCapsuleComponent()->GetScaledCapsuleRadius(), GetActorRotation(), FLinearColor::Black, 0.0f, 0.3f);
}

TEnumAsByte<EDrawDebugTrace::Type> ALmBaseCharacter::GetTraceDebugType(TEnumAsByte<EDrawDebugTrace::Type> showTraceType) {
	const auto pc = UGameplayStatics::GetPlayerController(this, 0);

	//Check if the player implements the ILmControllerInterface and Check if bShow debug values is set true;
	return  pc->GetClass()->ImplementsInterface(ULmControllerInterface::StaticClass()) && ILmControllerInterface::Execute_GetDebugInfo(pc).bShowDebugShapes ? showTraceType : EDrawDebugTrace::None;
}

void ALmBaseCharacter::BreakFall() {
	if (IsValid(animInstance)) {
		animInstance->Montage_Play(GetRollAnimation(), 1.35f);
	}
}

void ALmBaseCharacter::Roll() {
	if (IsValid(animInstance)) {
		animInstance->Montage_Play(GetRollAnimation(), 1.15f);
	}
}

void ALmBaseCharacter::SetMovementState_Implementation(ELmMovementState NewMovementState) {
	if (NewMovementState != MovementState) {
		OnMovementStateChanged(NewMovementState);
	}
}

void ALmBaseCharacter::SetMovementAction_Implementation(ELmMovementAction NewMovementAction) {
	if (NewMovementAction != MovementAction) {
		OnMovementActionChanged(NewMovementAction);
	}
}

void ALmBaseCharacter::SetRotationMode_Implementation(ELmRotationMode NewRotationMode) {
	if (NewRotationMode != RotationMode) {
		OnRotationModeChanged(NewRotationMode);
	}
}

void ALmBaseCharacter::SetGait_Implementation(ELmGait NewGait) {
	if (NewGait != Gait) {
		OnGaitChanged(NewGait);
	}
}

void ALmBaseCharacter::SetViewMode_Implementation(ELmViewMode NewViewMode) {
	if (NewViewMode != ViewMode) {
		OnViewModeChanged(NewViewMode);
	}
}

void ALmBaseCharacter::SetOverlayState_Implementation(ELmOverlayState NewOverlayState) {
	if (NewOverlayState != OverlayState) {
		OnOverlayStateChanged(NewOverlayState);
	}
}

FLmEssentialValues ALmBaseCharacter::GetEssentialValues_Implementation() {
	FLmEssentialValues retValue;
	retValue.Velocity = GetVelocity();
	retValue.Acceleration = Acceleration;
	retValue.MovementInput = GetCharacterMovement()->GetCurrentAcceleration();
	retValue.bIsMoving = bIsMoving;
	retValue.bHasMovementInput = bHasMovementInput;
	retValue.Speed = Speed;
	retValue.MovementInputAmount = MovementInputAmount;
	retValue.AimingRotation = GetControlRotation();
	retValue.AimYawRate = AimYawRate;
	return retValue;
}

FLmCurrentState ALmBaseCharacter::GetCurrentState_Implementation() {
	FLmCurrentState retValue = FLmCurrentState();
	retValue.PawnMovementMode = GetCharacterMovement()->MovementMode;
	retValue.MovementState = MovementState;
	retValue.PrevMovementState = PrevMovementState;
	retValue.MovementAction = MovementAction;
	retValue.RotationMode = RotationMode;
	retValue.ActualGait = Gait;
	retValue.ActualStance = Stance;
	retValue.ViewMode = ViewMode;
	retValue.OverlayState = OverlayState;

	return retValue;
}

FLmCameraParameters ALmBaseCharacter::GetCameraParameters_Implementation() {
	return FLmCameraParameters(ThirdPersonFOV, FirstPersonFOV, bRightShoulder);
}

FVector ALmBaseCharacter::GetFPCameraTarget_Implementation() {
	return GetMesh()->GetSocketLocation(FName("FP_Camera"));
}

FTransform ALmBaseCharacter::Get3PPivotTarget_Implementation() {
	return GetActorTransform();
}

FLmTraceParams ALmBaseCharacter::Get3PTraceParameters_Implementation() {
	return FLmTraceParams(ETT_CameraCollisionChannel, GetActorLocation(), 10.0f);
}