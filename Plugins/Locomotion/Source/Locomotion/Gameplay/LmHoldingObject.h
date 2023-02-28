#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "LmHoldingObjectInterface.h"
#include "LmHoldingObject.generated.h"

UCLASS()
class LOCOMOTION_API ALmHoldingObject : public AActor, public ILmHoldingObjectInterface {
	GENERATED_BODY()

public:
	ALmHoldingObject();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Locomotion")
		USceneComponent* Root;

	void SetHoldingActor_Implementation(AActor* holdingActor) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category="Locomotion|HoldingObjects")
		AActor* HoldingActor;
};
