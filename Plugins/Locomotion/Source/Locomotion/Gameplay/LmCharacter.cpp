#include "LmCharacter.h"

#include <Components/SkeletalMeshComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <UObject/Class.h>
#include <UObject/ConstructorHelpers.h>

#include "LmHoldingObjectInterface.h"
#include "../LmLogger.h"
#include "../LmStructs.h"
#include "../Animation/LmBowAnimInstance.h"
#include "Kismet/GameplayStatics.h"

ALmCharacter::ALmCharacter() {
	const auto mesh = GetMesh();
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> Mannequin(TEXT("SkeletalMesh'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/Meshes/Mannequin.Mannequin'"));
	if (Mannequin.Succeeded())
		mesh->SetSkeletalMeshAsset(Mannequin.Object);
	else
		ULmLogger::LogError("Mannequin not found.");

	HoldingObject = CreateDefaultSubobject<UChildActorComponent>(FName("HoldingObjectComponent"));
	HoldingObject->AttachToComponent(mesh, FAttachmentTransformRules::KeepRelativeTransform);

	mesh->bUpdateJointsFromAnimation = true;

	const ConstructorHelpers::FObjectFinder<UDataTable> holdingObjects_dt(TEXT("DataTable'/Locomotion/Data/DT_HoldingActorInstances.DT_HoldingActorInstances'"));
	if (holdingObjects_dt.Succeeded()) {
		DT_HoldingActors.DataTable = holdingObjects_dt.Object;
		DT_HoldingActors.RowName = FName("Empty");
	}

	else
		ULmLogger::LogError("Holding Objects DataTable not found.");
#pragma region Setting up Mantles
	//Mantle 2m Default
	Mantle2mDefault.StartingOffset = FVector(0.0f, 65.0f, 200.0f);
	Mantle2mDefault.LowHeight = 125.0f;
	Mantle2mDefault.LowPlayRate = 1.2f;
	Mantle2mDefault.LowStartPosition = 0.6f;
	Mantle2mDefault.HighHeight = 200.0f;
	Mantle2mDefault.HighPlayRate = 1.2f;
	Mantle2mDefault.HighStartPosition = 0.0f;
	const ConstructorHelpers::FObjectFinder<UAnimMontage> Montage2m(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_N_Mantle_2m_Montage_Default.ALS_N_Mantle_2m_Montage_Default'"));
	if (Montage2m.Succeeded())
		Mantle2mDefault.AnimMontage = Montage2m.Object;
	else
		ULmLogger::LogError("Lm_N_Mantle_2m_Montage_Default not found.");
	const ConstructorHelpers::FObjectFinder<UCurveVector> Curve2m(TEXT("CurveVector'/Game/AdvancedLocomotionV4/Data/Curves/MantleCurves/Mantle_2m.Mantle_2m'"));
	if (Curve2m.Succeeded())
		Mantle2mDefault.PositionCorrectionCurve = Curve2m.Object;
	else
		ULmLogger::LogError("Curve Mantle_2m not found.");

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
		ULmLogger::LogError("Lm_N_Mantle_1m_Montage_Default not found.");

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
		ULmLogger::LogError("Lm_N_Mantle_1m_Montage_RH not found.");


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
		ULmLogger::LogError("Lm_N_Mantle_1m_Montage_LH not found.");

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
		ULmLogger::LogError("Lm_N_Mantle_1m_Montage_2H not found.");

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
		ULmLogger::LogError("Lm_N_Mantle_1m_Montage_Box not found.");

	//Setting up 1m Mantle Curve
	const ConstructorHelpers::FObjectFinder<UCurveVector> Curve1m(TEXT("CurveVector'/Game/AdvancedLocomotionV4/Data/Curves/MantleCurves/Mantle_1m.Mantle_1m'"));
	if (Curve1m.Succeeded()) {
		Mantle1mDefault.PositionCorrectionCurve = Curve1m.Object;
		Mantle1mRH.PositionCorrectionCurve = Curve1m.Object;
		Mantle1mLH.PositionCorrectionCurve = Curve1m.Object;
		Mantle1m2H.PositionCorrectionCurve = Curve1m.Object;
		Mantle1mBox.PositionCorrectionCurve = Curve1m.Object;
	} else
		ULmLogger::LogError("Curve Mantle_1m not found.");
#pragma endregion

#pragma region Setting Up Land Roll
	const ConstructorHelpers::FObjectFinder<UAnimMontage> LandRollDefault(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_N_LandRoll_F_Montage_Default.ALS_N_LandRoll_F_Montage_Default'"));
	if (LandRollDefault.Succeeded())
		LandRoll_Default = LandRollDefault.Object;
	else
		ULmLogger::LogError("Lm_N_LandRoll_F_Montage_Default not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> LandRollRH(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_N_LandRoll_F_Montage_RH.ALS_N_LandRoll_F_Montage_RH'"));
	if (LandRollRH.Succeeded())
		LandRoll_RH = LandRollRH.Object;
	else
		ULmLogger::LogError("Lm_N_LandRoll_F_Montage_RH not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> LandRollLH(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_N_LandRoll_F_Montage_LH.ALS_N_LandRoll_F_Montage_LH'"));
	if (LandRollLH.Succeeded())
		LandRoll_LH = LandRollLH.Object;
	else
		ULmLogger::LogError("Lm_N_LandRoll_F_Montage_LH not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> LandRoll2H(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_N_LandRoll_F_Montage_2H.ALS_N_LandRoll_F_Montage_2H'"));
	if (LandRoll2H.Succeeded())
		LandRoll_2H = LandRoll2H.Object;
	else
		ULmLogger::LogError("Lm_N_LandRoll_F_Montage_2H not found.");
