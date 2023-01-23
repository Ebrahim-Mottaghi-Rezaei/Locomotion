#include "LmDebugCharacter.h"
#include "LmCharacter.h"
#include "../LmLogger.h"
#include "../LmStructs.h"
#include "../Animation/LmBowAnimInstance.h"
#include "LmControllerInterface.h"
#include <UObject/Class.h>
#include <Components/CapsuleComponent.h>
#include "Kismet/GameplayStatics.h"
#include <Kismet/KismetMathLibrary.h>
#include <Animation/AnimBlueprint.h>
#include <Components/SkeletalMeshComponent.h>
#include <UObject/ConstructorHelpers.h>
#include <UObject/UObjectBase.h>

ALmDebugCharacter::ALmDebugCharacter() {
	const auto mesh = GetMesh();
	const FString DefaultMeshPath = FString(TEXT("SkeletalMesh'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/Meshes/AnimMan.AnimMan'"));
	const FString MannequinMeshPath = FString(TEXT("SkeletalMesh'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/Meshes/Mannequin.Mannequin'"));

	const ConstructorHelpers::FObjectFinder<USkeletalMesh> _defaultMesh(*DefaultMeshPath);
	if (_defaultMesh.Succeeded())
		DefaultMesh = _defaultMesh.Object;
	else
		ULmLogger::LogError("Default Mesh not found.");

	const ConstructorHelpers::FObjectFinder<USkeletalMesh> _mannequinMesh(*MannequinMeshPath);
	if (_mannequinMesh.Succeeded())
		SkinMesh = _mannequinMesh.Object;
	else
		ULmLogger::LogError("Mannequin Mesh not found.");

	mesh->SetSkeletalMesh(CurrentMeshType == ELmCharacterMeshStyle::Lm_Default ? DefaultMesh : SkinMesh);
	mesh->bUpdateJointsFromAnimation = true;
}

void ALmDebugCharacter::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

	SetDynamicMaterials();

	SetResetColors();
}

void ALmDebugCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	UpdateColoringSystem();
}

void ALmDebugCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindKey(EKeys::M, IE_Pressed, this, &ALmDebugCharacter::ToggleCharacterMesh);
}

void ALmDebugCharacter::SetDynamicMaterials() {
	const auto mesh = GetMesh();
	Pelvis = mesh->CreateDynamicMaterialInstance(0);
	Torso = mesh->CreateDynamicMaterialInstance(1);
	Head = mesh->CreateDynamicMaterialInstance(2);
	UpperArm_L = mesh->CreateDynamicMaterialInstance(3);
	Shoulder_L = mesh->CreateDynamicMaterialInstance(4);
	LowerArm_L = mesh->CreateDynamicMaterialInstance(5);
	UpperLegs = mesh->CreateDynamicMaterialInstance(6);
	LowerLegs = mesh->CreateDynamicMaterialInstance(7);
	Feet = mesh->CreateDynamicMaterialInstance(8);
	Hand_L = mesh->CreateDynamicMaterialInstance(9);
	UpperArm_R = mesh->CreateDynamicMaterialInstance(11);
	Shoulder_R = mesh->CreateDynamicMaterialInstance(12);
	LowerArm_R = mesh->CreateDynamicMaterialInstance(13);
	Hand_R = mesh->CreateDynamicMaterialInstance(14);
}

