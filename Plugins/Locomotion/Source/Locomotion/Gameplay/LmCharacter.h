#pragma once

#include "CoreMinimal.h"
#include "LmBaseCharacter.h"
#include "GameFramework/PlayerController.h"
#include <Materials/MaterialInstanceDynamic.h>
#include <Engine/StaticMesh.h>
#include <Animation/AnimInstance.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/SceneComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/InputComponent.h>
#include "LmCharacter.generated.h"


UCLASS()
class LOCOMOTION_API ALmCharacter : public ALmBaseCharacter {
	GENERATED_BODY()

public:
	ALmCharacter();

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		USceneComponent* HeldObjectRoot;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		USceneComponent* VisualMeshes;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		USkeletalMeshComponent* BodyMesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		ELmCharacterMeshStyle CurrentMeshType = ELmCharacterMeshStyle::Lm_Default;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		USkeletalMesh* DefaultMesh;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		USkeletalMesh* SkinMesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Holding Objects")
		USkeletalMesh* M4A1;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Holding Objects")
		USkeletalMesh* M9;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Holding Objects")
		USkeletalMesh* Bow;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Holding Objects")
		UStaticMesh* Barrel;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Holding Objects")
		UStaticMesh* Binoculars;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Holding Objects")
		UStaticMesh* Box;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Holding Objects")
		UStaticMesh* Torch;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Holding Objects")
		TSubclassOf<UAnimInstance> BowAnimInstance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling")
		bool bSolidColor = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling")
		uint8 ShirtType = 2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling")
		uint8 PantsType = 2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling")
		bool bShoes = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling")
		bool bGloves = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling|Colors")
		FLinearColor DefaultColor = FColor::FromHex("7C7CFFFF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling|Colors")
		FLinearColor SkinColor = FColor::FromHex("E5B191FF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling|Colors")
		FLinearColor ShirtColor = FColor::FromHex("668F80FF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling|Colors")
		FLinearColor PantsColor = FColor::FromHex("4A6670FF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling|Colors")
		FLinearColor ShoesColor = FColor::FromHex("C3B59FFF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling|Colors")
		FLinearColor GlovesColor = FColor::FromHex("A0AF84FF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling|Colors")
		FLinearColor BaseLayerColor = FLinearColor::White;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling|Colors")
		FLinearColor OverlayLayerColor = FLinearColor(0.027282f, 0.840056f, 1.0f);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling|Colors")
		FLinearColor AdditiveAmountColor = FLinearColor(1.0f, 0.889943f, 0.108294f);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling|Colors")
		FLinearColor HandColor = FLinearColor(0.583333f, 0.18893f, 0.115451f);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling|Colors")
		FLinearColor HandIKColor = FColor::Green;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Mantle")
		FLmMantleAsset Mantle2mDefault;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Mantle")
		FLmMantleAsset Mantle1mDefault;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Mantle")
		FLmMantleAsset Mantle1mRH;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Mantle")
		FLmMantleAsset Mantle1mLH;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Mantle")
		FLmMantleAsset Mantle1m2H;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Mantle")
		FLmMantleAsset Mantle1mBox;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Roll")
		UAnimMontage* LandRoll_Default;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Roll")
		UAnimMontage* LandRoll_RH;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Roll")
		UAnimMontage* LandRoll_LH;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Roll")
		UAnimMontage* LandRoll_2H;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|GetUp")
		UAnimMontage* GetupFront_Default;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|GetUp")
		UAnimMontage* GetupFront_RH;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|GetUp")
		UAnimMontage* GetupFront_LH;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|GetUp")
		UAnimMontage* GetupFront_2H;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|GetUp")
		UAnimMontage* GetupBack_Default;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|GetUp")
		UAnimMontage* GetupBack_RH;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|GetUp")
		UAnimMontage* GetupBack_LH;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|GetUp")
		UAnimMontage* GetupBack_2H;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Coloring")
		UMaterialInstanceDynamic* Head;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Coloring")
		UMaterialInstanceDynamic* Torso;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Coloring")
		UMaterialInstanceDynamic* Pelvis;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Coloring")
		UMaterialInstanceDynamic* Feet;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Coloring")
		UMaterialInstanceDynamic* Shoulder_L;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Coloring")
		UMaterialInstanceDynamic* UpperArm_L;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Coloring")
		UMaterialInstanceDynamic* LowerArm_L;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Coloring")
		UMaterialInstanceDynamic* Hand_L;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Coloring")
		UMaterialInstanceDynamic* Shoulder_R;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Coloring")
		UMaterialInstanceDynamic* UpperArm_R;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Coloring")
		UMaterialInstanceDynamic* LowerArm_R;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Coloring")
		UMaterialInstanceDynamic* Hand_R;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Coloring")
		UMaterialInstanceDynamic* UpperLegs;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Coloring")
		UMaterialInstanceDynamic* LowerLegs;

	UFUNCTION(BlueprintCallable, Category = "Locomotion|Coloring")
		void SetDynamicMaterials();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Coloring")
		void SetResetColors();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Coloring")
		void UpdateColoringSystem();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Coloring")
		void UpdateLayeringColors();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Held Object")
		void UpdateHeldObject();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Held Object")
		void ClearHeldObject();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Held Object")
		virtual void AttachToHand(UStaticMesh* NewStaticMesh, USkeletalMesh* NewSkeletalMesh, UClass* NewAnimClass = nullptr, bool bLeftHand = false, FVector Offset = FVector::ZeroVector);
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Held Object")
		void UpdateHeldObjectAnimations();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|State Changes")
		virtual void OnOverlayStateChanged(ELmOverlayState NewOverlayState) override;

	virtual FTransform Get3PPivotTarget_Implementation() override;
	virtual FLmTraceParams Get3PTraceParameters_Implementation() override;

	virtual UAnimMontage* GetRollAnimation() override;
	virtual FLmMantleAsset GetMantleAsset(ELmMantleType MantleType) override;
	virtual void MantleStart(float MantleHeight, FLmComponentAndTransform MantleLedgeWS, ELmMantleType MantleType) override;
	virtual void MantleEnd() override;
	virtual UAnimMontage* GetGetupAnimation(const bool bIsRagdollFacedUp) override;
	virtual void RagdollStart() override;
	virtual void RagdollEnd() override;
	virtual void ToggleCharacterMesh();
	virtual void SetCharacterMesh(ELmCharacterMeshStyle MeshType);
	virtual FLinearColor LerpColors2Level(FLinearColor L1A, FLinearColor L1B, FLinearColor L2A, FName L1Name, FName L2Name);
private:
	bool bUpdateColoringSystemDoOnceFlag;
};