#pragma endregion

#pragma region Getup Montages
	//Front
	const ConstructorHelpers::FObjectFinder<UAnimMontage> GetupFrontDefault(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_CLF_GetUp_Front_Montage_Default.ALS_CLF_GetUp_Front_Montage_Default'"));
	if (GetupFrontDefault.Succeeded())
		GetupFront_Default = GetupFrontDefault.Object;
	else
		ULmLogger::LogError("Lm_CLF_GetUp_Front_Montage_Default not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> GetupFrontRH(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_CLF_GetUp_Front_Montage_RH.ALS_CLF_GetUp_Front_Montage_RH'"));
	if (GetupFrontRH.Succeeded())
		GetupFront_RH = GetupFrontRH.Object;
	else
		ULmLogger::LogError("Lm_CLF_GetUp_Front_Montage_RH not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> GetupFrontLH(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_CLF_GetUp_Front_Montage_LH.ALS_CLF_GetUp_Front_Montage_LH'"));
	if (GetupFrontLH.Succeeded())
		GetupFront_LH = GetupFrontLH.Object;
	else
		ULmLogger::LogError("Lm_CLF_GetUp_Front_Montage_LH not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> GetupFront2H(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_CLF_GetUp_Front_Montage_2H.ALS_CLF_GetUp_Front_Montage_2H'"));
	if (GetupFront2H.Succeeded())
		GetupFront_2H = GetupFront2H.Object;
	else
		ULmLogger::LogError("Lm_CLF_GetUp_Front_Montage_LH not found.");

	//Back
	const ConstructorHelpers::FObjectFinder<UAnimMontage> GetupBackDefault(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_CLF_GetUp_Back_Montage_Default.ALS_CLF_GetUp_Back_Montage_Default'"));
	if (GetupBackDefault.Succeeded())
		GetupBack_Default = GetupBackDefault.Object;
	else
		ULmLogger::LogError("Lm_CLF_GetUp_Back_Montage_Default not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> GetupBackRH(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_CLF_GetUp_Back_Montage_RH.ALS_CLF_GetUp_Back_Montage_RH'"));
	if (GetupBackRH.Succeeded())
		GetupBack_RH = GetupBackRH.Object;
	else
		ULmLogger::LogError("Lm_CLF_GetUp_Back_Montage_RH not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> GetupBackLH(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_CLF_GetUp_Back_Montage_LH.ALS_CLF_GetUp_Back_Montage_LH'"));
	if (GetupBackLH.Succeeded())
		GetupBack_LH = GetupBackLH.Object;
	else
		ULmLogger::LogError("Lm_CLF_GetUp_Back_Montage_LH not found.");

	const ConstructorHelpers::FObjectFinder<UAnimMontage> GetupBack2H(TEXT("AnimMontage'/Game/AdvancedLocomotionV4/CharacterAssets/MannequinSkeleton/AnimationExamples/Actions/ALS_CLF_GetUp_Back_Montage_2H.ALS_CLF_GetUp_Back_Montage_2H'"));
	if (GetupBack2H.Succeeded())
		GetupBack_2H = GetupBack2H.Object;
	else
		ULmLogger::LogError("Lm_CLF_GetUp_Back_Montage_LH not found.");