void ALmDebugCharacter::SetResetColors() {
	if (bSolidColor) {
		Head->SetVectorParameterValue(FName("BaseColor"), DefaultColor);
		Torso->SetVectorParameterValue(FName("BaseColor"), DefaultColor);
		Pelvis->SetVectorParameterValue(FName("BaseColor"), DefaultColor);
		Shoulder_L->SetVectorParameterValue(FName("BaseColor"), DefaultColor);
		UpperArm_L->SetVectorParameterValue(FName("BaseColor"), DefaultColor);
		LowerArm_L->SetVectorParameterValue(FName("BaseColor"), DefaultColor);
		Hand_L->SetVectorParameterValue(FName("BaseColor"), DefaultColor);
		Shoulder_R->SetVectorParameterValue(FName("BaseColor"), DefaultColor);
		UpperArm_R->SetVectorParameterValue(FName("BaseColor"), DefaultColor);
		LowerArm_R->SetVectorParameterValue(FName("BaseColor"), DefaultColor);
		Hand_R->SetVectorParameterValue(FName("BaseColor"), DefaultColor);
		UpperLegs->SetVectorParameterValue(FName("BaseColor"), DefaultColor);
		LowerLegs->SetVectorParameterValue(FName("BaseColor"), DefaultColor);
		Feet->SetVectorParameterValue(FName("BaseColor"), DefaultColor);
	} else {
		Head->SetVectorParameterValue(FName("BaseColor"), SkinColor);
		if (ShirtType == 0) {
			Torso->SetVectorParameterValue(FName("BaseColor"), SkinColor);
			Shoulder_L->SetVectorParameterValue(FName("BaseColor"), SkinColor);
			UpperArm_L->SetVectorParameterValue(FName("BaseColor"), SkinColor);
			LowerArm_L->SetVectorParameterValue(FName("BaseColor"), SkinColor);
			Shoulder_R->SetVectorParameterValue(FName("BaseColor"), SkinColor);
			UpperArm_R->SetVectorParameterValue(FName("BaseColor"), SkinColor);
			LowerArm_R->SetVectorParameterValue(FName("BaseColor"), SkinColor);
		} else if (ShirtType == 1) {
			Torso->SetVectorParameterValue(FName("BaseColor"), ShirtColor);
			Shoulder_L->SetVectorParameterValue(FName("BaseColor"), ShirtColor);
			Shoulder_R->SetVectorParameterValue(FName("BaseColor"), ShirtColor);
			UpperArm_L->SetVectorParameterValue(FName("BaseColor"), SkinColor);
			LowerArm_L->SetVectorParameterValue(FName("BaseColor"), SkinColor);
			UpperArm_R->SetVectorParameterValue(FName("BaseColor"), SkinColor);
			LowerArm_R->SetVectorParameterValue(FName("BaseColor"), SkinColor);
		} else if (ShirtType == 2) {
			Torso->SetVectorParameterValue(FName("BaseColor"), ShirtColor);
			Shoulder_L->SetVectorParameterValue(FName("BaseColor"), ShirtColor);
			Shoulder_R->SetVectorParameterValue(FName("BaseColor"), ShirtColor);
			UpperArm_L->SetVectorParameterValue(FName("BaseColor"), ShirtColor);
			UpperArm_R->SetVectorParameterValue(FName("BaseColor"), ShirtColor);
			LowerArm_L->SetVectorParameterValue(FName("BaseColor"), SkinColor);
			LowerArm_R->SetVectorParameterValue(FName("BaseColor"), SkinColor);
		} else if (ShirtType == 3) {
			Torso->SetVectorParameterValue(FName("BaseColor"), ShirtColor);
			Shoulder_L->SetVectorParameterValue(FName("BaseColor"), ShirtColor);
			UpperArm_L->SetVectorParameterValue(FName("BaseColor"), ShirtColor);
			LowerArm_L->SetVectorParameterValue(FName("BaseColor"), ShirtColor);
			Shoulder_R->SetVectorParameterValue(FName("BaseColor"), ShirtColor);
			UpperArm_R->SetVectorParameterValue(FName("BaseColor"), ShirtColor);
			LowerArm_R->SetVectorParameterValue(FName("BaseColor"), ShirtColor);
		}

		if (PantsType == 0) {
			Pelvis->SetVectorParameterValue(FName("BaseColor"), PantsColor);
			UpperLegs->SetVectorParameterValue(FName("BaseColor"), SkinColor);
			LowerLegs->SetVectorParameterValue(FName("BaseColor"), SkinColor);
		} else if (PantsType == 1) {
			Pelvis->SetVectorParameterValue(FName("BaseColor"), PantsColor);
			UpperLegs->SetVectorParameterValue(FName("BaseColor"), PantsColor);
			LowerLegs->SetVectorParameterValue(FName("BaseColor"), SkinColor);
		} else if (PantsType == 2) {
			Pelvis->SetVectorParameterValue(FName("BaseColor"), PantsColor);
			UpperLegs->SetVectorParameterValue(FName("BaseColor"), PantsColor);
			LowerLegs->SetVectorParameterValue(FName("BaseColor"), PantsColor);
		}

		Feet->SetVectorParameterValue(FName("BaseColor"), bShoes ? ShoesColor : SkinColor);

		Hand_L->SetVectorParameterValue(FName("BaseColor"), bGloves ? GlovesColor : SkinColor);
		Hand_R->SetVectorParameterValue(FName("BaseColor"), bGloves ? GlovesColor : SkinColor);
	}
}

