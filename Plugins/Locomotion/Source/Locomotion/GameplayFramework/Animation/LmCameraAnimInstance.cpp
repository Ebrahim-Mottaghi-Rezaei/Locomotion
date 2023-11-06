#include "LmCameraAnimInstance.h"
#include "Locomotion/DataTypes/LmStructs.h"
#include "Locomotion/GameplayFramework/Camera/Interfaces/LmCameraInterface.h"
#include "Locomotion/GameplayFramework/Character/Interfaces/LmCharacterInterface.h"
#include "Locomotion/GameplayFramework/Character/Interfaces/LmControllerInterface.h"

//Get info from the character each frame to use in the camera graph.
void ULmCameraAnimInstance::NativeUpdateAnimation(const float DeltaSeconds) {
	Super::NativeUpdateAnimation( DeltaSeconds );

	//Updating Character Info
	if ( IsValid( ControlledPawn ) ) {
		if ( ControlledPawn->GetClass()->ImplementsInterface( ULmCharacterInterface::StaticClass() ) ) {
			const auto CurrentState = ILmCharacterInterface::Execute_GetCurrentState( ControlledPawn );
			MovementState           = CurrentState.MovementState;
			MovementAction          = CurrentState.MovementAction;
			RotationMode            = CurrentState.RotationMode;
			Gait                    = CurrentState.ActualGait;
			Stance                  = CurrentState.ActualStance;
			ViewMode                = CurrentState.ViewMode;
		}

		if ( ControlledPawn->GetClass()->ImplementsInterface( ULmCameraInterface::StaticClass() ) ) {
			bRightShoulder = ILmCameraInterface::Execute_GetCameraParameters( ControlledPawn ).bRightShoulder;
		}
	}

	if ( PlayerController && PlayerController->GetClass()->ImplementsInterface( ULmControllerInterface::StaticClass() ) ) {
		bDebugView = ILmControllerInterface::Execute_GetDebugInfo( PlayerController ).bDebugView;
	}
}


void ULmCameraAnimInstance::SetControlledPawn(APawn* Pawn) {
	ControlledPawn = Pawn;
}


void ULmCameraAnimInstance::SetPlayerController(APlayerController* Controller) {
	PlayerController = Controller;
}
