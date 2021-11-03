#include "ALSPlayerCameraBehaviour.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include "CALSv4/Core/Interfaces/ALSCameraInterface.h"
#include "CALSv4/Core/Interfaces/ALSCharacterInterface.h"
#include "CALSv4/Core/Interfaces/ALSControllerInterface.h"

UALSPlayerCameraBehaviour::UALSPlayerCameraBehaviour() {}

void UALSPlayerCameraBehaviour::NativeBeginPlay() {
	Super::NativeBeginPlay();

	MovementState = EALSMovementState::ALS_None;
	MovementAction = EALSMovementAction::ALS_None;
	RotationMode = EALSRotationMode::ALS_VelocityDirection;
	Gait = EALSGait::ALS_Walking;
	Stance = EALSStance::ALS_Standing;
	ViewMode = EALSViewMode::ALS_TPS;
}

//Get info from the character each frame to use in the camera graph.
void UALSPlayerCameraBehaviour::NativeUpdateAnimation(const float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	//Updating Character Info
	if (IsValid(controlledPawn)) {
		if (controlledPawn->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
			const auto currentState = IALSCharacterInterface::Execute_GetCurrentState(controlledPawn);
			MovementState = currentState.MovementState;
			MovementAction = currentState.MovementAction;
			RotationMode = currentState.RotationMode;
			Gait = currentState.ActualGait;
			Stance = currentState.ActualStance;
			ViewMode = currentState.ViewMode;
		}
	}

	if (IsValid(controlledPawn)) {
		if (controlledPawn->GetClass()->ImplementsInterface(UALSCameraInterface::StaticClass())) {
			bRightShoulder = IALSCameraInterface::Execute_GetCameraParameters(controlledPawn).bRightShoulder;
		}
	}

	if (IsValid(controlledPawn)) {
		if (controlledPawn->GetClass()->ImplementsInterface(UALSControllerInterface::StaticClass())) {
			bDebugView = IALSControllerInterface::Execute_GetDebugInfo(controlledPawn).bDebugView;
		}
	}
}