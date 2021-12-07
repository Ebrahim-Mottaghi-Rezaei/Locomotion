#include "ALSCharacter.h"

#include "ClothingSimulationFactoryNv.h"
#include "CALSv4/Core/Animation/ALSBowAnimInstance.h"
#include "CALSv4/Core/Interfaces/ALSControllerInterface.h"
#include "CALSv4/Core/Utilities/ALSHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Curves/CurveVector.h"

AALSCharacter::AALSCharacter() {
	const auto mesh = GetMesh();
	const FString DefaultMeshPath = FString(TEXT("SkeletalMesh'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/Meshes/AnimMan.AnimMan'"));
	const FString MannequinMeshPath = FString(TEXT("SkeletalMesh'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/Meshes/Mannequin.Mannequin'"));

	const ConstructorHelpers::FObjectFinder<USkeletalMesh> _defaultMesh(*DefaultMeshPath);
	if (_defaultMesh.Succeeded())
		DefaultMesh = _defaultMesh.Object;
	else
		UALSLogger::LogError("Default Mesh not found.");

	const ConstructorHelpers::FObjectFinder<USkeletalMesh> _mannequinMesh(*MannequinMeshPath);
	if (_mannequinMesh.Succeeded())
		MannequinMesh = _mannequinMesh.Object;
	else
		UALSLogger::LogError("Mannequin Mesh not found.");

#pragma region Setting Up Holding Objects
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> M4A1Mesh(TEXT("SkeletalMesh'/Game/AdvancedLocomotionV4/Props/Meshes/M4A1.M4A1'"));
	if (M4A1Mesh.Succeeded())
		M4A1 = M4A1Mesh.Object;
	else
		UALSLogger::LogError("M4A1 not found.");

	const ConstructorHelpers::FObjectFinder<USkeletalMesh> M9Mesh(TEXT("SkeletalMesh'/Game/AdvancedLocomotionV4/Props/Meshes/M9.M9'"));
	if (M9Mesh.Succeeded())
		M9 = M9Mesh.Object;
	else
		UALSLogger::LogError("M9 not found.");

	const ConstructorHelpers::FObjectFinder<USkeletalMesh> BowMesh(TEXT("SkeletalMesh'/Game/AdvancedLocomotionV4/Props/Meshes/Bow.Bow'"));
	if (BowMesh.Succeeded())
		Bow = BowMesh.Object;
	else
		UALSLogger::LogError("Bow not found.");

	const ConstructorHelpers::FObjectFinder<UStaticMesh> BarrelMesh(TEXT("StaticMesh'/Game/AdvancedLocomotionV4/Props/Meshes/Barrel.Barrel'"));
	if (BarrelMesh.Succeeded())
		Barrel = BarrelMesh.Object;
	else
		UALSLogger::LogError("Barrel not found.");

	const ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMesh(TEXT("StaticMesh'/Game/AdvancedLocomotionV4/Props/Meshes/Box.Box'"));
	if (BoxMesh.Succeeded())
		Box = BoxMesh.Object;
	else
		UALSLogger::LogError("Box not found.");

	const ConstructorHelpers::FObjectFinder<UStaticMesh> TorchMesh(TEXT("StaticMesh'/Game/AdvancedLocomotionV4/Props/Meshes/Torch.Torch'"));
	if (TorchMesh.Succeeded())
		Torch = TorchMesh.Object;
	else
		UALSLogger::LogError("Torch not found.");

	const ConstructorHelpers::FObjectFinder<UStaticMesh> BinocularsMesh(TEXT("StaticMesh'/Game/AdvancedLocomotionV4/Props/Meshes/Binoculars.Binoculars'"));
	if (BinocularsMesh.Succeeded())
		Binoculars = BinocularsMesh.Object;
	else
		UALSLogger::LogError("Binoculars not found.");
#pragma endregion

	HeldObjectRoot = CreateDefaultSubobject<USceneComponent>(FName("HeldObjectRoot"));
	HeldObjectRoot->AttachToComponent(mesh, FAttachmentTransformRules::KeepRelativeTransform);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("SkeletalMesh"));
	SkeletalMesh->AttachToComponent(HeldObjectRoot, FAttachmentTransformRules::KeepRelativeTransform);
	SkeletalMesh->ClothingSimulationFactory = UClothingSimulationFactoryNv::StaticClass();
	SkeletalMesh->SetCollisionProfileName(FName("NoCollision"));

	SkeletalMesh->SetVisibility(false, true);
	SkeletalMesh->SetSkeletalMesh(Bow);
	const ConstructorHelpers::FObjectFinder<UAnimBlueprint> BowAnimBP(TEXT("AnimBlueprint'/CALSv4/CharacterLogic/Animation/BP_ALSBowAnimInstance.BP_ALSBowAnimInstance'"));
	if (BowAnimBP.Succeeded())
		SkeletalMesh->SetAnimInstanceClass(BowAnimBP.Object->GetAnimBlueprintGeneratedClass());
	else
		UALSLogger::LogError("BowAnimInstance not found.");

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMesh->AttachToComponent(HeldObjectRoot, FAttachmentTransformRules::KeepRelativeTransform);
	StaticMesh->SetCollisionProfileName(FName("ALS_Prop"));

	VisualMeshes = CreateDefaultSubobject<USceneComponent>(FName("VisualMeshes"));
	VisualMeshes->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);

	BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("BodyMesh"));
	BodyMesh->AttachToComponent(VisualMeshes, FAttachmentTransformRules::KeepRelativeTransform);
	BodyMesh->ClothingSimulationFactory = UClothingSimulationFactoryNv::StaticClass();
	BodyMesh->SetCollisionProfileName(FName("NoCollision"));

	const auto capsule = GetCapsuleComponent();
	capsule->SetCapsuleRadius(35.0f);

	const ConstructorHelpers::FObjectFinder<USkeletalMesh> defaultCharacterMesh(TEXT("SkeletalMesh'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/Meshes/AnimMan.AnimMan'"));
	if (defaultCharacterMesh.Succeeded())
		mesh->SetSkeletalMesh(defaultCharacterMesh.Object);
	else
		UALSLogger::LogError("AnimMan not found.");
	mesh->bUpdateJointsFromAnimation = true;

	const ConstructorHelpers::FObjectFinder<UAnimBlueprint> ALSCharacterAnimBP(TEXT("AnimBlueprint'/CALSv4/CharacterLogic/Animation/BP_ALSAnimInstance.BP_ALSAnimInstance'"));
	if (ALSCharacterAnimBP.Succeeded()) {
		mesh->SetAnimInstanceClass(ALSCharacterAnimBP.Object->GetAnimBlueprintGeneratedClass());
	} else
		UALSLogger::LogError("BP_AnimInstance not found.");

