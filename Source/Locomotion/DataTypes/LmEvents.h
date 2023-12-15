// // Copyright Ebrahim Mottaghi Rezaei. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "LmEnums.h"
#include "UObject/Object.h"
#include "LmEvents.generated.h"

UCLASS( Hidden , HideDropdown )
class LOCOMOTION_API ULmDummy : public UObject {
	GENERATED_BODY()
};

//~ LmCharacter
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FGaitChangedDelegate , const ELmGait , NewGait );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FMovementActionChangedDelegate , const ELmMovementAction , NewMovementAction );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FMovementStateChangedDelegate , const ELmMovementState , NewMovementState );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOverlayStateChangedDelegate , const ELmOverlayState , NewOverlayState );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FStanceChangedDelegate , const ELmStance , NewStance );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FViewModeChangedDelegate , const ELmViewMode , NewViewMode );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FGroundedEntryStateChangedDelegate , const ELmGroundedEntryState , NewGroundedState );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FRotationModeChangedDelegate , const ELmRotationMode , NewRotationMode );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FUsingHandChangedDelegate , const ELmUsingHand , NewUsingHand );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FCameraShoulderChangedDelegate , const bool , bRight );

//~ LmCharacter

//~ LmController
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FDebugViewChangedDelegate , const bool , NewDebugView );

//~ LmController