#pragma endregion

}

void ALmCharacter::UpdateHeldObject() {
	FName rowName = TEXT("Empty");
	if (OverlayState == ELmOverlayState::Lm_Rifle) {
		rowName = FName(TEXT("Rifle"));
	} else if (OverlayState == ELmOverlayState::Lm_Pistol1H) {
		rowName = FName(TEXT("Pistol1Hand"));
	} else if (OverlayState == ELmOverlayState::Lm_Pistol2H) {
		rowName = FName(TEXT("Pistol2Hands"));
	} else if (OverlayState == ELmOverlayState::Lm_Bow) {
		rowName = FName(TEXT("Bow"));
	} else if (OverlayState == ELmOverlayState::Lm_Torch) {
		rowName = FName(TEXT("Torch"));
	} else if (OverlayState == ELmOverlayState::Lm_Box) {
		rowName = FName(TEXT("Box"));
	} else if (OverlayState == ELmOverlayState::Lm_Barrel) {
		rowName = FName(TEXT("Barrel"));
	} else if (OverlayState == ELmOverlayState::Lm_Binoculars) {
		rowName = FName(TEXT("Binoculars"));
	}

	const auto& NewHoldingObject = *DT_HoldingActors.DataTable->FindRow<FLmHoldingInstance>(rowName, TEXT("NONE"), true);
	SetHeldObject(NewHoldingObject);
}

void ALmCharacter::SetHeldObject(const FLmHoldingInstance NewHoldingObject) {
	if (IsValid(NewHoldingObject.Instance)) {
		ClearHeldObject();

		SetOverlayState(NewHoldingObject.OverlayState);

		AttachToHand(NewHoldingObject);
	} else {
		ClearHeldObject();
	}
}

void ALmCharacter::ClearHeldObject() {
	HoldingObject->SetChildActorClass(nullptr);
}

void ALmCharacter::AttachToHand(FLmHoldingInstance NewHoldingObject) {
	HoldingObject->SetChildActorClass(NewHoldingObject.Instance);
	HoldingObject->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true), NewHoldingObject.UsingHands == ELmUseWhichHand::Lm_LeftHand ? FName(TEXT("VB LHS_ik_hand_gun")) : FName(TEXT("VB RHS_ik_hand_gun")));
	HoldingObject->SetRelativeLocation(NewHoldingObject.Offset);

	if (HoldingObject->GetChildActor()->GetClass()->ImplementsInterface(ULmHoldingObjectInterface::StaticClass()))
		ILmHoldingObjectInterface::Execute_SetParent(HoldingObject->GetChildActor(), this);
}

FTransform ALmCharacter::Get3PPivotTarget_Implementation() {
	TArray<FVector> vectorArray;
	const auto mesh = GetMesh();
	vectorArray.Add(mesh->GetSocketLocation(FName("head")));
	vectorArray.Add(mesh->GetSocketLocation(FName("root")));
	return FTransform(GetActorRotation(), UKismetMathLibrary::GetVectorArrayAverage(vectorArray));
}

FLmTraceParams ALmCharacter::Get3PTraceParameters_Implementation() {
	return FLmTraceParams(ETT_CameraCollisionChannel, GetMesh()->GetSocketLocation(FName(bRightShoulder ? "TP_CameraTrace_R" : "TP_CameraTrace_L")), 15.0f);
}

void ALmCharacter::OnOverlayStateChanged(const ELmOverlayState NewOverlayState) {
	Super::OnOverlayStateChanged(NewOverlayState);

	UpdateHeldObject();
}