#pragma region Setting up Mantles
	//Mantle 2m Default
	Mantle2mDefault.StartingOffset = FVector(0.0f, 65.0f, 200.0f);
	Mantle2mDefault.LowHeight = 1250.0f;
	Mantle2mDefault.LowPlayRate = 1.2f;
	Mantle2mDefault.LowStartPosition = 0.6f;
	Mantle2mDefault.HighHeight = 200.0f;
	Mantle2mDefault.HighPlayRate = 1.2f;
	Mantle2mDefault.HighStartPosition = 0.0f;
	const ConstructorHelpers::FObjectFinder<UAnimMontage> Montage2m(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_N_Mantle_2m_Montage_Default.ALS_N_Mantle_2m_Montage_Default'"));
	if (Montage2m.Succeeded())
		Mantle2mDefault.AnimMontage = Montage2m.Object;
	else
		UALSLogger::LogError("ALS_N_Mantle_2m_Montage_Default not found.");
	const ConstructorHelpers::FObjectFinder<UCurveVector> Curve2m(TEXT("CurveVector'/Game/AdvancedLocomotionV4/Data/Curves/MantleCurves/Mantle_2m.Mantle_2m'"));
	if (Curve2m.Succeeded())
		Mantle2mDefault.PositionCorrectionCurve = Curve2m.Object;
	else
		UALSLogger::LogError("Curve Mantle_2m not found.");

	//Mantle 1m Default
	Mantle1mDefault.StartingOffset = FVector(0.0f, 65.0f, 100.0f);
	Mantle1mDefault.LowHeight = 50.0f;
	Mantle1mDefault.LowPlayRate = 1.0f;
	Mantle1mDefault.LowStartPosition = 0.5f;
	Mantle1mDefault.HighHeight = 100.0;
	Mantle1mDefault.HighPlayRate = 1.0f;
	Mantle1mDefault.HighStartPosition = 0.0f;
	const ConstructorHelpers::FObjectFinder<UAnimMontage> Montage1m(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_N_Mantle_1m_Montage_Default.ALS_N_Mantle_1m_Montage_Default'"));
	if (Montage1m.Succeeded())
		Mantle1mDefault.AnimMontage = Montage1m.Object;
	else
		UALSLogger::LogError("ALS_N_Mantle_1m_Montage_Default not found.");

	//Mantle 1m RH
	Mantle1mRH.StartingOffset = FVector(0.0f, 65.0f, 100.0f);
	Mantle1mRH.LowHeight = 50.0f;
	Mantle1mRH.LowPlayRate = 1.0f;
	Mantle1mRH.LowStartPosition = 0.5f;
	Mantle1mRH.HighHeight = 100.0;
	Mantle1mRH.HighPlayRate = 1.0f;
	Mantle1mRH.HighStartPosition = 0.0f;
	const ConstructorHelpers::FObjectFinder<UAnimMontage> Montage1mRH(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_N_Mantle_1m_Montage_RH.ALS_N_Mantle_1m_Montage_RH'"));
	if (Montage1mRH.Succeeded())
		Mantle1mRH.AnimMontage = Montage1mRH.Object;
	else
		UALSLogger::LogError("ALS_N_Mantle_1m_Montage_RH not found.");


	//Mantle 1m LH
	Mantle1mLH.StartingOffset = FVector(0.0f, 65.0f, 100.0f);
	Mantle1mLH.LowHeight = 50.0f;
	Mantle1mLH.LowPlayRate = 1.0f;
	Mantle1mLH.LowStartPosition = 0.5f;
	Mantle1mLH.HighHeight = 100.0;
	Mantle1mLH.HighPlayRate = 1.0f;
	Mantle1mLH.HighStartPosition = 0.0f;
	const ConstructorHelpers::FObjectFinder<UAnimMontage> Montage1mLH(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_N_Mantle_1m_Montage_LH.ALS_N_Mantle_1m_Montage_LH'"));
	if (Montage1mLH.Succeeded())
		Mantle1mLH.AnimMontage = Montage1mLH.Object;
	else
		UALSLogger::LogError("ALS_N_Mantle_1m_Montage_LH not found.");

	//Mantle 1m 2H
	Mantle1m2H.StartingOffset = FVector(0.0f, 65.0f, 100.0f);
	Mantle1m2H.LowHeight = 50.0f;
	Mantle1m2H.LowPlayRate = 1.0f;
	Mantle1m2H.LowStartPosition = 0.5f;
	Mantle1m2H.HighHeight = 100.0;
	Mantle1m2H.HighPlayRate = 1.0f;
	Mantle1m2H.HighStartPosition = 0.0f;
	const ConstructorHelpers::FObjectFinder<UAnimMontage> Montage2H(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_N_Mantle_1m_Montage_2H.ALS_N_Mantle_1m_Montage_2H'"));
	if (Montage2H.Succeeded())
		Mantle1m2H.AnimMontage = Montage2H.Object;
	else
		UALSLogger::LogError("ALS_N_Mantle_1m_Montage_2H not found.");

	//Mantle 1m Box
	Mantle1mBox.StartingOffset = FVector(0.0f, 65.0f, 100.0f);
	Mantle1mBox.LowHeight = 50.0f;
	Mantle1mBox.LowPlayRate = 1.0f;
	Mantle1mBox.LowStartPosition = 0.5f;
	Mantle1mBox.HighHeight = 100.0;
	Mantle1mBox.HighPlayRate = 1.0f;
	Mantle1mBox.HighStartPosition = 0.0f;
	const ConstructorHelpers::FObjectFinder<UAnimMontage> Montage1mBox(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_N_Mantle_1m_Montage_Box.ALS_N_Mantle_1m_Montage_Box'"));
	if (Montage1mBox.Succeeded())
		Mantle1mBox.AnimMontage = Montage1mBox.Object;
	else
		UALSLogger::LogError("ALS_N_Mantle_1m_Montage_Box not found.");

	//Setting up 1m Mantle Curve
	const ConstructorHelpers::FObjectFinder<UCurveVector> Curve1m(TEXT("CurveVector'/Game/AdvancedLocomotionV4/Data/Curves/MantleCurves/Mantle_1m.Mantle_1m'"));
	if (Curve1m.Succeeded()) {
		Mantle1mDefault.PositionCorrectionCurve = Curve1m.Object;
		Mantle1mRH.PositionCorrectionCurve = Curve1m.Object;
		Mantle1mLH.PositionCorrectionCurve = Curve1m.Object;
		Mantle1m2H.PositionCorrectionCurve = Curve1m.Object;
		Mantle1mBox.PositionCorrectionCurve = Curve1m.Object;
	} else
		UALSLogger::LogError("Curve Mantle_1m not found.");
#pragma endregion

#pragma region Setting Up Land Roll
	const ConstructorHelpers::FObjectFinder<UAnimMontage> LandRollDefault(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_N_LandRoll_F_Montage_Default.ALS_N_LandRoll_F_Montage_Default'"));
	if (LandRollDefault.Succeeded())
		LandRoll_Default = LandRollDefault.Object;
	else
		UALSLogger::LogError("ALS_N_LandRoll_F_Montage_Default not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> LandRollRH(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_N_LandRoll_F_Montage_RH.ALS_N_LandRoll_F_Montage_RH'"));
	if (LandRollRH.Succeeded())
		LandRoll_RH = LandRollRH.Object;
	else
		UALSLogger::LogError("ALS_N_LandRoll_F_Montage_RH not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> LandRollLH(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_N_LandRoll_F_Montage_LH.ALS_N_LandRoll_F_Montage_LH'"));
	if (LandRollLH.Succeeded())
		LandRoll_LH = LandRollLH.Object;
	else
		UALSLogger::LogError("ALS_N_LandRoll_F_Montage_LH not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> LandRoll2H(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_N_LandRoll_F_Montage_2H.ALS_N_LandRoll_F_Montage_2H'"));
	if (LandRoll2H.Succeeded())
		LandRoll_2H = LandRoll2H.Object;
	else
		UALSLogger::LogError("ALS_N_LandRoll_F_Montage_2H not found.");
#pragma endregion

#pragma region MyRegion
	//Front
	const ConstructorHelpers::FObjectFinder<UAnimMontage> GetupFrontDefault(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_CLF_GetUp_Front_Montage_Default.ALS_CLF_GetUp_Front_Montage_Default'"));
	if (GetupFrontDefault.Succeeded())
		GetupFront_Default = GetupFrontDefault.Object;
	else
		UALSLogger::LogError("ALS_CLF_GetUp_Front_Montage_Default not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> GetupFrontRH(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_CLF_GetUp_Front_Montage_RH.ALS_CLF_GetUp_Front_Montage_RH'"));
	if (GetupFrontRH.Succeeded())
		GetupFront_RH = GetupFrontRH.Object;
	else
		UALSLogger::LogError("ALS_CLF_GetUp_Front_Montage_RH not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> GetupFrontLH(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_CLF_GetUp_Front_Montage_LH.ALS_CLF_GetUp_Front_Montage_LH'"));
	if (GetupFrontLH.Succeeded())
		GetupFront_LH = GetupFrontLH.Object;
	else
		UALSLogger::LogError("ALS_CLF_GetUp_Front_Montage_LH not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> GetupFront2H(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_CLF_GetUp_Front_Montage_2H.ALS_CLF_GetUp_Front_Montage_2H'"));
	if (GetupFront2H.Succeeded())
		GetupFront_2H = GetupFront2H.Object;
	else
		UALSLogger::LogError("ALS_CLF_GetUp_Front_Montage_LH not found.");

	//Back
	const ConstructorHelpers::FObjectFinder<UAnimMontage> GetupBackDefault(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_CLF_GetUp_Back_Montage_Default.ALS_CLF_GetUp_Back_Montage_Default'"));
	if (GetupBackDefault.Succeeded())
		GetupBack_Default = GetupBackDefault.Object;
	else
		UALSLogger::LogError("ALS_CLF_GetUp_Back_Montage_Default not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> GetupBackRH(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_CLF_GetUp_Back_Montage_RH.ALS_CLF_GetUp_Back_Montage_RH'"));
	if (GetupBackRH.Succeeded())
		GetupBack_RH = GetupBackRH.Object;
	else
		UALSLogger::LogError("ALS_CLF_GetUp_Back_Montage_RH not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> GetupBackLH(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_CLF_GetUp_Back_Montage_LH.ALS_CLF_GetUp_Back_Montage_LH'"));
	if (GetupBackLH.Succeeded())
		GetupBack_LH = GetupBackLH.Object;
	else
		UALSLogger::LogError("ALS_CLF_GetUp_Back_Montage_LH not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> GetupBack2H(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_CLF_GetUp_Back_Montage_2H.ALS_CLF_GetUp_Back_Montage_2H'"));
	if (GetupBack2H.Succeeded())
		GetupBack_2H = GetupBack2H.Object;
	else
		UALSLogger::LogError("ALS_CLF_GetUp_Back_Montage_LH not found.");
