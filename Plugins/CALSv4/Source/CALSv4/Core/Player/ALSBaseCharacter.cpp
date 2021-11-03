#include "ALSBaseCharacter.h"

#include "CALSv4/Core/Interfaces/ALSAnimationInterface.h"
#include "CALSv4/Core/Interfaces/ALSControllerInterface.h"
#include "CALSv4/Core/Utilities/ALSHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Curves/CurveVector.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AALSBaseCharacter::AALSBaseCharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	ignoredActors.Add(GetOwner());
	ECC_Climbable = UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2);
	frameDeltaTime = 1.0 / static_cast<float>(AnimationFrameRate);

	//FOnTimelineEvent MantleUpdate;
	//float blendIn;
	//MantleUpdate.BindUFunction(this, FName("MantleUpdate"), blendIn);
	//mantleTimeline.SetTimelinePostUpdateFunc(MantleUpdate);

	
}

// Called when the game starts or when spawned
void AALSBaseCharacter::BeginPlay() {
	Super::BeginPlay();
	OnBeginPlay();
}

// Called every frame
void AALSBaseCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	SetEssentialValues();
	switch (MovementState) {
	case EALSMovementState::ALS_None:break;
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
	case EALSMovementState::ALS_Mantling: break;
	case EALSMovementState::ALS_Ragdoll:
		//Do while in Ragdoll
		RagdollUpdate();
		break;
	default:;
	}
}

// Called to bind functionality to input
void AALSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Checking the player input validity
	check(PlayerInputComponent)

		//Movement Input
		PlayerInputComponent->BindAxis(FName(TEXT("MoveForward/Backwards")), this, &AALSBaseCharacter::ReceiveMoveForwardBackwards);
	PlayerInputComponent->BindAxis(FName(TEXT("MoveRight/Left")), this, &AALSBaseCharacter::ReceiveMoveRightLeft);

	//Camera Input
	PlayerInputComponent->BindAxis(FName(TEXT("LookUp/Down")), this, &AALSBaseCharacter::PlayerCameraPitchInput);
	PlayerInputComponent->BindAxis(FName(TEXT("LookLeft/Right")), this, &AALSBaseCharacter::PlayerCameraYawInput);

	//Jump Action: Press "Jump Action" to end the ragdoll if ragdolling, check for a mantle if grounded or in air, stand up if crouching, or jump if standing.
	PlayerInputComponent->BindAction(FName(TEXT("JumpAction")), IE_Pressed, this, &AALSBaseCharacter::PlayerJumpPressedInput);
	PlayerInputComponent->BindAction(FName(TEXT("JumpAction")), IE_Released, this, &AALSBaseCharacter::StopJumping);

	PlayerInputComponent->BindAction(FName(TEXT("StanceAction")), IE_Pressed, this, &AALSBaseCharacter::PlayerStanceActionInput);
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
		if (bHasMovementInput) {
			GetCharacterMovement()->BrakingFrictionFactor = 0.5f;
		} else {
			GetCharacterMovement()->BrakingFrictionFactor = 3.0f;
		}

		FTimerDelegate timerDel;
		timerDel.BindUFunction(this, FName("ResetBrakingFrictionTimer"));
		GetWorldTimerManager().SetTimer(timerHandle_ResetBrakingFactor, timerDel, 0.5f, false);
	}
}

void AALSBaseCharacter::OnJumped_Implementation() {
	Super::OnJumped_Implementation();

	//On Jumped: Set the new In Air Rotation to the velocity rotation if speed is greater than 100.
	InAirRotation = Speed > 100.0f ? LastVelocityRotation : GetActorRotation();
	if (IsValid(animInstance) && animInstance->GetClass()->ImplementsInterface(UALSAnimationInterface::StaticClass()))
		IALSAnimationInterface::Execute_Jumped(this);

}

FALSControlVectors AALSBaseCharacter::GetControlVectors() {
	FALSControlVectors ControlVectors;
	ControlVectors.Forward = UKismetMathLibrary::GetForwardVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	ControlVectors.Right = UKismetMathLibrary::GetRightVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));

	return ControlVectors;
}

FVector AALSBaseCharacter::GetCapsuleBaseLocation(float ZOffset) {
	const auto cc = GetCapsuleComponent();
	return  cc->GetComponentLocation() - cc->GetUpVector() * (ZOffset + cc->GetScaledCapsuleHalfHeight());
}

FVector AALSBaseCharacter::GetCapsuleLocationFromBase(FVector baseLocation, float zOffset) {
	return  baseLocation + FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + zOffset);
}

