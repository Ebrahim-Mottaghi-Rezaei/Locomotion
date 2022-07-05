#include "LmCameraAnimInstance.h"
#include "../Gameplay/LmCharacterInterface.h"
#include "../Gameplay/LmCameraInterface.h"
#include "../Gameplay/LmControllerInterface.h"

//Get info from the character each frame to use in the camera graph.
void ULmCameraAnimInstance::NativeUpdateAnimation(const float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	//Updating Character Info
	if (IsValid(controlledPawn)) {
		//TODO optimizing these variable checking by implementing proper events in the possessed pawn. in this case Controlled Pawn

		if (controlledPawn->GetClass()->ImplementsInterface(ULmCharacterInterface::StaticClass())) {
			const auto currentState = ILmCharacterInterface::Execute_GetCurrentState(controlledPawn);
			MovementState = currentState.MovementState;
			MovementAction = currentState.MovementAction;
			RotationMode = currentState.RotationMode;
			Gait = currentState.ActualGait;
			Stance = currentState.ActualStance;
			ViewMode = currentState.ViewMode;
		}

		if (controlledPawn->GetClass()->ImplementsInterface(ULmCameraInterface::StaticClass())) {
			bRightShoulder = ILmCameraInterface::Execute_GetCameraParameters(controlledPawn).bRightShoulder;
		}
	}

	if (playerController && playerController->GetClass()->ImplementsInterface(ULmControllerInterface::StaticClass())) {
		bDebugView = ILmControllerInterface::Execute_GetDebugInfo(playerController).bDebugView;
	}
}