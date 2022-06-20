

#pragma once

#include "CoreMinimal.h"
#include "ALSBaseCharacter.h"
#include "GameFramework/PlayerController.h"
#include "ALSCharacter.generated.h"


UCLASS()
class CALSV4_API AALSCharacter : public AALSBaseCharacter {
	GENERATED_BODY()

public:
	AALSCharacter();

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character")
		USceneComponent* HeldObjectRoot;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character")
		USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character")
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character")
		USceneComponent* VisualMeshes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character")
		USkeletalMeshComponent* BodyMesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Character")
		EALSMannequinMeshType CharacterModelType = EALSMannequinMeshType::ALS_Default;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Character")
		USkeletalMesh* DefaultMesh;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Character")
		USkeletalMesh* MannequinMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Holding Objects")
		USkeletalMesh* M4A1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Holding Objects")
		USkeletalMesh* M9;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Holding Objects")
		USkeletalMesh* Bow;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Holding Objects")
		UStaticMesh* Barrel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Holding Objects")
		UStaticMesh* Binoculars;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Holding Objects")
		UStaticMesh* Box;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Holding Objects")
		UStaticMesh* Torch;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Holding Objects")
		TSubclassOf<UAnimInstance> BowAnimInstance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Coloring System")
		bool bSolidColor = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Coloring System")
		uint8 ShirtType = 2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Coloring System")
		uint8 PantsType = 2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Coloring System")
		bool bShoes = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Coloring System")
		bool bGloves = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Coloring System|Colors")
		FLinearColor DefaultColor = FColor::FromHex("7C7CFFFF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Coloring System|Colors")
		FLinearColor SkinColor = FColor::FromHex("E2A589FF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Coloring System|Colors")
		FLinearColor ShirtColor = FColor::FromHex("C6A5E1FF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Coloring System|Colors")
		FLinearColor PantsColor = FColor::FromHex("7F330CFF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Coloring System|Colors")
		FLinearColor ShoesColor = FColor::FromHex("E1E1E1FF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Coloring System|Colors")
		FLinearColor GlovesColor = FColor::FromHex("2C2C2CFF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Coloring System|Colors")
		FLinearColor BaseLayerColor = FColor::Black;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Coloring System|Colors")
		FLinearColor OverlayLayerColor = FColor::White;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Coloring System|Colors")
		FLinearColor AdditiveAmountColor = FColor::Red;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Coloring System|Colors")
		FLinearColor HandColor = FColor::FromHex("00AAFFFF");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Coloring System|Colors")
		FLinearColor HandIKColor = FColor::Green;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Mantle Animations")
		FALSMantleAsset Mantle2mDefault;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Mantle Animations")
		FALSMantleAsset Mantle1mDefault;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Mantle Animations")
		FALSMantleAsset Mantle1mRH;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Mantle Animations")
		FALSMantleAsset Mantle1mLH;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Mantle Animations")
		FALSMantleAsset Mantle1m2H;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Mantle Animations")
		FALSMantleAsset Mantle1mBox;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Roll Animations")
		UAnimMontage* LandRoll_Default;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Roll Animations")
		UAnimMontage* LandRoll_RH;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Roll Animations")
		UAnimMontage* LandRoll_LH;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|Roll Animations")
		UAnimMontage* LandRoll_2H;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|GetUp Animations")
		UAnimMontage* GetupFront_Default;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|GetUp Animations")
		UAnimMontage* GetupFront_RH;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|GetUp Animations")
		UAnimMontage* GetupFront_LH;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|GetUp Animations")
		UAnimMontage* GetupFront_2H;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|GetUp Animations")
		UAnimMontage* GetupBack_Default;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|GetUp Animations")
		UAnimMontage* GetupBack_RH;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|GetUp Animations")
		UAnimMontage* GetupBack_LH;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Character|GetUp Animations")
		UAnimMontage* GetupBack_2H;

	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Character|Coloring System")
		UMaterialInstanceDynamic* Head;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Character|Coloring System")
		UMaterialInstanceDynamic* Torso;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Character|Coloring System")
		UMaterialInstanceDynamic* Pelvis;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Character|Coloring System")
		UMaterialInstanceDynamic* Feet;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Character|Coloring System")
		UMaterialInstanceDynamic* Shoulder_L;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Character|Coloring System")
		UMaterialInstanceDynamic* UpperArm_L;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Character|Coloring System")
		UMaterialInstanceDynamic* LowerArm_L;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Character|Coloring System")
		UMaterialInstanceDynamic* Hand_L;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Character|Coloring System")
		UMaterialInstanceDynamic* Shoulder_R;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Character|Coloring System")
		UMaterialInstanceDynamic* UpperArm_R;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Character|Coloring System")
		UMaterialInstanceDynamic* LowerArm_R;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Character|Coloring System")
		UMaterialInstanceDynamic* Hand_R;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Character|Coloring System")
		UMaterialInstanceDynamic* UpperLegs;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Character|Coloring System")
		UMaterialInstanceDynamic* LowerLegs;

	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character|Coloring System")
		void SetDynamicMaterials();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character|Coloring System")
		void SetResetColors();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character|Coloring System")
		void UpdateColoringSystem();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character|Coloring System")
		void UpdateLayeringColors();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character|Held Object")
		void UpdateHeldObject();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character|Held Object")
		void ClearHeldObject();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character|Held Object")
		virtual void AttachToHand(UStaticMesh* NewStaticMesh, USkeletalMesh* NewSkeletalMesh, UClass* NewAnimClass = nullptr, bool bLeftHand = false, FVector Offset = FVector::ZeroVector);
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character|Held Object")
		void UpdateHeldObjectAnimations();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character|State Changes")
		virtual void OnOverlayStateChanged(EALSOverlayState NewOverlayState) override;

	virtual FTransform Get3PPivotTarget_Implementation() override;
	virtual FALSTraceParams Get3PTraceParameters_Implementation() override;

	virtual UAnimMontage* GetRollAnimation() override;
	virtual FALSMantleAsset GetMantleAsset(EALSMantleType MantleType) override;
	virtual void MantleStart(float MantleHeight, FALSComponentAndTransform MantleLedgeWS, EALSMantleType MantleType) override;
	virtual void MantleEnd() override;
	virtual UAnimMontage* GetGetupAnimation(const bool bIsRagdollFacedUp) override;
	virtual void RagdollStart() override;
	virtual void RagdollEnd() override;
	virtual void ToggleCharacterMesh();
	virtual void ChangeMannequinMeshTo(EALSMannequinMeshType MeshType);
	virtual FLinearColor LerpColors2Level(FLinearColor L1A, FLinearColor L1B, FLinearColor L2A, FName L1Name, FName L2Name);
private:
	bool bUpdateColoringSystemDoOnceFlag;
};
