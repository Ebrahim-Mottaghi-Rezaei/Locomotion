#include "LmHoldingObject.h"

// Sets default values
ALmHoldingObject::ALmHoldingObject() {
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root")));
	Root->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Root->SetComponentTickEnabled(false);
}

void ALmHoldingObject::SetHoldingActor_Implementation(AActor* holdingActor) {
	HoldingActor = holdingActor;
}