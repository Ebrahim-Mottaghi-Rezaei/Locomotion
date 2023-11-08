#include "LmCameraAnimInstance.h"
#include "Locomotion/DataTypes/LmStructs.h"
#include "Locomotion/GameplayFramework/Character/LmCharacter.h"
#include "Locomotion/GameplayFramework/Character/LmPlayerController.h"


void ULmCameraAnimInstance::SetControlledPawn(APawn* Pawn) {
	const auto LmCharacter = Cast<ALmCharacter>( Pawn );
	if ( !IsValid( LmCharacter ) )
		return;

	LmCharacter->OnGaitChanged.AddDynamic( this , &ULmCameraAnimInstance::OnGaitChanged );
	LmCharacter->OnMovementStateChanged.AddDynamic( this , &ULmCameraAnimInstance::OnMovementStateChanged );
	LmCharacter->OnMovementActionChanged.AddDynamic( this , &ULmCameraAnimInstance::OnMovementActionChanged );
	LmCharacter->OnStanceChanged.AddDynamic( this , &ULmCameraAnimInstance::OnStanceChanged );
	LmCharacter->OnRotationModeChanged.AddDynamic( this , &ULmCameraAnimInstance::OnRotationModeChanged );
	LmCharacter->OnViewModeChanged.AddDynamic( this , &ULmCameraAnimInstance::OnViewModeChanged );
	LmCharacter->OnCameraShoulderChanged.AddDynamic( this , &ULmCameraAnimInstance::OnCameraShoulderChanged );
}


void ULmCameraAnimInstance::SetPlayerController(APlayerController* Controller) {
	if ( !IsValid( Controller ) )
		return;

	const auto LmController = Cast<ALmPlayerController>( Controller );
	if ( !IsValid( LmController ) )
		return;

	LmController->OnDebugViewChanged.AddDynamic( this , &ULmCameraAnimInstance::OnDebugViewChanged );
}


void ULmCameraAnimInstance::OnGaitChanged(const ELmGait NewGait) {
	Gait = NewGait;
}


void ULmCameraAnimInstance::OnMovementStateChanged(const ELmMovementState NewMovementState) {
	MovementState = NewMovementState;
}


void ULmCameraAnimInstance::OnMovementActionChanged(const ELmMovementAction NewMovementAction) {
	MovementAction = NewMovementAction;
}


void ULmCameraAnimInstance::OnStanceChanged(const ELmStance NewStance) {
	Stance = NewStance;
}


void ULmCameraAnimInstance::OnRotationModeChanged(const ELmRotationMode NewRotationMode) {
	RotationMode = NewRotationMode;
}


void ULmCameraAnimInstance::OnViewModeChanged(const ELmViewMode NewViewMode) {
	ViewMode = NewViewMode;
}


void ULmCameraAnimInstance::OnCameraShoulderChanged(const bool bRight) {
	bRightShoulder = bRight;
}


void ULmCameraAnimInstance::OnDebugViewChanged(const bool bNewDebugView) {
	bDebugView = bNewDebugView;
}
