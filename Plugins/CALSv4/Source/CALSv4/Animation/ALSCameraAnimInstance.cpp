


#include "ALSCameraAnimInstance.h"
#include "../Gameplay/ALSCharacterInterface.h"
#include "../Gameplay/ALSCameraInterface.h"
#include "../Gameplay/ALSControllerInterface.h"

//Get info from the character each frame to use in the camera graph.
void UALSCameraAnimInstance::NativeUpdateAnimation(const float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	//Updating Character Info
	if (IsValid(controlledPawn)) {
		//TODO optimizing these variable checking by implementing proper events in the possessed pawn. in this case Controlled Pawn

		if (controlledPawn->GetClass()->ImplementsInterface(UALSCharacterInterface::StaticClass())) {
			const auto currentState = IALSCharacterInterface::Execute_GetCurrentState(controlledPawn);
			MovementState = currentState.MovementState;
			MovementAction = currentState.MovementAction;
			RotationMode = currentState.RotationMode;
			Gait = currentState.ActualGait;
			Stance = currentState.ActualStance;
			ViewMode = currentState.ViewMode;
		}

		if (controlledPawn->GetClass()->ImplementsInterface(UALSCameraInterface::StaticClass())) {
			bRightShoulder = IALSCameraInterface::Execute_GetCameraParameters(controlledPawn).bRightShoulder;
		}
	}

	if (playerController && playerController->GetClass()->ImplementsInterface(UALSControllerInterface::StaticClass())) {
		bDebugView = IALSControllerInterface::Execute_GetDebugInfo(playerController).bDebugView;
	}
}