float AALSBaseCharacter::GetAnimCurveValue(const FName curveName) {
	return 	IsValid(animInstance) ? animInstance->GetCurveValue(curveName) : 0.0f;
}

void AALSBaseCharacter::ReceiveMoveForwardBackwards(const float value) {
	CurrentForwardInput = value;
	PlayerMovementInput(true);
}

void AALSBaseCharacter::ReceiveMoveRightLeft(const float value) {
	CurrentRightInput = value;
	PlayerMovementInput(false);
}

void AALSBaseCharacter::PlayerMovementInput(const bool bIsForwardAxis) {
	if (MovementState == EALSMovementState::ALS_Grounded || MovementState == EALSMovementState::ALS_InAir) {
		const FVector2D values = FixDiagonalGamePadValues(CurrentForwardInput, CurrentRightInput);
		if (bIsForwardAxis) {
			AddMovementInput(GetControlVectors().Forward, values.Y);
		} else {
			AddMovementInput(GetControlVectors().Forward, values.X);
		}
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
	} else if (MovementState == EALSMovementState::ALS_InAir) {
		MantleCheck(FallingTraceSettings, EDrawDebugTrace::ForDuration);
	} else if (MovementState != EALSMovementState::ALS_Grounded) {
		bool bCanClimbOrVault = false;

		if (bHasMovementInput)
			bCanClimbOrVault = MantleCheck(GroundedTraceSettings, EDrawDebugTrace::ForDuration);

		if (!bCanClimbOrVault) {
			if (Stance == EALSStance::ALS_Standing) {
				Jump();
			} else {
				UnCrouch();
			}
		}
	}
}

void AALSBaseCharacter::PlayerStanceActionInput(FKey key) {
	if (MovementAction == EALSMovementAction::ALS_None) {

	}
}

FVector AALSBaseCharacter::GetPlayerMovementInput() {
	const FALSControlVectors Vectors = GetControlVectors();
	return CurrentForwardInput * Vectors.Forward + CurrentRightInput * Vectors.Right;
}

FVector2D AALSBaseCharacter::FixDiagonalGamePadValues(float inX, float inY) {
	FVector2D retvalue = FVector2D();

	retvalue.Y = UKismetMathLibrary::Clamp(inY * UKismetMathLibrary::MapRangeClamped(FMath::Abs(inX), 0.0f, 0.6f, 1.0f, 1.2f), -1.0f, 1.0f);

	retvalue.X = UKismetMathLibrary::Clamp(inX * UKismetMathLibrary::MapRangeClamped(FMath::Abs(inY), 0.0f, 0.6f, 1.0f, 1.2f), -1.0f, 1.0f);

	return retvalue;
}

void AALSBaseCharacter::SetEssentialValues() {
	//These values represent how the capsule is moving as well as how it wants to move, and therefore are essential for any data driven animation system. They are also used throughout the system for various functions, so I found it is easiest to manage them all in one place.

	//Set the amount of Acceleration.
	Acceleration = CalculateAcceleration();

	//Determine if the character is moving by getting it's speed. The Speed equals the length of the horizontal (x y) velocity, so it does not take vertical movement into account. If the character is moving, update the last velocity rotation. This value is saved because it might be useful to know the last orientation of movement even after the character has stopped.
	FVector nonZvelocity = GetVelocity();
	nonZvelocity.Z = 0.0f;
	const float speed = nonZvelocity.Size();
	bIsMoving = speed > 0;
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
			if (Stance == EALSStance::ALS_Crouching) {
				UnCrouch();
			}
		} else if (MovementAction == EALSMovementAction::ALS_Rolling) {
			RagdollStart();
		}
	} else if (MovementState == EALSMovementState::ALS_Ragdoll) {
		//Stop the Mantle Timeline if transitioning to the Ragdoll state while mantling.
		if (PrevMovementState == EALSMovementState::ALS_Mantling) {
			mantleTimeline.Stop();
		}
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
		Execute_SetViewMode(this, EALSViewMode::ALS_TPS);
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
			Execute_SetRotationMode(this, DesiredRotationMode);
	} else {
		//If First Person, set the rotation mode to looking direction if currently in the velocity direction mode.
		if (RotationMode == EALSRotationMode::ALS_VelocityDirection)
			Execute_SetRotationMode(this, EALSRotationMode::ALS_LookingDirection);
	}
}

void AALSBaseCharacter::OnOverlayStateChanged(const EALSOverlayState NewOverlayState) {
	const auto prevOverlayState = OverlayState;
	OverlayState = NewOverlayState;
}