#pragma endregion

}

void AALSCharacter::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

	BodyMesh->SetMasterPoseComponent(GetMesh());
	SetDynamicMaterials();
	SetResetColors();
	ChangeMannequinMeshTo(CharacterModelType);
}

void AALSCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	UpdateColoringSystem();
	UpdateHeldObjectAnimations();
}

void AALSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindKey(EKeys::M, IE_Pressed, this, &AALSCharacter::ToggleCharacterMesh);
}

void AALSCharacter::SetDynamicMaterials() {
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

void AALSCharacter::SetResetColors() {
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

void AALSCharacter::UpdateColoringSystem() {
	const auto pc = UGameplayStatics::GetPlayerController(this, 0);
	if (IsValid(pc) && pc->GetClass()->ImplementsInterface(UALSControllerInterface::StaticClass())) {
		const auto debugInfo = IALSControllerInterface::Execute_GetDebugInfo(pc);
		if (debugInfo.bShowLayerColors && GetMesh()->IsVisible()) {
			bUpdateColoringSystemDoOnceFlag = true;
			UpdateLayeringColors();
		} else if (bUpdateColoringSystemDoOnceFlag) {
			bUpdateColoringSystemDoOnceFlag = false;
			SetResetColors();

			//TODO REMOVE in production
			UALSLogger::LogInfo(TEXT("Reminder Log: UpdateColoringSystem"));
		}
	}
}

void AALSCharacter::UpdateLayeringColors() {

	Head->SetVectorParameterValue(FName(TEXT("BaseColor")), LerpColors2Level(OverlayLayerColor, AdditiveAmountColor, BaseLayerColor, FName("Layering_Head_Add"), FName("Layering_Head")));
	Torso->SetVectorParameterValue(FName(TEXT("BaseColor")), LerpColors2Level(OverlayLayerColor, AdditiveAmountColor, BaseLayerColor, FName("Layering_Spine_Add"), FName("Layering_Spine")));

	Pelvis->SetVectorParameterValue(FName(TEXT("BaseColor")), UKismetMathLibrary::LinearColorLerp(BaseLayerColor, AdditiveAmountColor, GetAnimCurveValue(FName("Layering_Pelvis"))));
	UpperLegs->SetVectorParameterValue(FName(TEXT("BaseColor")), UKismetMathLibrary::LinearColorLerp(BaseLayerColor, AdditiveAmountColor, GetAnimCurveValue(FName("Layering_Legs"))));
	LowerLegs->SetVectorParameterValue(FName(TEXT("BaseColor")), UKismetMathLibrary::LinearColorLerp(BaseLayerColor, AdditiveAmountColor, GetAnimCurveValue(FName("Layering_Legs"))));
	Feet->SetVectorParameterValue(FName(TEXT("BaseColor")), UKismetMathLibrary::LinearColorLerp(BaseLayerColor, AdditiveAmountColor, GetAnimCurveValue(FName("Layering_Legs"))));

	Shoulder_L->SetVectorParameterValue(FName(TEXT("BaseColor")), LerpColors2Level(OverlayLayerColor, AdditiveAmountColor, BaseLayerColor, FName("Layering_Arm_L_Add"), FName("Layering_Arm_L")));
	UpperArm_L->SetVectorParameterValue(FName(TEXT("BaseColor")), LerpColors2Level(OverlayLayerColor, AdditiveAmountColor, BaseLayerColor, FName("Layering_Arm_L_Add"), FName("Layering_Arm_L")));
	LowerArm_L->SetVectorParameterValue(FName(TEXT("BaseColor")), LerpColors2Level(OverlayLayerColor, AdditiveAmountColor, BaseLayerColor, FName("Layering_Arm_L_Add"), FName("Layering_Arm_L")));
	const auto A = LowerArm_L->K2_GetVectorParameterValue(FName("BaseColor"));
	Hand_L->SetVectorParameterValue(FName(TEXT("BaseColor")), LerpColors2Level(A, HandColor, HandIKColor, FName("Layering_Hand_L"), FName("Enable_HandIK_L")));

	Shoulder_R->SetVectorParameterValue(FName(TEXT("BaseColor")), LerpColors2Level(OverlayLayerColor, AdditiveAmountColor, BaseLayerColor, FName("Layering_Arm_R_Add"), FName("Layering_Arm_R")));
	UpperArm_R->SetVectorParameterValue(FName(TEXT("BaseColor")), LerpColors2Level(OverlayLayerColor, AdditiveAmountColor, BaseLayerColor, FName("Layering_Arm_R_Add"), FName("Layering_Arm_R")));
	LowerArm_R->SetVectorParameterValue(FName(TEXT("BaseColor")), LerpColors2Level(OverlayLayerColor, AdditiveAmountColor, BaseLayerColor, FName("Layering_Arm_R_Add"), FName("Layering_Arm_R")));
	const auto B = LowerArm_R->K2_GetVectorParameterValue(FName("BaseColor"));
	Hand_R->SetVectorParameterValue(FName(TEXT("BaseColor")), LerpColors2Level(B, HandColor, HandIKColor, FName("Layering_Hand_R"), FName("Enable_HandIK_R")));
}

void AALSCharacter::UpdateHeldObject() {
	if (OverlayState == EALSOverlayState::ALS_Rifle) {
		AttachToHand(nullptr, M4A1);
	} else if (OverlayState == EALSOverlayState::ALS_Pistol1H || OverlayState == EALSOverlayState::ALS_Pistol2H) {
		AttachToHand(nullptr, M9);
	} else if (OverlayState == EALSOverlayState::ALS_Bow) {
		AttachToHand(nullptr, Bow);
	} else if (OverlayState == EALSOverlayState::ALS_Torch) {
		AttachToHand(Torch, nullptr);
	} else if (OverlayState == EALSOverlayState::ALS_Box) {
		AttachToHand(Box, nullptr);
	} else if (OverlayState == EALSOverlayState::ALS_Barrel) {
		AttachToHand(Barrel, nullptr, nullptr, true);
	} else if (OverlayState == EALSOverlayState::ALS_Binoculars) {
		AttachToHand(Binoculars, nullptr);
	} else {
		ClearHeldObject();
	}
}

void AALSCharacter::ClearHeldObject() {
	StaticMesh->SetStaticMesh(nullptr);
	SkeletalMesh->SetSkeletalMesh(nullptr, false);
	SkeletalMesh->SetAnimInstanceClass(nullptr);
}

void AALSCharacter::AttachToHand(UStaticMesh* NewStaticMesh, USkeletalMesh* NewSkeletalMesh, UClass* NewAnimClass, bool bLeftHand, FVector Offset) {
	ClearHeldObject();
	if (IsValid(NewStaticMesh))
		StaticMesh->SetStaticMesh(NewStaticMesh);
	if (IsValid(NewSkeletalMesh))
		SkeletalMesh->SetSkeletalMesh(NewSkeletalMesh);
	if (IsValid(NewAnimClass))
		SkeletalMesh->SetAnimInstanceClass(NewAnimClass);

	HeldObjectRoot->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, bLeftHand ? FName(TEXT("VB LHS_ik_hand_gun")) : FName(TEXT("VB RHS_ik_hand_gun")));
	HeldObjectRoot->SetRelativeLocation(Offset);
}

void AALSCharacter::UpdateHeldObjectAnimations() {
	if (OverlayState == EALSOverlayState::ALS_Bow && IsValid(BowAnimInstance)) {
		const auto animBp = static_cast<UALSBowAnimInstance*>(SkeletalMesh->GetAnimInstance());
		if (IsValid(animBp)) {
			animBp->ChangeDraw(GetAnimCurveValue("Enable_SpineRotation"));
		}
	}
}

FTransform AALSCharacter::Get3PPivotTarget_Implementation() {
	TArray<FVector> vectorArray;
	const auto mesh = GetMesh();
	vectorArray.Add(mesh->GetSocketLocation(FName("head")));
	vectorArray.Add(mesh->GetSocketLocation(FName("root")));
	return FTransform(GetActorRotation(), UKismetMathLibrary::GetVectorArrayAverage(vectorArray));
}

FALSTraceParams AALSCharacter::Get3PTraceParameters_Implementation() {
	Super::Get3PTraceParameters_Implementation();

	return FALSTraceParams(static_cast<TEnumAsByte<ETraceTypeQuery>>(ECC_Camera), GetMesh()->GetSocketLocation(FName(bRightShoulder ? "TP_CameraTrace_R" : "TP_CameraTrace_L")), 15.0f);
}

void AALSCharacter::OnOverlayStateChanged(const EALSOverlayState NewOverlayState) {
	Super::OnOverlayStateChanged(NewOverlayState);

	UpdateHeldObject();
}

UAnimMontage* AALSCharacter::GetRollAnimation() {
	switch (OverlayState) {
		case EALSOverlayState::ALS_HandsTied:
		case EALSOverlayState::ALS_Rifle:
		case EALSOverlayState::ALS_Binoculars:
		case EALSOverlayState::ALS_Box:
			return LandRoll_2H;
		case EALSOverlayState::ALS_Pistol1H:
		case EALSOverlayState::ALS_Pistol2H:
			return LandRoll_RH;
		case EALSOverlayState::ALS_Injured:
		case EALSOverlayState::ALS_Bow:
		case EALSOverlayState::ALS_Torch:
		case EALSOverlayState::ALS_Barrel:
			return LandRoll_LH;
		case EALSOverlayState::ALS_Default:;
		case EALSOverlayState::ALS_Masculine:
		case EALSOverlayState::ALS_Feminine:
		default:
			return LandRoll_Default;
	}
}

FALSMantleAsset AALSCharacter::GetMantleAsset(const EALSMantleType MantleType) {
	//Super::GetMantleAsset(MantleType);

	if (MantleType != EALSMantleType::ALS_LowMantle)
		return Mantle2mDefault;

	switch (OverlayState) {
		case EALSOverlayState::ALS_HandsTied:
			return Mantle1m2H;
		case EALSOverlayState::ALS_Rifle:
		case EALSOverlayState::ALS_Pistol1H:
		case EALSOverlayState::ALS_Pistol2H:
		case EALSOverlayState::ALS_Binoculars:
			return Mantle1mRH;
		case EALSOverlayState::ALS_Barrel:
		case EALSOverlayState::ALS_Injured:
		case EALSOverlayState::ALS_Bow:
		case EALSOverlayState::ALS_Torch:
			return Mantle1mRH;
		case EALSOverlayState::ALS_Box:
			return Mantle1mBox;
		case EALSOverlayState::ALS_Default:
		case EALSOverlayState::ALS_Masculine:
		case EALSOverlayState::ALS_Feminine:
		default:
			return Mantle1mDefault;
	}
}

void AALSCharacter::MantleStart(const float MantleHeight, const FALSComponentAndTransform MantleLedgeWS, const EALSMantleType MantleType) {
	Super::MantleStart(MantleHeight, MantleLedgeWS, MantleType);

	if (MantleType == EALSMantleType::ALS_LowMantle)
		return;

	ClearHeldObject();
}

void AALSCharacter::MantleEnd() {
	Super::MantleEnd();

	UpdateHeldObject();
}

UAnimMontage* AALSCharacter::GetGetupAnimation(const bool bIsRagdollFacedUp) {

	if (bIsRagdollFacedUp) {
		switch (OverlayState) {
			case EALSOverlayState::ALS_Default:
			case EALSOverlayState::ALS_Masculine:
			case EALSOverlayState::ALS_Feminine:
			default:
				return GetupBack_Default;
			case EALSOverlayState::ALS_Injured:
			case EALSOverlayState::ALS_Bow:
			case EALSOverlayState::ALS_Torch:
			case EALSOverlayState::ALS_Barrel:
				return GetupBack_LH;
			case EALSOverlayState::ALS_Rifle:
			case EALSOverlayState::ALS_Pistol1H:
			case EALSOverlayState::ALS_Pistol2H:
			case EALSOverlayState::ALS_Binoculars:
				return GetupBack_RH;
			case EALSOverlayState::ALS_HandsTied:
			case EALSOverlayState::ALS_Box:
				return GetupBack_2H;
		}
	}

	switch (OverlayState) {
		case EALSOverlayState::ALS_Default:
		case EALSOverlayState::ALS_Masculine:
		case EALSOverlayState::ALS_Feminine:
		default:
			return GetupFront_Default;
		case EALSOverlayState::ALS_Injured:
		case EALSOverlayState::ALS_Bow:
		case EALSOverlayState::ALS_Torch:
		case EALSOverlayState::ALS_Barrel:
			return GetupFront_LH;
		case EALSOverlayState::ALS_Rifle:
		case EALSOverlayState::ALS_Pistol1H:
		case EALSOverlayState::ALS_Pistol2H:
		case EALSOverlayState::ALS_Binoculars:
			return GetupFront_RH;
		case EALSOverlayState::ALS_HandsTied:
		case EALSOverlayState::ALS_Box:
			return GetupFront_2H;
	}
}

void AALSCharacter::RagdollStart() {
	Super::RagdollStart();
	UALSLogger::LogInfo(TEXT("Calling in ALSCharacter"));
}

void AALSCharacter::RagdollEnd() {
	Super::RagdollEnd();
}

void AALSCharacter::ToggleCharacterMesh() {
	ChangeMannequinMeshTo(CharacterModelType == EALSMannequinMeshType::ALS_Default ? EALSMannequinMeshType::ALS_Mannequin : EALSMannequinMeshType::ALS_Default);
}

void AALSCharacter::ChangeMannequinMeshTo(EALSMannequinMeshType MeshType) {
	if (MeshType != CharacterModelType) {

		GetMesh()->SetSkeletalMesh(MeshType == EALSMannequinMeshType::ALS_Mannequin ? MannequinMesh : DefaultMesh);

		CharacterModelType = MeshType;
	}
}

FLinearColor AALSCharacter::LerpColors2Level(const FLinearColor L1A, const FLinearColor L1B, const FLinearColor L2A, const FName L1Name, const FName L2Name) {
	const float alpha1 = GetAnimCurveValue(L1Name);
	const float alpha2 = GetAnimCurveValue(L2Name);

	const auto tmpColor = UKismetMathLibrary::LinearColorLerp(L1A, L2A, alpha1);
	return UKismetMathLibrary::LinearColorLerp(L2A, tmpColor, alpha2);
}