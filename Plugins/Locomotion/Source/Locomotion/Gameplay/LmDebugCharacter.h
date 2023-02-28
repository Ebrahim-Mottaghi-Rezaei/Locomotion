#pragma once

#include "CoreMinimal.h"
#include "LmCharacter.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "LmDebugCharacter.generated.h"


UCLASS()
class LOCOMOTION_API ALmDebugCharacter : public ALmCharacter {
	GENERATED_BODY()

public:
	ALmDebugCharacter();

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Styling")
		ELmCharacterMeshStyle CurrentMeshType = ELmCharacterMeshStyle::Lm_Default;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Styling")
		USkeletalMesh* DefaultMesh;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Styling")
		USkeletalMesh* SkinMesh;
	
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
		FLinearColor BaseLayerColor = FLinearColor::Black;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling|Colors")
		FLinearColor OverlayLayerColor = FLinearColor::White;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling|Colors")
		FLinearColor AdditiveAmountColor = FLinearColor::Red;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling|Colors")
		FLinearColor HandColor = FColor::FromHex(TEXT("00D5FFFF"));
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion|Styling|Colors")
		FLinearColor HandIKColor = FColor::Green;

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
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Coloring")
		virtual void SetRoleColors(const FLmRoleSkinColors SkinColors);
	
	virtual void ToggleCharacterMesh();
	virtual void SetCharacterMesh(ELmCharacterMeshStyle MeshType);
	virtual FLinearColor LerpColors2Level(const FLinearColor L1A, const  FLinearColor L1B, const  FLinearColor L2A, const  FName L1Name, const  FName L2Name);
	virtual FLinearColor LerpColors2Level2(const FLinearColor L1A, const FLinearColor L1B, const FLinearColor L2B, const FName L1Name, const FName L2Name);
private:
	bool bUpdateColoringSystemDoOnceFlag;
	TArray<UMaterialInterface*> LastSkinMaterials;
};