void ALmDebugCharacter::UpdateColoringSystem() {
	const auto pc = UGameplayStatics::GetPlayerController(this, 0);
	if (IsValid(pc) && pc->GetClass()->ImplementsInterface(ULmControllerInterface::StaticClass())) {
		const auto debugInfo = ILmControllerInterface::Execute_GetDebugInfo(pc);
		if (debugInfo.bShowLayerColors && GetMesh()->IsVisible()) {
			bUpdateColoringSystemDoOnceFlag = true;
			UpdateLayeringColors();
		} else if (bUpdateColoringSystemDoOnceFlag) {
			bUpdateColoringSystemDoOnceFlag = false;
			SetResetColors();
		}
	}
}

void ALmDebugCharacter::UpdateLayeringColors() {

	Head->SetVectorParameterValue(FName(TEXT("BaseColor")), LerpColors2Level(OverlayLayerColor, AdditiveAmountColor, BaseLayerColor, FName("Layering_Head_Add"), FName("Layering_Head")));
	Torso->SetVectorParameterValue(FName(TEXT("BaseColor")), LerpColors2Level(OverlayLayerColor, AdditiveAmountColor, BaseLayerColor, FName("Layering_Spine_Add"), FName("Layering_Spine")));

	Pelvis->SetVectorParameterValue(FName(TEXT("BaseColor")), UKismetMathLibrary::LinearColorLerp(BaseLayerColor, AdditiveAmountColor, GetAnimCurveValue(FName("Layering_Pelvis"))));
	const auto lower_body_color = UKismetMathLibrary::LinearColorLerp(BaseLayerColor, AdditiveAmountColor, GetAnimCurveValue(FName("Layering_Legs")));
	UpperLegs->SetVectorParameterValue(FName(TEXT("BaseColor")), lower_body_color);
	LowerLegs->SetVectorParameterValue(FName(TEXT("BaseColor")), lower_body_color);
	Feet->SetVectorParameterValue(FName(TEXT("BaseColor")), lower_body_color);

	const auto upper_body_left_color = LerpColors2Level(OverlayLayerColor, AdditiveAmountColor, BaseLayerColor, FName("Layering_Arm_L_Add"), FName("Layering_Arm_L"));
	Shoulder_L->SetVectorParameterValue(FName(TEXT("BaseColor")), upper_body_left_color);
	UpperArm_L->SetVectorParameterValue(FName(TEXT("BaseColor")), upper_body_left_color);
	LowerArm_L->SetVectorParameterValue(FName(TEXT("BaseColor")), upper_body_left_color);
	Hand_L->SetVectorParameterValue(FName(TEXT("BaseColor")), LerpColors2Level2(upper_body_left_color, HandColor, HandIKColor, FName("Layering_Hand_L"), FName("Enable_HandIK_L")));

	const auto upper_body_right_color = LerpColors2Level(OverlayLayerColor, AdditiveAmountColor, BaseLayerColor, FName("Layering_Arm_R_Add"), FName("Layering_Arm_R"));
	Shoulder_R->SetVectorParameterValue(FName(TEXT("BaseColor")), upper_body_right_color);
	UpperArm_R->SetVectorParameterValue(FName(TEXT("BaseColor")), upper_body_right_color);
	LowerArm_R->SetVectorParameterValue(FName(TEXT("BaseColor")), upper_body_right_color);
	Hand_R->SetVectorParameterValue(FName(TEXT("BaseColor")), LerpColors2Level2(upper_body_right_color, HandColor, HandIKColor, FName("Layering_Hand_R"), FName("Enable_HandIK_R")));
}

