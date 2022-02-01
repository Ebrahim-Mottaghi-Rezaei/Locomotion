#include "ALSBaseCharacter.h"

#include "ClothingSimulationFactoryNv.h"
#include "CALSv4/Core/AI/ALSBaseAIController.h"
#include "CALSv4/Core/Interfaces/ALSAnimationInterface.h"
#include "CALSv4/Core/Interfaces/ALSControllerInterface.h"
#include "CALSv4/Core/Utilities/ALSHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Curves/CurveVector.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AALSBaseCharacter::AALSBaseCharacter() {
	PrimaryActorTick.bCanEverTick = true;

	ALS_ECC_Climbable = UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2);
	ECC__Visibility = UEngineTypes::ConvertToTraceType(ECC_Visibility);

	bUseControllerRotationYaw = false;

	Tags.Add(TEXT("ALS_Character"));

	const auto capsule = GetCapsuleComponent();
	capsule->SetCapsuleHalfHeight(90.0f);
	capsule->SetCapsuleRadius(30.0f);
	capsule->AreaClass = FNavigationSystem::GetDefaultObstacleArea();
	capsule->SetCollisionProfileName(TEXT("ALS_Character"));

	const auto mesh = GetMesh();
	mesh->SetWorldLocation(FVector(0.0f, 0.0f, -92.0f));
	mesh->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> proxyMesh(TEXT("SkeletalMesh'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/Meshes/Proxy.Proxy'"));
	if (proxyMesh.Succeeded())
		mesh->SetSkeletalMesh(proxyMesh.Object);
	else
		UALSLogger::LogError("ProxyMesh not found.");

	mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	mesh->SetCollisionResponseToAllChannels(ECR_Block);
	mesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	mesh->SetCollisionResponseToChannel(UEngineTypes::ConvertToCollisionChannel(ALS_ECC_Climbable), ECR_Ignore);
	mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	mesh->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Ignore);
	mesh->ClothingSimulationFactory = UClothingSimulationFactoryNv::StaticClass();
	mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

	const auto cmc = GetCharacterMovement();
	cmc->MaxAcceleration = 1500.0f;
	cmc->BrakingFrictionFactor = 0.0f;
	cmc->CrouchedHalfHeight = 60.0f;
	cmc->MinAnalogWalkSpeed = 25.0f;
	cmc->bCanWalkOffLedgesWhenCrouching = true;
	cmc->AirControl = 0.15f;
	cmc->GetNavAgentPropertiesRef().bCanCrouch = true;
	cmc->GetNavAgentPropertiesRef().bCanFly = true;
	cmc->bRequestedMoveUseAcceleration = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> MovementDataModel(TEXT("DataTable'/CALSv4/Data/MovementModelTable.MovementModelTable'"));
	if (MovementDataModel.Succeeded()) {
		MovementModel.DataTable = MovementDataModel.Object;
		MovementModel.RowName = FName("Normal");
	} else
		UALSLogger::LogError("MovementModelTable not found.");

	CurrentMovementSettings.WalkSpeed = 165.0f;
	CurrentMovementSettings.RunSpeed = 350.0f;
	CurrentMovementSettings.SprintSpeed = 600.0f;
	static ConstructorHelpers::FObjectFinder<UCurveVector> NormalMovementCurve(TEXT("CurveVector'/Game/AdvancedLocomotionV4/Data/Curves/CharacterMovementCurves/NormalMovement.NormalMovement'"));
	if (MovementDataModel.Succeeded()) {
		CurrentMovementSettings.MovementCurve = NormalMovementCurve.Object;
	} else
		UALSLogger::LogError("Normal Movement Curve not found.");

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
	CurrentMovementSettings.WalkSpeed = 350.0;
	CurrentMovementSettings.WalkSpeed = 600.0;
	static ConstructorHelpers::FObjectFinder<UCurveVector> MovementCurve(TEXT("CurveVector'/Game/AdvancedLocomotionV4/Data/Curves/CharacterMovementCurves/NormalMovement.NormalMovement'"));
	if (MovementCurve.Succeeded())
		CurrentMovementSettings.MovementCurve = MovementCurve.Object;
	else
		UALSLogger::LogError("Mantle_1m not found.");


	IgnoredActors.Add(GetOwner());

	DeltaTimeX = 1.0 / static_cast<float>(AnimationFrameRate);

	AIControllerClass = AALSBaseAIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<UCurveVector> highMantle(TEXT("CurveVector'/Game/AdvancedLocomotionV4/Data/Curves/MantleCurves/Mantle_1m.Mantle_1m'"));
	if (highMantle.Succeeded())
		HighMantle = highMantle.Object;
	else
		UALSLogger::LogError("Mantle_1m not found.");

	static ConstructorHelpers::FObjectFinder<UCurveVector> lowMantle(TEXT("CurveVector'/Game/AdvancedLocomotionV4/Data/Curves/MantleCurves/Mantle_2m.Mantle_2m'"));
	if (lowMantle.Succeeded())
		LowMantle = lowMantle.Object;
	else
		UALSLogger::LogError("Mantle_2m not found.");

	FOnTimelineEvent MantleUpdate;
	//float blendIn;
	MantleUpdate.BindUFunction(this, FName("MantleUpdate"));
	mantleTimeline.SetTimelinePostUpdateFunc(MantleUpdate);

	FOnTimelineEvent MantleEnd;
	MantleEnd.BindUFunction(this, FName("MantleEnd"));
	mantleTimeline.SetTimelineFinishedFunc(MantleEnd);
}

void AALSBaseCharacter::BeginPlay() {
	Super::BeginPlay();
	OnBeginPlay();
}

void AALSBaseCharacter::Tick(const float DeltaTime) {
	Super::Tick(DeltaTime);

	SetEssentialValues();
	switch (MovementState) {
		case EALSMovementState::ALS_Grounded:
			//Do While On Ground
			UpdateCharacterMovement();
			UpdateGroundedRotation();
			break;

		case EALSMovementState::ALS_InAir:
			//Do while In Air
			UpdateInAirRotation();
			//Perform a mantle check if falling while movement input is pressed.
			if (bHasMovementInput)
				MantleCheck(FallingTraceSettings, EDrawDebugTrace::ForOneFrame);
			break;

		case EALSMovementState::ALS_Ragdoll:
			//Do while in Rag-doll
			RagdollUpdate();
			break;
		case EALSMovementState::ALS_None:
		case EALSMovementState::ALS_Mantling:
		default:;
			break;
	}

	CacheValues();
	DrawDebugShapes();
}

void AALSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Checking the player input validity
	if (!IsValid(PlayerInputComponent))
		return;

	//Movement Input
	PlayerInputComponent->BindAxis(FName(TEXT("MoveForward/Backwards")), this, &AALSBaseCharacter::ReceiveMoveForwardBackwards);
	PlayerInputComponent->BindAxis(FName(TEXT("MoveRight/Left")), this, &AALSBaseCharacter::ReceiveMoveRightLeft);

	//Camera Input
	PlayerInputComponent->BindAxis(FName(TEXT("LookUp/Down")), this, &AALSBaseCharacter::PlayerCameraPitchInput);
	PlayerInputComponent->BindAxis(FName(TEXT("LookLeft/Right")), this, &AALSBaseCharacter::PlayerCameraYawInput);

	//Jump Action: Press "Jump Action" to end the rag-doll if rag-dolling, check for a mantle if grounded or in air, stand up if crouching, or jump if standing.
	PlayerInputComponent->BindAction(FName(TEXT("JumpAction")), IE_Pressed, this, &AALSBaseCharacter::PlayerJumpPressedInput);
	PlayerInputComponent->BindAction(FName(TEXT("JumpAction")), IE_Released, this, &AALSBaseCharacter::StopJumping);

	//Stance Action: Press "Stance Action" to toggle Standing / Crouching, double tap to Roll.
	PlayerInputComponent->BindAction(FName(TEXT("StanceAction")), IE_Pressed, this, &AALSBaseCharacter::PlayerStanceActionInput);

	//Gait Actions Type 1: Press "Walk Action" to toggle walking/running, hold "Sprint Action" to sprint.
	PlayerInputComponent->BindAction(FName(TEXT("WalkAction")), IE_Pressed, this, &AALSBaseCharacter::PlayerWalkBegin);
	PlayerInputComponent->BindAction(FName(TEXT("WalkAction")), IE_Released, this, &AALSBaseCharacter::PlayerWalkEnd);

	//Gait Action Type 2 (Unused): Hold "Sprint Action" to run, double tap and hold to sprint.
	PlayerInputComponent->BindAction(FName(TEXT("SprintAction")), IE_Pressed, this, &AALSBaseCharacter::PlayerSprintBegin);
	PlayerInputComponent->BindAction(FName(TEXT("SprintAction")), IE_Released, this, &AALSBaseCharacter::PlayerSprintEnd);

	//Select Rotation Mode: Switch the desired (default) rotation mode to Velocity or Looking Direction. This will be the mode the character reverts back to when un-aiming
	PlayerInputComponent->BindAction(FName(TEXT("ToggleRotationMode")), IE_Pressed, this, &AALSBaseCharacter::ToggleRotationMode);

	//AimAction: Hold "AimAction" to enter the aiming mode, release to revert back the desired rotation mode.
	PlayerInputComponent->BindAction(FName(TEXT("AimAction")), IE_Pressed, this, &AALSBaseCharacter::AimActionBegin);
	PlayerInputComponent->BindAction(FName(TEXT("AimAction")), IE_Released, this, &AALSBaseCharacter::AimActionEnd);

	//Camera Action: Hold "Camera Action" to toggle Third / First Person, tap to swap shoulders.
	PlayerInputComponent->BindAction(FName(TEXT("CameraAction")), IE_Pressed, this, &AALSBaseCharacter::CameraActionBegin);
	PlayerInputComponent->BindAction(FName(TEXT("CameraAction")), IE_Released, this, &AALSBaseCharacter::CameraActionEnd);

	//Ragdoll Action: Press "Ragdoll Action" to toggle the ragdoll state on or off.
	PlayerInputComponent->BindAction(FName(TEXT("RagdollAction")), IE_Pressed, this, &AALSBaseCharacter::ToggleRagdollMode);

}

void AALSBaseCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) {
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
	OnCharacterMovementModeChanged(PrevMovementMode, GetCharacterMovement()->MovementMode, PreviousCustomMode, GetCharacterMovement()->CustomMovementMode);
}

void AALSBaseCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) {
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);

	OnStanceChanged(EALSStance::ALS_Crouching);
}

void AALSBaseCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) {
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);

	OnStanceChanged(EALSStance::ALS_Standing);
}

void AALSBaseCharacter::Landed(const FHitResult& Hit) {
	Super::Landed(Hit);

	if (bBreakFall) {
		BreakFall();
	} else {
		GetCharacterMovement()->BrakingFrictionFactor = bHasMovementInput ? 0.5f : 3.0f;

		FTimerDelegate timerDel;

		timerDel.BindLambda([this] {
			if (GetWorldTimerManager().IsTimerActive(timerHandle_Landing))
				GetWorldTimerManager().ClearTimer(timerHandle_Landing);
			GetCharacterMovement()->BrakingFrictionFactor = 0.0f;
		});

		GetWorldTimerManager().SetTimer(timerHandle_Landing, timerDel, 0.5f, false);
	}
}

void AALSBaseCharacter::OnJumped_Implementation() {
	Super::OnJumped_Implementation();

	//On Jumped: Set the new In Air Rotation to the velocity rotation if speed is greater than 100.
	InAirRotation = Speed > 100.0f ? LastVelocityRotation : GetActorRotation();
	if (IsValid(animInstance) && animInstance->GetClass()->ImplementsInterface(UALSAnimationInterface::StaticClass())) {
		const auto Interface = Cast<IALSAnimationInterface>(animInstance);
		Interface->Jumped_Implementation();
	}
}

FALSControlVectors AALSBaseCharacter::GetControlVectors() {
	FALSControlVectors ControlVectors;

	const FRotator yaw = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);

	ControlVectors.Forward = UKismetMathLibrary::GetForwardVector(yaw);
	ControlVectors.Right = UKismetMathLibrary::GetRightVector(yaw);

	return ControlVectors;
}

FVector AALSBaseCharacter::GetCapsuleBaseLocation(float ZOffset) {
	const auto cc = GetCapsuleComponent();
	return cc->GetComponentLocation() - cc->GetUpVector() * (ZOffset + cc->GetScaledCapsuleHalfHeight());
}

FVector AALSBaseCharacter::GetCapsuleLocationFromBase(FVector baseLocation, float zOffset) {
	return baseLocation + FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + zOffset);
}

float AALSBaseCharacter::GetAnimCurveValue(const FName curveName) {
	return IsValid(animInstance) ? animInstance->GetCurveValue(curveName) : 0.0f;
}

void AALSBaseCharacter::ReceiveMoveForwardBackwards(const float value) {
	forwardInputValue = value;
	PlayerMovementInput(true);
}

void AALSBaseCharacter::ReceiveMoveRightLeft(const float value) {
	rightInputValue = value;
	PlayerMovementInput(false);
}

void AALSBaseCharacter::PlayerMovementInput(const bool bIsForwardAxis) {
	if (MovementState != EALSMovementState::ALS_Grounded && MovementState != EALSMovementState::ALS_InAir)
		return;

	const auto gamepadValues = FixDiagonalGamePadValues(rightInputValue, forwardInputValue);
	const auto controlVectors = GetControlVectors();

	if (bIsForwardAxis) {
		AddMovementInput(controlVectors.Forward, gamepadValues.Y);
	} else {
		AddMovementInput(controlVectors.Right, gamepadValues.X);
	}
}

void AALSBaseCharacter::PlayerCameraYawInput(const float value) {
	AddControllerYawInput(LookLeftRightRate * value);
}

void AALSBaseCharacter::PlayerCameraPitchInput(const float value) {
	AddControllerPitchInput(LookUpDownRate * value);
}