void AALSBaseCharacter::SetMovementModel() {
	//Get movement data from the Movement Model Data table and set the Movement Data Struct. This allows you to easily switch out movement behaviors.
	MovementData = *MovementModel.DataTable->FindRow<FALSMovementSettingsState>(MovementModel.RowName, "");
}

void AALSBaseCharacter::UpdateCharacterMovement() {
	//Set the Allowed Gait
	const EALSGait allowedGait = GetAllowedGait();

	//Determine the Actual Gait. If it is different from the current Gait, Set the new Gait Event.
	const EALSGait actualGait = GetActualGait(allowedGait);
	if (Gait != actualGait)
		Execute_SetGait(this, actualGait);

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
				AddActorWorldRotation(FRotator(0.0f, curveAmount * (UGameplayStatics::GetWorldDeltaSeconds(this) / frameDeltaTime), 0.0f));
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

	UKismetSystemLibrary::CapsuleTraceSingle(this, start, end, TraceSettings.ForwardTraceRadius, halfHeight, ECC_Climbable, false, ignoredActors, DebugType, HitResult, true, FColor::Black, FColor::Black, 1.0f);

	if (!HitResult.bBlockingHit || HitResult.bStartPenetrating || GetCharacterMovement()->IsWalkable(HitResult))
		return false;

	//Step 2: Trace downward from the first trace's Impact Point and determine if the hit location is walkable.
	const FVector impactPoint = HitResult.ImpactPoint;
	const FVector impactNormal = HitResult.ImpactNormal;

	const FVector end2 = -15.0f * impactNormal + FVector(impactPoint.X, impactPoint.Y, GetCapsuleBaseLocation(2.0f).Z);
	const FVector start2 = end2 + FVector(0.0f, 0.0f, TraceSettings.MaxLedgeHeight + TraceSettings.DownwardTraceRadius + 1.0f);
	UKismetSystemLibrary::SphereTraceSingle(this, start2, end2, TraceSettings.DownwardTraceRadius, ECC_Climbable, false, ignoredActors, DebugType, HitResult, true, FColor::Orange, FColor::Red, 1.0f);

	if (!HitResult.bBlockingHit || !GetCharacterMovement()->IsWalkable(HitResult))
		return false;

	FVector DownTraceLocation = FVector(HitResult.Location.X, HitResult.Location.Y, impactPoint.Z);
	UPrimitiveComponent* HitComponent = HitResult.Component.Get();

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

	const float playRate = UKismetMathLibrary::MapRangeClamped(MantleHeight, mantleAsset.LowHeight, mantleAsset.HighHeight, mantleAsset.LowPlayRate, mantleAsset.HighPlayRate);

	const float startingPosition = UKismetMathLibrary::MapRangeClamped(MantleHeight, mantleAsset.LowHeight, mantleAsset.HighHeight, mantleAsset.LowStartPosition, mantleAsset.HighStartPosition);

	const auto mantleParams = FALSMantleParams(mantleAsset.AnimMontage, mantleAsset.PositionCorrectionCurve, startingPosition, mantleAsset.StartingOffset, playRate);

	//Step 2: Convert the world space target to the mantle component's local space for use in moving objects.
	MantleLedgeLS = ALSHelpers::WorldSpaceToLocalSpace(MantleLedgeWS);

	//Step 3: Set the Mantle Target and calculate the Starting Offset(offset amount between the actor and target transform).
	MantleTarget = MantleLedgeWS.Transform;
	MantleActualStartOffset = ALSHelpers::SubtractTransform(GetActorTransform(), MantleTarget);

	//Step 4: Calculate the Animated Start Offset from the Target Location. This would be the location the actual animation starts at relative to the Target Transform.
	const FVector tmp = MantleTarget.Rotator().Vector() * mantleParams.StartingOffset.Y;
	const FVector v = FVector(tmp.X, tmp.Y, mantleParams.StartingOffset.Z);
	MantleAnimatedStartOffset = ALSHelpers::SubtractTransform(FTransform(MantleTarget.Rotator(), MantleTarget.GetLocation() - v), MantleTarget);

	//Step 5: Clear the Character Movement Mode and set the Movement State to Mantling
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	Execute_SetMovementState(this, EALSMovementState::ALS_Mantling);

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

void AALSBaseCharacter::MantleEnd() {
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void AALSBaseCharacter::MantleUpdate(float BlendIn) {
	//Step 1: Continually update the mantle target from the stored local transform to follow along with moving objects.
	MantleTarget = ALSHelpers::LocalSpaceToWorldSpace(MantleLedgeLS).Transform;

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

bool AALSBaseCharacter::CapsuleHasRoomCheck(UCapsuleComponent* Capsule, const FVector TargetLocation, const float HeightOffset, const float RadiusOffset, const TEnumAsByte<EDrawDebugTrace::Type> DebugType) {
	const float Z =
		GetCapsuleComponent()->GetScaledCapsuleHalfHeight_WithoutHemisphere() -
		RadiusOffset +
		HeightOffset;

	FHitResult HitResult;

	UKismetSystemLibrary::SphereTraceSingleByProfile(this, TargetLocation + FVector(0.0f, 0.0f, Z), TargetLocation - FVector(0.0f, 0.0f, Z), GetCapsuleComponent()->GetUnscaledCapsuleRadius() + RadiusOffset, FName(TEXT("ALS_Character")), false, ignoredActors, DebugType, HitResult, true, FColor::FromHex(TEXT("21E525FF")), FColor::FromHex(TEXT("EE4AFFFF")), 1.0f);

	return !HitResult.bBlockingHit && !HitResult.bStartPenetrating;
}

FALSMantleAsset AALSBaseCharacter::GetMantleAsset(EALSMantleType MantleType) {
	//Get the Default Mantle Asset values.These will be overriden in the AnimMan Child Character
	if (MantleType == EALSMantleType::ALS_HighMantle)
		return FALSMantleAsset(nullptr, HighMantle, FVector(0.0f, 65.0f, 200.0f), 50.0f, 1.0f, 0.5f, 100.0f, 1.0f, 0.0f);

	if (MantleType == EALSMantleType::ALS_LowMantle)
		return FALSMantleAsset(nullptr, LowMantle, FVector(0.0f, 65.0f, 200.0f), 125.0f, 1.2f, 0.6f, 200.0f, 1.2f, 0.0f);

	return FALSMantleAsset(nullptr, LowMantle, FVector(0.0f, 65.0f, 200.0f), 125.0f, 1.2f, 0.6f, 200.0f, 1.2f, 0.0f);
}

void AALSBaseCharacter::RagdollStart() {
	//Step 1: Clear the Character Movement Mode and set the Movement State to Ragdoll
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	Execute_SetMovementState(this, EALSMovementState::ALS_Ragdoll);

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
	if (!pc->GetClass()->ImplementsInterface(UALSControllerInterface::StaticClass()) || !IALSControllerInterface::Execute_GetDebugInfo(pc).bShowDebugShapes)
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
		IALSCharacterInterface::SetMovementState_Implementation(NewMovementState);
		OnMovementStateChanged(NewMovementState);
	}
}

void AALSBaseCharacter::SetMovementAction_Implementation(EALSMovementAction NewMovementAction) {
	if (NewMovementAction != MovementAction) {
		IALSCharacterInterface::SetMovementAction_Implementation(NewMovementAction);
		OnMovementActionChanged(NewMovementAction);
	}
}

void AALSBaseCharacter::SetRotationMode_Implementation(EALSRotationMode NewRotationMode) {
	if (NewRotationMode != RotationMode) {
		IALSCharacterInterface::SetRotationMode_Implementation(NewRotationMode);
		OnRotationModeChanged(NewRotationMode);
	}
}

void AALSBaseCharacter::SetGait_Implementation(EALSGait NewGait) {
	if (NewGait != Gait) {
		IALSCharacterInterface::SetGait_Implementation(NewGait);
		OnGaitChanged(NewGait);
	}
}

void AALSBaseCharacter::SetViewMode_Implementation(EALSViewMode NewViewMode) {
	if (NewViewMode != ViewMode) {
		IALSCharacterInterface::SetViewMode_Implementation(NewViewMode);
		OnViewModeChanged(NewViewMode);
	}
}

void AALSBaseCharacter::SetOverlayState_Implementation(EALSOverlayState NewOverlayState) {
	if (NewOverlayState != OverlayState) {
		IALSCharacterInterface::SetOverlayState_Implementation(NewOverlayState);
		OnOverlayStateChanged(NewOverlayState);
	}
}

void AALSBaseCharacter::ResetBrakingFrictionTimer() {
	GetWorldTimerManager().ClearTimer(timerHandle_ResetBrakingFactor);
	GetCharacterMovement()->BrakingFrictionFactor = 0.0f;
}

void AALSBaseCharacter::ResetPressCounterTimer(uint8& counter) {

}
