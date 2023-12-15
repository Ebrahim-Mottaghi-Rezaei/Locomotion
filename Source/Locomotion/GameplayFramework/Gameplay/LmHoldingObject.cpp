#include "LmHoldingObject.h"

// Sets default values
ALmHoldingObject::ALmHoldingObject() {
	PrimaryActorTick.bCanEverTick          = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Root = CreateDefaultSubobject<USceneComponent>( FName( TEXT( "Root" ) ) );

	Root->AttachToComponent( RootComponent , FAttachmentTransformRules::KeepRelativeTransform );
	Root->SetComponentTickEnabled( false );
	RootComponent = Root;
}


void ALmHoldingObject::SetHoldingActor_Implementation(AActor* holdingActor) {
	HoldingActor = holdingActor;
}