void AALSBaseCharacter::PlayerJumpPressedInput(FKey key) {
	if (MovementAction != EALSMovementAction::ALS_None)
		return;

	if (MovementState == EALSMovementState::ALS_Ragdoll) {
		RagdollEnd();
	} else if (MovementState != EALSMovementState::ALS_Mantling) {
		if (MovementState == EALSMovementState::ALS_Grounded) {
			if (!bHasMovementInput || bHasMovementInput && !MantleCheck(GroundedTraceSettings, EDrawDebugTrace::ForDuration))
				if (Stance == EALSStance::ALS_Standing)
					Jump();
				else
					UnCrouch();

		} else if (MovementState == EALSMovementState::ALS_InAir) {
			MantleCheck(FallingTraceSettings, EDrawDebugTrace::ForDuration);
		}
	}
}

void AALSBaseCharacter::PlayerStanceActionInput(FKey key) {
	if (MovementAction != EALSMovementAction::ALS_None)
		return;

	StanceActionInputCounter++;

	if (GetWorldTimerManager().IsTimerActive(timerHandle_StanceActionInputCounter))
		GetWorldTimerManager().ClearTimer(timerHandle_StanceActionInputCounter);

	FTimerDelegate timerDel;
	timerDel.BindLambda([this] {
		GetWorldTimerManager().ClearTimer(timerHandle_StanceActionInputCounter);

		if (StanceActionInputCounter < 2) {
			if (MovementState == EALSMovementState::ALS_Grounded) {
				if (Stance == EALSStance::ALS_Standing) {
					DesiredStance = EALSStance::ALS_Crouching;
					Crouch();
				} else {
					DesiredStance = EALSStance::ALS_Standing;
					UnCrouch();
				}
			} else if (MovementState == EALSMovementState::ALS_InAir) {
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
			DesiredStance = Stance == EALSStance::ALS_Standing ? EALSStance::ALS_Crouching : EALSStance::ALS_Standing;
		}

		this->StanceActionInputCounter = 0;
	});

	GetWorldTimerManager().SetTimer(timerHandle_StanceActionInputCounter, timerDel, 0.3f, false);
}

void AALSBaseCharacter::PlayerWalkBegin() {
	DesiredGait = EALSGait::ALS_Walking;
}

void AALSBaseCharacter::PlayerWalkEnd() {
	DesiredGait = EALSGait::ALS_Running;
}

void AALSBaseCharacter::PlayerSprintBegin() {
	//Implementing the dual mode functionality on "Sprint Action" input event, 'double tap' or 'hold to sprint'

	if (SprintProcessingMode == EALSInputProcessingMode::ALS_PressAndHold) {
		DesiredGait = EALSGait::ALS_Sprinting;
	} else {
		//UALSLogger::LogInfo(TEXT("Sprint Pressed"));
		bSprintHeld = true;
		SprintTapCounter++;

		DesiredGait = EALSGait::ALS_Running;

		FTimerDelegate del;
		del.BindLambda([this]() {
			if (SprintTapCounter > 1) {
				GetWorldTimerManager().ClearTimer(Sprint_Handle);

				//UALSLogger::LogInfo(TEXT("Sprinting"));
				DesiredGait = EALSGait::ALS_Sprinting;
			} else if (SprintTapCounter == 1) {
				GetWorldTimerManager().ClearTimer(Sprint_Handle);

				//UALSLogger::LogInfo(TEXT("Walking"));
				DesiredGait = EALSGait::ALS_Walking;
			}
		});

		GetWorldTimerManager().SetTimer(Sprint_Handle, del, DoubleTapTime, false);
	}
}

void AALSBaseCharacter::PlayerSprintEnd() {
	if (SprintProcessingMode == EALSInputProcessingMode::ALS_PressAndHold) {
		DesiredGait = EALSGait::ALS_Running;
	} else {
		//UALSLogger::LogError(TEXT("Sprint Released"));

		bSprintHeld = true;

		FTimerDelegate del;
		del.BindLambda([this]() {
			GetWorldTimerManager().ClearTimer(Sprint_Handle);
			//UALSLogger::LogError(TEXT("Running"));

			SprintTapCounter = 0;
			DesiredGait = EALSGait::ALS_Running;
		});

		GetWorldTimerManager().SetTimer(Sprint_Handle, del, DoubleTapTime, false);
	}
}

void AALSBaseCharacter::ToggleRotationMode() {
	if (DesiredRotationMode == EALSRotationMode::ALS_LookingDirection) {
		ChangeRotationMode(EALSRotationMode::ALS_VelocityDirection);
	} else if (DesiredRotationMode == EALSRotationMode::ALS_VelocityDirection) {
		ChangeRotationMode(EALSRotationMode::ALS_LookingDirection);
	}
}

void AALSBaseCharacter::ChangeRotationMode(EALSRotationMode newMode) {
	DesiredRotationMode = newMode;
	SetRotationMode_Implementation(newMode);
}

void AALSBaseCharacter::AimActionBegin() {
	SetRotationMode_Implementation(EALSRotationMode::ALS_Aiming);
}

void AALSBaseCharacter::AimActionEnd() {
	//AimAction: Hold "AimAction" to enter the aiming mode, release to revert back the desired rotation mode.
	SetRotationMode_Implementation(ViewMode == EALSViewMode::ALS_TPS ? DesiredRotationMode : EALSRotationMode::ALS_LookingDirection);
}

void AALSBaseCharacter::CameraActionBegin() {
	//Camera Action: Hold "Camera Action" to toggle Third / First Person, tap to swap shoulders.
	GetWorldTimerManager().ClearTimer(cameraAction_th);

	CameraActionPressType = EALSButtonPressType::ALS_Tapping;

	FTimerDelegate holdAction;
	holdAction.BindLambda([this] {
		if (CameraActionPressType == EALSButtonPressType::ALS_Tapping) {
			CameraActionPressType = EALSButtonPressType::ALS_Holding;
			SetViewMode_Implementation(ViewMode == EALSViewMode::ALS_TPS ? EALSViewMode::ALS_FPS : EALSViewMode::ALS_TPS);
		}
	});

	GetWorldTimerManager().SetTimer(cameraAction_th, holdAction, 0.2f, false);
}

void AALSBaseCharacter::CameraActionEnd() {
	if (CameraActionPressType == EALSButtonPressType::ALS_Tapping) {
		bRightShoulder = !bRightShoulder;
	} else {
		GetWorldTimerManager().ClearTimer(cameraAction_th);
	}

	CameraActionPressType = EALSButtonPressType::ALS_Released;
}

void AALSBaseCharacter::RagdollActionBegin() {
	//Ragdoll Action: Press "Ragdoll Action" to toggle the ragdoll state on or off.
	if (MovementState == EALSMovementState::ALS_Ragdoll) {
		RagdollEnd();
	} else {
		RagdollStart();
	}
}

FVector AALSBaseCharacter::GetPlayerMovementInput() {
	const auto Vectors = GetControlVectors();
	const auto tmp = forwardInputValue * Vectors.Forward + rightInputValue* Vectors.Right;
	return tmp.GetSafeNormal();
}

FVector2D AALSBaseCharacter::FixDiagonalGamePadValues(const float inX, const float inY) {
	FVector2D Retvalue;

	Retvalue.Y = UKismetMathLibrary::Clamp(inY * UKismetMathLibrary::MapRangeClamped(FMath::Abs(inX), 0.0f, 0.6f, 1.0f, 1.2f), -1.0f, 1.0f);
	Retvalue.X = UKismetMathLibrary::Clamp(inX * UKismetMathLibrary::MapRangeClamped(FMath::Abs(inY), 0.0f, 0.6f, 1.0f, 1.2f), -1.0f, 1.0f);

	return Retvalue;
}

void AALSBaseCharacter::SetEssentialValues() {
	//These values represent how the capsule is moving as well as how it wants to move, and therefore are essential for any data driven animation system. They are also used throughout the system for various functions, so I found it is easiest to manage them all in one place.

	//Set the amount of Acceleration.
	Acceleration = CalculateAcceleration();

	//Determine if the character is moving by getting it's speed. The Speed equals the length of the horizontal (x y) velocity, so it does not take vertical movement into account. If the character is moving, update the last velocity rotation. This value is saved because it might be useful to know the last orientation of movement even after the character has stopped.
	FVector nonZvelocity = GetVelocity();
	nonZvelocity.Z = 0.0f;
	Speed = nonZvelocity.Size();
	bIsMoving = Speed > 1.0f;
	LastVelocityRotation = GetVelocity().ToOrientationRotator();

	//Determine if the character has movement input by getting its movement input amount. The Movement Input Amount is equal to the current acceleration divided by the max acceleration so that it has a range of 0-1, 1 being the maximum possible amount of input, and 0 being none. If the character has movement input, update the Last Movement Input Rotation.
	const auto* characterMovement = GetCharacterMovement();
	MovementInputAmount = characterMovement->GetCurrentAcceleration().Size() / characterMovement->GetMaxAcceleration();

	bHasMovementInput = MovementInputAmount > 0.0f;
	if (bHasMovementInput)
		LastMovementInputRotation = characterMovement->GetCurrentAcceleration().ToOrientationRotator();

	//Set the Aim Yaw rate by comparing the current and previous Aim Yaw value, divided by Delta Seconds. This represents the speed the camera is rotating left to right.
	AimYawRate = FMath::Abs((GetControlRotation().Yaw - PreviousAimYaw) / UGameplayStatics::GetWorldDeltaSeconds(this));
}

void AALSBaseCharacter::CacheValues() {
	//Cache certain values to be used in calculations on the next frame
	PreviousVelocity = GetVelocity();
	PreviousAimYaw = GetControlRotation().Yaw;
}

FVector AALSBaseCharacter::CalculateAcceleration() {
	//Calculate the Acceleration by comparing the current and previous velocity. The Current Acceleration returned by the movement component equals the input acceleration, and does not represent the actual physical acceleration of the character.
	return (GetVelocity() - PreviousVelocity) / UGameplayStatics::GetWorldDeltaSeconds(this);
}

void AALSBaseCharacter::OnBeginPlay() {
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
	if (DesiredStance == EALSStance::ALS_Standing) {
		UnCrouch();
	} else {
		Crouch();
	}

	//Set default rotation values.
	const FRotator rotation = GetActorRotation();
	TargetRotation = rotation;
	LastVelocityRotation = rotation;
	LastMovementInputRotation = rotation;
}

void AALSBaseCharacter::OnCharacterMovementModeChanged(EMovementMode PrevMovementMode, EMovementMode NewMovementMode, uint8 PrevCustomMode, uint8 NewCustomMode) {
	if (NewMovementMode == MOVE_Walking || NewMovementMode == MOVE_NavWalking) {
		Execute_SetMovementState(this, EALSMovementState::ALS_Grounded);
	} else if (NewMovementMode == MOVE_Falling) {
		Execute_SetMovementState(this, EALSMovementState::ALS_InAir);
	}
}

void AALSBaseCharacter::OnMovementStateChanged(const EALSMovementState NewMovementState) {
	PrevMovementState = MovementState;
	MovementState = NewMovementState;

	if (MovementState == EALSMovementState::ALS_InAir) {
		//If the character enters the air, set the In Air Rotation and uncrouch if crouched. If the character is currently rolling, enable the Ragdoll.
		if (MovementAction == EALSMovementAction::ALS_None) {
			InAirRotation = GetActorRotation();
			if (Stance == EALSStance::ALS_Crouching)
				UnCrouch();

		} else if (MovementAction == EALSMovementAction::ALS_Rolling) {
			RagdollStart();
		}
	} else if (MovementState == EALSMovementState::ALS_Ragdoll) {
		//Stop the Mantle Timeline if transitioning to the Ragdoll state while mantling.
		if (PrevMovementState == EALSMovementState::ALS_Mantling)
			mantleTimeline.Stop();
	}
}

void AALSBaseCharacter::OnMovementActionChanged(const EALSMovementAction NewMovementAction) {
	const auto PrevMovementAction = MovementAction;
	MovementAction = NewMovementAction;
	//Make the character crouch if performing a roll.
	if (MovementAction == EALSMovementAction::ALS_Rolling) {
		Crouch();
	}

	//Upon ending a roll, reset the stance back to its desired value.
	if (PrevMovementAction == EALSMovementAction::ALS_Rolling) {
		if (DesiredStance == EALSStance::ALS_Standing)
			UnCrouch();
		else
			Crouch();
	}
}

void AALSBaseCharacter::OnStanceChanged(const EALSStance NewStance) {
	const auto prevStance = Stance;
	Stance = NewStance;
}

void AALSBaseCharacter::OnRotationModeChanged(const EALSRotationMode NewRotationMode) {
	const auto prevRotationMode = RotationMode;
	RotationMode = NewRotationMode;

	if (RotationMode == EALSRotationMode::ALS_VelocityDirection && ViewMode == EALSViewMode::ALS_FPS)
		SetViewMode_Implementation(EALSViewMode::ALS_TPS);
}

void AALSBaseCharacter::OnGaitChanged(const EALSGait NewActualGait) {
	const auto prevGait = Gait;
	Gait = NewActualGait;
}

void AALSBaseCharacter::OnViewModeChanged(const EALSViewMode NewViewMode) {
	const auto prevViewMode = ViewMode;
	ViewMode = NewViewMode;

	if (ViewMode == EALSViewMode::ALS_TPS) {
		//If Third Person, set the rotation mode back to the desired mode.
		if (RotationMode != EALSRotationMode::ALS_Aiming)
			SetRotationMode_Implementation(DesiredRotationMode);
	} else {
		//If First Person, set the rotation mode to looking direction if currently in the velocity direction mode.
		if (RotationMode == EALSRotationMode::ALS_VelocityDirection)
			SetRotationMode_Implementation(EALSRotationMode::ALS_LookingDirection);
	}
}

void AALSBaseCharacter::OnOverlayStateChanged(const EALSOverlayState NewOverlayState) {
	const auto prevOverlayState = OverlayState;
	OverlayState = NewOverlayState;
}

void AALSBaseCharacter::SetMovementModel() {
	// Search using FindRow. It returns a handle to the row.
	// Access the variables like GOLookupRow->Blueprint_Class, GOLookupRow->UseCode
	MovementData = *MovementModel.DataTable->FindRow<FALSMovementSettingsState>(MovementModel.RowName, nullptr);
}

void AALSBaseCharacter::UpdateCharacterMovement() {
	//Set the Allowed Gait
	const EALSGait allowedGait = GetAllowedGait();

	//Determine the Actual Gait. If it is different from the current Gait, Set the new Gait Event.
	const auto actualGait = GetActualGait(allowedGait);
	if (Gait != actualGait)
		SetGait_Implementation(actualGait);

	//Use the allowed gait to update the movement settings.
	UpdateDynamicMovementSettings(allowedGait);
}

void AALSBaseCharacter::UpdateDynamicMovementSettings(EALSGait AllowedGait) {
	CurrentMovementSettings = GetTargetMovementSettings();
	const auto cm = GetCharacterMovement();

	//Update the Character Max Walk Speed to the configured speeds based on the currently Allowed Gait.
	if (AllowedGait == EALSGait::ALS_Walking) {
		cm->MaxWalkSpeed = CurrentMovementSettings.WalkSpeed;
	} else if (AllowedGait == EALSGait::ALS_Running) {
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

FALSMovementSettings AALSBaseCharacter::GetTargetMovementSettings() {
	if (RotationMode == EALSRotationMode::ALS_VelocityDirection) {
		if (Stance == EALSStance::ALS_Standing)
			return MovementData.VelocityDirection.Standing;
		return MovementData.VelocityDirection.Crouching;
	}

	if (RotationMode == EALSRotationMode::ALS_LookingDirection) {
		if (Stance == EALSStance::ALS_Standing)
			return MovementData.LookingDirection.Standing;
		return MovementData.LookingDirection.Crouching;
	}

	// since this is not those 2 cases above, this is Aiming mode for sure
	if (Stance == EALSStance::ALS_Standing)
		return MovementData.Aiming.Standing;
	return MovementData.Aiming.Crouching;
}

EALSGait AALSBaseCharacter::GetAllowedGait() {
	//Calculate the Allowed Gait. This represents the maximum Gait the character is currently allowed to be in, and can be determined by the desired gait, the rotation mode, the stance, etc. For example, if you wanted to force the character into a walking state while indoors, this could be done here.
	if (Stance == EALSStance::ALS_Standing) {
		if (RotationMode != EALSRotationMode::ALS_Aiming) {
			if (DesiredGait == EALSGait::ALS_Walking || DesiredGait == EALSGait::ALS_Running)
				return  DesiredGait;

			return CanSprint() ? EALSGait::ALS_Sprinting : EALSGait::ALS_Running;
		}
	}

	return DesiredGait == EALSGait::ALS_Walking ? EALSGait::ALS_Walking : EALSGait::ALS_Running;

}

EALSGait AALSBaseCharacter::GetActualGait(EALSGait AllowedGait) {
	if (Speed >= CurrentMovementSettings.RunSpeed + 10)
		return AllowedGait == EALSGait::ALS_Sprinting ? EALSGait::ALS_Sprinting : EALSGait::ALS_Running;

	return  Speed >= CurrentMovementSettings.WalkSpeed + 10 ? EALSGait::ALS_Running : EALSGait::ALS_Walking;
}

bool AALSBaseCharacter::CanSprint() {
	if (!bHasMovementInput || RotationMode == EALSRotationMode::ALS_Aiming)
		return false;

	if (RotationMode == EALSRotationMode::ALS_VelocityDirection)
		return  MovementInputAmount > 0.9f;

	float yaw = UKismetMathLibrary::NormalizedDeltaRotator(GetCharacterMovement()->GetCurrentAcceleration().ToOrientationRotator(), GetControlRotation()).Yaw;

	yaw = FMath::Abs(yaw);
	return MovementInputAmount > 0.9f && yaw < 50.0f;
}

float AALSBaseCharacter::GetMappedSpeed() {
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

UAnimMontage* AALSBaseCharacter::GetRollAnimation() {
	//This gets overriden in the AnimMan Child character to select the appropriate animation based on the overlay state.
	return nullptr;
}

void AALSBaseCharacter::UpdateGroundedRotation() {
	if (MovementAction == EALSMovementAction::ALS_Rolling) {
		if (bHasMovementInput) {
			SmoothCharacterRotation(FRotator(0, LastMovementInputRotation.Yaw, 0), 0.0f, 2.0f);
		}
	} else if (MovementAction == EALSMovementAction::ALS_None) {
		if (CanUpdateMovingRotation()) {
			if (RotationMode == EALSRotationMode::ALS_VelocityDirection) {
				//Velocity Direction Rotation
				SmoothCharacterRotation(FRotator(0.0f, LastVelocityRotation.Yaw, 0.0f), 800.0f, CalculateGroundedRotationRate());
			} else if (RotationMode == EALSRotationMode::ALS_LookingDirection) {
				//Looking Direction Rotation
				if (Gait == EALSGait::ALS_Sprinting) {
					SmoothCharacterRotation(FRotator(0, LastVelocityRotation.Yaw, 0), 500.0f, CalculateGroundedRotationRate());
				} else {
					SmoothCharacterRotation(FRotator(0, GetControlRotation().Yaw + GetAnimCurveValue(FName(TEXT("YawOffset"))), 0), 500.0f, CalculateGroundedRotationRate());
				}
			} else {
				//Aiming Rotation
				SmoothCharacterRotation(FRotator(0, GetControlRotation().Yaw, 0), 1000.0f, 20.0f);
			}
		} else {
			//Not Moving
			if (ViewMode == EALSViewMode::ALS_FPS || RotationMode == EALSRotationMode::ALS_Aiming)
				LimitRotation(-100.0f, 100.0f, 20.0f);

			//Apply the RotationAmount curve from Turn In Place Animations. The Rotation Amount curve defines how much rotation should be applied each frame, and is calculated for animations that are animated at 30fps.
			const float curveAmount = GetAnimCurveValue(FName(TEXT("RotationAmount")));
			if (FMath::Abs(curveAmount) > 0.001f) {
				AddActorWorldRotation(FRotator(0.0f, curveAmount * (UGameplayStatics::GetWorldDeltaSeconds(this) / DeltaTimeX), 0.0f));
				TargetRotation = GetActorRotation();
			}
		}
	}
}

void AALSBaseCharacter::UpdateInAirRotation() {
	if (RotationMode == EALSRotationMode::ALS_Aiming) {
		SmoothCharacterRotation(FRotator(0.0f, GetControlRotation().Yaw, 0.0f), 0.0f, 15.0f);
		InAirRotation = GetActorRotation();
	} else {
		SmoothCharacterRotation(FRotator(0.0f, InAirRotation.Yaw, 0.0f), 0.0f, 5.0f);
	}
}

void AALSBaseCharacter::SmoothCharacterRotation(FRotator Target, float TargetInterpSpeedConst, float ActorInterpSpeedSmooth) {
	//Interpolate the Target Rotation for extra smooth rotation behavior
	TargetRotation = UKismetMathLibrary::RInterpTo_Constant(TargetRotation, Target, UGameplayStatics::GetWorldDeltaSeconds(this), TargetInterpSpeedConst);

	SetActorRotation(UKismetMathLibrary::RInterpTo(GetActorRotation(), Target, UGameplayStatics::GetWorldDeltaSeconds(this), ActorInterpSpeedSmooth));
}

void AALSBaseCharacter::AddToCharacterRotation(FRotator DeltaRotation) {
	TargetRotation = UKismetMathLibrary::ComposeRotators(TargetRotation, DeltaRotation);
	AddActorWorldRotation(DeltaRotation);
}

void AALSBaseCharacter::LimitRotation(float AimYawMin, float AimYawMax, float InterpSpeed) {
	const float deltaYaw = UKismetMathLibrary::NormalizedDeltaRotator(GetControlRotation(), GetActorRotation()).Yaw;

	const float controlYaw = GetControlRotation().Yaw;
	if (UKismetMathLibrary::InRange_FloatFloat(deltaYaw, AimYawMin, AimYawMax))
		return;

	SmoothCharacterRotation(FRotator(0.0f, controlYaw + deltaYaw > 0 ? AimYawMin : AimYawMax, 0.0f), 0.0f, InterpSpeed);
}

FALSHitResult AALSBaseCharacter::SetActorLocationRotationUpdateTarget(FVector NewLocation, FRotator NewRotation, bool bSweep, bool bTeleport) {
	TargetRotation = NewRotation;
	FALSHitResult HitResult;

	const bool result = SetActorLocationAndRotation(NewLocation, NewRotation, bSweep, &HitResult.SweepHitResult);
	HitResult.bHit = result;

	return HitResult;
}

float AALSBaseCharacter::CalculateGroundedRotationRate() {
	//Calculate the rotation rate by using the current Rotation Rate Curve in the Movement Settings. Using the curve in conjunction with the mapped speed gives you a high level of control over the rotation rates for each speed. Increase the speed if the camera is rotating quickly for more responsive rotation.
	return CurrentMovementSettings.RotationRateCurve->GetFloatValue(GetMappedSpeed() * UKismetMathLibrary::MapRangeClamped(AimYawRate, 0.0, 300.0f, 1.0f, 3.0f));
}

bool AALSBaseCharacter::CanUpdateMovingRotation() {
	return !HasAnyRootMotion() && (bIsMoving && bHasMovementInput || Speed > 15000);
}

bool AALSBaseCharacter::MantleCheck(FALSMantleTraceSettings TraceSettings, TEnumAsByte<EDrawDebugTrace::Type> DebugType) {
	//Step 1: Trace forward to find a wall / object the character cannot walk on.
	const FVector start = GetCapsuleBaseLocation(2.0f) - 30 * GetPlayerMovementInput() + FVector(0.0f, 0.0f, (TraceSettings.MaxLedgeHeight + TraceSettings.MinLedgeHeight) / 2.0f);
	const FVector end = start + GetPlayerMovementInput() * TraceSettings.ReachDistance;
	const float halfHeight = 1.0f + (TraceSettings.MaxLedgeHeight - TraceSettings.MinLedgeHeight) / 2;

	FHitResult HitResult;

	UKismetSystemLibrary::CapsuleTraceSingle(this, start, end, TraceSettings.ForwardTraceRadius, halfHeight, ALS_ECC_Climbable, false, IgnoredActors, DebugType, HitResult, true, FColor::Black, FColor::Black, 1.0f);

	if (!HitResult.bBlockingHit || HitResult.bStartPenetrating || GetCharacterMovement()->IsWalkable(HitResult))
		return false;

	//Step 2: Trace downward from the first trace's Impact Point and determine if the hit location is walkable.
	const FVector impactPoint = HitResult.ImpactPoint;
	const FVector impactNormal = HitResult.ImpactNormal;

	const FVector end2 = -15.0f * impactNormal + FVector(impactPoint.X, impactPoint.Y, GetCapsuleBaseLocation(2.0f).Z);
	const FVector start2 = end2 + FVector(0.0f, 0.0f, TraceSettings.MaxLedgeHeight + TraceSettings.DownwardTraceRadius + 1.0f);
	UKismetSystemLibrary::SphereTraceSingle(this, start2, end2, TraceSettings.DownwardTraceRadius, ALS_ECC_Climbable, false, IgnoredActors, DebugType, HitResult, true, FColor::Orange, FColor::Red, 1.0f);

	if (!HitResult.bBlockingHit || !GetCharacterMovement()->IsWalkable(HitResult))
		return false;

	FVector DownTraceLocation = FVector(HitResult.Location.X, HitResult.Location.Y, impactPoint.Z);
	UPrimitiveComponent * HitComponent = HitResult.Component.Get();

	//Step 3: Check if the capsule has room to stand at the downward trace's location. If so, set that location as the Target Transform and calculate the mantle height.
	const FVector targetLocation = GetCapsuleLocationFromBase(DownTraceLocation, 2.0f);

	if (!CapsuleHasRoomCheck(GetCapsuleComponent(), targetLocation, 0.0f, 0.0f, DebugType)) return false;

	const FTransform TargetTransform = FTransform(UKismetMathLibrary::Multiply_VectorVector(impactNormal, FVector(-1.0f, -1.0f, 0.0f)).ToOrientationRotator(), targetLocation);
	const float mantleHeight = (TargetTransform.GetLocation() - GetActorLocation()).Z;

	//Step 4: Determine the Mantle Type by checking the movement mode and Mantle Height.
	EALSMantleType mantleType;
	if (MovementState == EALSMovementState::ALS_InAir) {
		mantleType = EALSMantleType::ALS_FallingCatch;
	} else {
		mantleType = mantleHeight > 125.0f ? EALSMantleType::ALS_HighMantle : EALSMantleType::ALS_LowMantle;
	}

	//Step 5: If everything checks out, start the Mantle
	MantleStart(mantleHeight, FALSComponentAndTransform(TargetTransform, HitComponent), mantleType);
	return true;
}

void AALSBaseCharacter::MantleStart(float MantleHeight, FALSComponentAndTransform MantleLedgeWS, EALSMantleType MantleType) {
	//Step 1: Get the Mantle Asset and use it to set the new Mantle Params.
	const auto mantleAsset = GetMantleAsset(MantleType);

	float playRate = UKismetMathLibrary::MapRangeClamped(MantleHeight, mantleAsset.LowHeight, mantleAsset.HighHeight, mantleAsset.LowPlayRate, mantleAsset.HighPlayRate);

	float startingPosition = UKismetMathLibrary::MapRangeClamped(MantleHeight, mantleAsset.LowHeight, mantleAsset.HighHeight, mantleAsset.LowStartPosition, mantleAsset.HighStartPosition);

	auto mantleParams = FALSMantleParams(mantleAsset.AnimMontage, mantleAsset.PositionCorrectionCurve, startingPosition, mantleAsset.StartingOffset, playRate);

	//Step 2: Convert the world space target to the mantle component's local space for use in moving objects.
	MantleLedgeLS = UALSHelpers::WorldSpaceToLocalSpace(MantleLedgeWS);

	//Step 3: Set the Mantle Target and calculate the Starting Offset(offset amount between the actor and target transform).
	MantleTarget = MantleLedgeWS.Transform;
	MantleActualStartOffset = UALSHelpers::SubtractTransform(GetActorTransform(), MantleTarget);

	//Step 4: Calculate the Animated Start Offset from the Target Location. This would be the location the actual animation starts at relative to the Target Transform.
	const FVector tmp = MantleTarget.Rotator().Vector() * mantleParams.StartingOffset.Y;
	const FVector v = FVector(tmp.X, tmp.Y, mantleParams.StartingOffset.Z);
	MantleAnimatedStartOffset = UALSHelpers::SubtractTransform(FTransform(MantleTarget.Rotator(), MantleTarget.GetLocation() - v), MantleTarget);

	//Step 5: Clear the Character Movement Mode and set the Movement State to Mantling
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	SetMovementState_Implementation(EALSMovementState::ALS_Mantling);

	//Step 6: Configure the Mantle Timeline so that it is the same length as the Lerp/Correction curve minus the starting position, and plays at the same speed as the animation. Then start the timeline.
	float timelineMin, timelineMax;
	mantleParams.PositionCorrectionCurve->GetTimeRange(timelineMin, timelineMax);
	mantleTimeline.SetTimelineLength(timelineMax - mantleParams.StartingPosition);

	mantleTimeline.SetPlayRate(mantleParams.PlayRate);
	mantleTimeline.PlayFromStart();

	//Step 7: Play the Anim Montage if valid.
	if (IsValid(mantleParams.AnimMontage) && IsValid(animInstance)) {
		animInstance->Montage_Play(mantleParams.AnimMontage, mantleParams.PlayRate, EMontagePlayReturnType::MontageLength, mantleParams.StartingPosition);
	}
}

void AALSBaseCharacter::MantleUpdate(float BlendIn) {
	//Step 1: Continually update the mantle target from the stored local transform to follow along with moving objects.
	MantleTarget = UALSHelpers::LocalSpaceToWorldSpace(MantleLedgeLS).Transform;

	//Step 2: Update the Position and Correction Alphas using the Position/Correction curve set for each Mantle.
	const FVector VectorValue = MantleParams.PositionCorrectionCurve->GetVectorValue(MantleParams.StartingPosition + mantleTimeline.GetPlaybackPosition());

	float positionAlpha = VectorValue.X;
	float XYCorrectionAlpha = VectorValue.Y;
	float ZCorrection = VectorValue.Z;

	//Step 3: Lerp multiple transforms together for independent control over the horizontal and vertical blend to the animated start position, as well as the target position.

	//Blend into the animated horizontal and rotation offset using the Y value of the Position/Correction Curve.
	const auto Bh = FTransform(MantleAnimatedStartOffset.GetRotation(), FVector(MantleAnimatedStartOffset.GetLocation().X, MantleAnimatedStartOffset.GetLocation().Y, MantleActualStartOffset.GetLocation().Z));
	const auto horizontalTransform = UKismetMathLibrary::TLerp(MantleActualStartOffset, Bh, XYCorrectionAlpha);

	//Blend into the animated vertical offset using the Z value of the Position / Correction Curve.
	const auto Bv = FTransform(MantleActualStartOffset.GetRotation(), FVector(MantleActualStartOffset.GetLocation().X, MantleActualStartOffset.GetLocation().Y, MantleAnimatedStartOffset.GetLocation().Z));
	const auto verticalTransform = UKismetMathLibrary::TLerp(MantleActualStartOffset, Bv, XYCorrectionAlpha);

	const auto t1 = FTransform(Bh.GetRotation(), FVector(Bh.GetLocation().X, Bh.GetLocation().Y, Bv.GetLocation().Z));

	//Blend from the currently blending transforms into the final mantle target using the X value of the Position/Correction Curve.
	const auto t2 = UKismetMathLibrary::TLerp(MantleTarget + t1, MantleTarget, positionAlpha);

	//Initial Blend In (controlled in the timeline curve) to allow the actor to blend into the Position/Correction curve at the mid point. This prevents pops when mantling an object lower than the animated mantle.
	const auto lerpedTarget = UKismetMathLibrary::TLerp(MantleTarget + MantleActualStartOffset, t2, BlendIn);

	//Step 4: Set the actors location and rotation to the Lerped Target.
	SetActorLocationRotationUpdateTarget(lerpedTarget.GetLocation(), lerpedTarget.Rotator(), false, false);
}

void AALSBaseCharacter::MantleEnd() {
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

bool AALSBaseCharacter::CapsuleHasRoomCheck(UCapsuleComponent * Capsule, const FVector TargetLocation, const float HeightOffset, const float RadiusOffset, const TEnumAsByte<EDrawDebugTrace::Type> DebugType) {
	float Z =
		GetCapsuleComponent()->GetScaledCapsuleHalfHeight_WithoutHemisphere() -
		RadiusOffset +
		HeightOffset;

	FHitResult HitResult;

	UKismetSystemLibrary::SphereTraceSingleByProfile(this, TargetLocation + FVector(0.0f, 0.0f, Z), TargetLocation - FVector(0.0f, 0.0f, Z), GetCapsuleComponent()->GetUnscaledCapsuleRadius() + RadiusOffset, FName(TEXT("ALS_Character")), false, IgnoredActors, DebugType, HitResult, true, FColor::FromHex(TEXT("21E525FF")), FColor::FromHex(TEXT("EE4AFFFF")), 1.0f);

	return !HitResult.bBlockingHit && !HitResult.bStartPenetrating;
}

FALSMantleAsset AALSBaseCharacter::GetMantleAsset(EALSMantleType MantleType) {
	//Get the Default Mantle Asset values.These will be overriden in the AnimMan Child Character
	if (MantleType == EALSMantleType::ALS_HighMantle) {
		return FALSMantleAsset(nullptr, HighMantle, FVector(0.0f, 65.0f, 200.0f), 50.0f, 1.0f, 0.5f, 100.0f, 1.0f, 0.0f);
	}

	if (MantleType == EALSMantleType::ALS_LowMantle) {
		return FALSMantleAsset(nullptr, LowMantle, FVector(0.0f, 65.0f, 200.0f), 125.0f, 1.2f, 0.6f, 200.0f, 1.2f, 0.0f);
	}

	return FALSMantleAsset(nullptr, LowMantle, FVector(0.0f, 65.0f, 200.0f), 125.0f, 1.2f, 0.6f, 200.0f, 1.2f, 0.0f);
}

void AALSBaseCharacter::RagdollStart() {
	UALSLogger::LogInfo(TEXT("Calling in ALSBaseCharacter"));
	//Step 1: Clear the Character Movement Mode and set the Movement State to Ragdoll
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	SetMovementState_Implementation(EALSMovementState::ALS_Ragdoll);

	//Step 2: Disable capsule collision and enable mesh physics simulation starting from the pelvis.
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionObjectType(ECC_PhysicsBody);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetAllBodiesBelowSimulatePhysics(FName(TEXT("pelvis")), true);

	//Step 3: Stop any active montages
	animInstance->Montage_Stop(0.2f);
}

void AALSBaseCharacter::RagdollEnd() {
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

void AALSBaseCharacter::RagdollUpdate() {
	//Set the Last Ragdoll Velocity
	LastRagdollVelocity = GetMesh()->GetPhysicsLinearVelocity(FName(TEXT("root")));

	//Use the Ragdoll Velocity to scale the ragdoll's joint strength for physical animation
	GetMesh()->SetAllMotorsAngularDriveParams(UKismetMathLibrary::MapRangeClamped(LastRagdollVelocity.Size(), 0.0f, 1000.0f, 0.0f, 25000.0f), 0.0f, 0.0f);

	//Disable Gravity if falling faster than -4000 to prevent continual acceleration. This also prevents the ragdoll from going through the floor.
	GetMesh()->SetEnableGravity(LastRagdollVelocity.Z > -4000.0f);

	//Update the Actor location to follow the ragdoll.
	SetActorLocationDuringRagdoll();
}

void AALSBaseCharacter::ToggleRagdollMode() {
	if (MovementState == EALSMovementState::ALS_Ragdoll) {
		RagdollEnd();
	} else {
		RagdollStart();
	}
}

void AALSBaseCharacter::SetActorLocationDuringRagdoll() {
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

UAnimMontage* AALSBaseCharacter::GetGetupAnimation(const bool bIsRagdollFacedUp) {
	//This gets overriden in the AnimMan Child character to select the appropriate animation based on the overlay state.

	return nullptr;
}

void AALSBaseCharacter::DrawDebugShapes() {
	const auto pc = UGameplayStatics::GetPlayerController(this, 0);
	if (!pc || !pc->GetClass()->ImplementsInterface(UALSControllerInterface::StaticClass()) || !IALSControllerInterface::Execute_GetDebugInfo(pc).bShowDebugShapes)
		return;

	//Velocity Arrow
	const FVector arrow1Start = GetActorLocation() - FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	const FVector arrow1End = arrow1Start + (GetVelocity() == FVector::ZeroVector ? LastVelocityRotation.Vector() : GetVelocity()).GetUnsafeNormal() * UKismetMathLibrary::MapRangeClamped(GetVelocity().Size(), 0.0f, GetCharacterMovement()->MaxWalkSpeed, 50.0f, 75.0f);
	UKismetSystemLibrary::DrawDebugArrow(this,
										 arrow1Start,
										 arrow1End,
										 60.0f,
										 GetVelocity() == FVector::ZeroVector ? FColor::FromHex(TEXT("890089FF")) : FColor::FromHex(TEXT("FF00FFFF")));

	//Movement Input Arrow
	const FVector arrow2Start = GetActorLocation() - FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - 3.5f);
	const FVector arrow2End = arrow1Start +
		(GetCharacterMovement()->GetCurrentAcceleration() == FVector::ZeroVector ? LastMovementInputRotation.Vector() : GetVelocity()).GetUnsafeNormal() *
		UKismetMathLibrary::MapRangeClamped(GetCharacterMovement()->GetCurrentAcceleration().Size() / GetCharacterMovement()->GetMaxAcceleration(),
											0.0f, 1.0f, 50.0f, 75.0f);
	UKismetSystemLibrary::DrawDebugArrow(this,
										 arrow2Start,
										 arrow2End,
										 60.0f,
										 GetVelocity() == FVector::ZeroVector ? FColor::FromHex(TEXT("896300FF")) : FColor::FromHex(TEXT("FFBC00FF")));

	//Target Rotation Arrow
	const FVector arrow3Start = GetActorLocation() - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - 7.0f);
	const FVector arrow3End = arrow3Start + TargetRotation.Vector().GetUnsafeNormal() * 50.0f;

	UKismetSystemLibrary::DrawDebugArrow(this, arrow3Start, arrow3End, 50.0f, FColor::FromHex(TEXT("009CFFFF")), 0.0f, 3.0f);

	//Aiming Rotation Cone
	UKismetSystemLibrary::DrawDebugCone(this, GetMesh()->GetSocketLocation(FName(TEXT("FP_Camera"))), GetControlRotation().Vector().GetUnsafeNormal(), 100.0f, 30.0f, 30.0f, 8, FColor::FromHex(TEXT("009CFFFF")), 0.0f, 5.0f);

	//Capsule 
	UKismetSystemLibrary::DrawDebugCapsule(this, GetActorLocation(), GetCapsuleComponent()->GetScaledCapsuleHalfHeight(), GetCapsuleComponent()->GetScaledCapsuleRadius(), GetActorRotation(), FColor::Black, 0.0f, 0.3f);
}

TEnumAsByte<EDrawDebugTrace::Type> AALSBaseCharacter::GetTraceDebugType(TEnumAsByte<EDrawDebugTrace::Type> showTraceType) {
	const auto pc = UGameplayStatics::GetPlayerController(this, 0);

	//Check if the player implements the IALSControllerInterface and Check if bShow debug values is set true;
	return  pc->GetClass()->ImplementsInterface(UALSControllerInterface::StaticClass()) && IALSControllerInterface::Execute_GetDebugInfo(pc).bShowDebugShapes ? showTraceType : EDrawDebugTrace::None;
}

void AALSBaseCharacter::BreakFall() {
	if (IsValid(animInstance)) {
		animInstance->Montage_Play(GetRollAnimation(), 1.35f);
	}
}

void AALSBaseCharacter::Roll() {
	if (IsValid(animInstance)) {
		animInstance->Montage_Play(GetRollAnimation(), 1.15f);
	}
}

void AALSBaseCharacter::SetMovementState_Implementation(EALSMovementState NewMovementState) {
	if (NewMovementState != MovementState) {
		OnMovementStateChanged(NewMovementState);
	}
}

void AALSBaseCharacter::SetMovementAction_Implementation(EALSMovementAction NewMovementAction) {
	if (NewMovementAction != MovementAction) {
		OnMovementActionChanged(NewMovementAction);
	}
}

void AALSBaseCharacter::SetRotationMode_Implementation(EALSRotationMode NewRotationMode) {
	if (NewRotationMode != RotationMode) {
		OnRotationModeChanged(NewRotationMode);
	}
}

void AALSBaseCharacter::SetGait_Implementation(EALSGait NewGait) {
	if (NewGait != Gait) {
		OnGaitChanged(NewGait);
	}
}

void AALSBaseCharacter::SetViewMode_Implementation(EALSViewMode NewViewMode) {
	if (NewViewMode != ViewMode) {
		OnViewModeChanged(NewViewMode);
	}
}

void AALSBaseCharacter::SetOverlayState_Implementation(EALSOverlayState NewOverlayState) {
	if (NewOverlayState != OverlayState) {
		OnOverlayStateChanged(NewOverlayState);
	}
}

FALSEssentialValues AALSBaseCharacter::GetEssentialValues_Implementation() {
	FALSEssentialValues retValue;
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

FALSCurrentState AALSBaseCharacter::GetCurrentState_Implementation() {
	FALSCurrentState retValue = FALSCurrentState();
	retValue.PawnMovementMode = GetCharacterMovement()->MovementMode;
	retValue.MovementState = MovementState;
	retValue.PrevMovementState = PrevMovementState;
	retValue.RotationMode = RotationMode;
	retValue.ActualGait = Gait;
	retValue.ActualStance = Stance;
	retValue.ViewMode = ViewMode;
	retValue.OverlayState = OverlayState;
	return retValue;
}

FALSCameraParameters AALSBaseCharacter::GetCameraParameters_Implementation() {
	return FALSCameraParameters(ThirdPersonFOV, FirstPersonFOV, bRightShoulder);
}

FVector AALSBaseCharacter::GetFPCameraTarget_Implementation() {
	return GetMesh()->GetSocketLocation(FName("FP_Camera"));
}

FTransform AALSBaseCharacter::Get3PPivotTarget_Implementation() {
	return GetActorTransform();
}

FALSTraceParams AALSBaseCharacter::Get3PTraceParameters_Implementation() {
	return FALSTraceParams(ECC__Visibility, GetActorLocation(), 10.0f);
}