UAnimMontage* ALmCharacter::GetRollAnimation() {
	switch (OverlayState) {
	case ELmOverlayState::Lm_HandsTied:
	case ELmOverlayState::Lm_Rifle:
	case ELmOverlayState::Lm_Binoculars:
	case ELmOverlayState::Lm_Box:
		return LandRoll_2H;
	case ELmOverlayState::Lm_Pistol1H:
	case ELmOverlayState::Lm_Pistol2H:
		return LandRoll_RH;
	case ELmOverlayState::Lm_Injured:
	case ELmOverlayState::Lm_Bow:
	case ELmOverlayState::Lm_Torch:
	case ELmOverlayState::Lm_Barrel:
		return LandRoll_LH;
	case ELmOverlayState::Lm_Default:;
	case ELmOverlayState::Lm_Masculine:
	case ELmOverlayState::Lm_Feminine:
	default:
		return LandRoll_Default;
	}
}

FLmMantleAsset ALmCharacter::GetMantleAsset(const ELmMantleType MantleType) {
	//Check if the mantle type is falling catch or high-mantle to return the Mantle2mDefault
	if (MantleType != ELmMantleType::Lm_LowMantle)
		return Mantle2mDefault;

	switch (OverlayState) {
	case ELmOverlayState::Lm_HandsTied:
		return Mantle1m2H;
	case ELmOverlayState::Lm_Rifle:
	case ELmOverlayState::Lm_Pistol1H:
	case ELmOverlayState::Lm_Pistol2H:
	case ELmOverlayState::Lm_Binoculars:
		return Mantle1mRH;
	case ELmOverlayState::Lm_Barrel:
	case ELmOverlayState::Lm_Injured:
	case ELmOverlayState::Lm_Bow:
	case ELmOverlayState::Lm_Torch:
		return Mantle1mRH;
	case ELmOverlayState::Lm_Box:
		return Mantle1mBox;
	case ELmOverlayState::Lm_Default:
	case ELmOverlayState::Lm_Masculine:
	case ELmOverlayState::Lm_Feminine:
	default:
		return Mantle1mDefault;
	}
}

void ALmCharacter::MantleStart(const float MantleHeight, const FLmComponentAndTransform MantleLedgeWS, const ELmMantleType MantleType) {
	Super::MantleStart(MantleHeight, MantleLedgeWS, MantleType);

	if (MantleType != ELmMantleType::Lm_LowMantle)
		ClearHeldObject();
}

void ALmCharacter::MantleEnd() {
	Super::MantleEnd();

	UpdateHeldObject();
}

UAnimMontage* ALmCharacter::GetGetupAnimation(const bool bIsRagdollFacedUp) {

	if (bIsRagdollFacedUp) {
		switch (OverlayState) {
		case ELmOverlayState::Lm_Default:
		case ELmOverlayState::Lm_Masculine:
		case ELmOverlayState::Lm_Feminine:
		default:
			return GetupBack_Default;
		case ELmOverlayState::Lm_Injured:
		case ELmOverlayState::Lm_Bow:
		case ELmOverlayState::Lm_Torch:
		case ELmOverlayState::Lm_Barrel:
			return GetupBack_LH;
		case ELmOverlayState::Lm_Rifle:
		case ELmOverlayState::Lm_Pistol1H:
		case ELmOverlayState::Lm_Pistol2H:
		case ELmOverlayState::Lm_Binoculars:
			return GetupBack_RH;
		case ELmOverlayState::Lm_HandsTied:
		case ELmOverlayState::Lm_Box:
			return GetupBack_2H;
		}
	}

	switch (OverlayState) {
	case ELmOverlayState::Lm_Default:
	case ELmOverlayState::Lm_Masculine:
	case ELmOverlayState::Lm_Feminine:
	default:
		return GetupFront_Default;
	case ELmOverlayState::Lm_Injured:
	case ELmOverlayState::Lm_Bow:
	case ELmOverlayState::Lm_Torch:
	case ELmOverlayState::Lm_Barrel:
		return GetupFront_LH;
	case ELmOverlayState::Lm_Rifle:
	case ELmOverlayState::Lm_Pistol1H:
	case ELmOverlayState::Lm_Pistol2H:
	case ELmOverlayState::Lm_Binoculars:
		return GetupFront_RH;
	case ELmOverlayState::Lm_HandsTied:
	case ELmOverlayState::Lm_Box:
		return GetupFront_2H;
	}
}

void ALmCharacter::RagdollStart() {
	ClearHeldObject();
	Super::RagdollStart();
}

void ALmCharacter::RagdollEnd() {
	Super::RagdollEnd();

	UpdateHeldObject();
}