void ALmDebugCharacter::SetRoleColors(const FLmRoleSkinColors SkinColors) {
	ShirtType = SkinColors.ShirtType;
	PantsType = SkinColors.PantsType;
	bGloves = SkinColors.UseGloves;
	bShoes = SkinColors.UseShoes;

	SkinColor = SkinColors.Skin;
	ShirtColor = SkinColors.Shirt;
	PantsColor = SkinColors.Pants;
	GlovesColor = SkinColors.Gloves;
	ShoesColor = SkinColors.Shoes;

	SetResetColors();
}

void ALmDebugCharacter::ToggleCharacterMesh() {
	SetCharacterMesh(CurrentMeshType == ELmCharacterMeshStyle::Lm_Default ? ELmCharacterMeshStyle::Lm_Skin : ELmCharacterMeshStyle::Lm_Default);
}

void ALmDebugCharacter::SetCharacterMesh(ELmCharacterMeshStyle MeshType) {
	if (MovementState == ELmMovementState::Lm_Ragdoll || CurrentMeshType == MeshType)
		return;

	const auto tmpMaterials = GetMesh()->GetMaterials();
	const auto CurMatNum = GetMesh()->GetNumMaterials();
	for (int i = 0; i < CurMatNum; i++)
		GetMesh()->SetMaterial(i, nullptr);

	TArray<UMaterialInterface*> newMaterials;

	if (LastSkinMaterials.Num() > 0) {
		newMaterials = LastSkinMaterials;
	} else {
		const auto& tmp = (MeshType == ELmCharacterMeshStyle::Lm_Default ? DefaultMesh : SkinMesh)->GetMaterials();
		for (auto& t : tmp) {
			newMaterials.Add(t.MaterialInterface);
		}
	}

	for (int i = 0; i < newMaterials.Num(); i++)
		GetMesh()->SetMaterial(i, newMaterials[i]);

	LastSkinMaterials = tmpMaterials;

	GetMesh()->SetSkeletalMesh(MeshType == ELmCharacterMeshStyle::Lm_Default ? DefaultMesh : SkinMesh);
	CurrentMeshType = MeshType;
}

FLinearColor ALmDebugCharacter::LerpColors2Level(const FLinearColor L1A, const FLinearColor L1B, const FLinearColor L2A, const FName L1Name, const FName L2Name) {
	const float alpha1 = GetAnimCurveValue(L1Name);
	const float alpha2 = GetAnimCurveValue(L2Name);

	const auto l2_b = UKismetMathLibrary::LinearColorLerp(L1A, L1B, alpha1);
	return UKismetMathLibrary::LinearColorLerp(L2A, l2_b, alpha2);
}

FLinearColor ALmDebugCharacter::LerpColors2Level2(const FLinearColor L1A, const FLinearColor L1B, const FLinearColor L2B, const FName L1Name, const FName L2Name) {
	const float alpha1 = GetAnimCurveValue(L1Name);
	const float alpha2 = GetAnimCurveValue(L2Name);

	const auto l2_a = UKismetMathLibrary::LinearColorLerp(L1A, L1B, alpha1);
	return UKismetMathLibrary::LinearColorLerp(l2_a, L2B, alpha2);
}