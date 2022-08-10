#include "LmPlayerController.h"

#include "LmBaseCharacter.h"
#include "LmPlayerCameraManager.h"
#include "../LmLogger.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/LmWHuD.h"
#include <Sound/SoundWave.h>

ALmPlayerController::ALmPlayerController() {
	static ConstructorHelpers::FObjectFinder<USoundWave> clickSound(TEXT("SoundWave'/Game/AdvancedLocomotionV4/Audio/UI/Click.Click'"));
	if (clickSound.Succeeded())
		ClickSound = clickSound.Object;
	else
		ULmLogger::LogError("ClickSound not found.");

	/*static ConstructorHelpers::FObjectFinder<ULmWHuD> tmp1(TEXT("WidgetBlueprint'/Locomotion/UI/WBP_ALSHUD.WBP_ALSHUD'"));
	if (IsValid(tmp1.Object)) {
		HudTemplate = static_cast<UWidgetBlueprint>(tmp1.Object);
	}*/

	/*if (!IsValid(HudTemplate))
		ULmLogger::LogError(TEXT("ALS HUD Template is null. Please set it in BP_ALSPlayerController blueprint."));*/

	PlayerCameraManagerClass = ALmPlayerCameraManager::StaticClass();
}

void ALmPlayerController::BeginPlay() {
	Super::BeginPlay();

	DebugFocusCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	if (IsValid(HudTemplate))
		CreateWidget(this, HudTemplate)->AddToViewport();
	//else
	//	ULmLogger::LogError(TEXT("ALS HUD Template is null. Please set it in BP_ALSPlayerController blueprint."));

	//Search for all ALS Characters and populate array.
	//Used to switch target character when viewing character info in the HUD
	TArray<AActor*> alsCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALmBaseCharacter::StaticClass(), alsCharacters);
	for (AActor* c : alsCharacters)
		AvailableDebugCharacters.Add(static_cast<ALmBaseCharacter*>(c));

	OverlaySwitcher = static_cast<ULmWOverlayStateSwitcher*>(CreateWidget(this, OverlayStateSwitcherTemplate));
}

void ALmPlayerController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	auto* cameraManager = static_cast<ALmPlayerCameraManager*>(PlayerCameraManager);
	if (IsValid(cameraManager)) {
		cameraManager->OnPossess(InPawn);
	} else {
		ULmLogger::LogError(FString::Printf(TEXT("Camera Manager is invalid.")));
	}
}

void ALmPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	// Attaching Debug Keys to the game.
	if (bBindDefaultInputEvents) {
		InputComponent->BindKey(EKeys::Tab, IE_Pressed, this, &ALmPlayerController::ToggleShowHud);
		InputComponent->BindKey(EKeys::V, IE_Pressed, this, &ALmPlayerController::ToggleDebugView);
		InputComponent->BindKey(EKeys::T, IE_Pressed, this, &ALmPlayerController::ToggleShowTraces);
		InputComponent->BindKey(EKeys::Y, IE_Pressed, this, &ALmPlayerController::ToggleShowDebugShapes);
		InputComponent->BindKey(EKeys::U, IE_Pressed, this, &ALmPlayerController::ToggleShowLayerColors);
		InputComponent->BindKey(EKeys::I, IE_Pressed, this, &ALmPlayerController::ToggleShowCharacterInfo);
		InputComponent->BindKey(EKeys::Z, IE_Pressed, this, &ALmPlayerController::ToggleSlowMotion);

		InputComponent->BindKey(EKeys::Comma, IE_Pressed, this, &ALmPlayerController::SelectPrevALSCharacter);
		InputComponent->BindKey(EKeys::Period, IE_Pressed, this, &ALmPlayerController::SelectNextALSCharacter);

		InputComponent->BindAction(TEXT("OpenOverlayMenu"), IE_Pressed, this, &ALmPlayerController::OpenOverlayMenu);
		InputComponent->BindAction(TEXT("OpenOverlayMenu"), IE_Released, this, &ALmPlayerController::CloseOverlayMenu);

		InputComponent->BindAction(TEXT("CycleOverlayUp"), IE_Pressed, this, &ALmPlayerController::CycleOverlayDown);
		InputComponent->BindAction(TEXT("CycleOverlayDown"), IE_Released, this, &ALmPlayerController::CycleOverlayUp);
	}
}

void ALmPlayerController::ToggleShowHud() {
	bShowHud = !bShowHud;
}

void ALmPlayerController::ToggleDebugView() {
	bDebugView = !bDebugView;
}

void ALmPlayerController::ToggleShowTraces() {
	bShowTraces = !bShowTraces;
}

void ALmPlayerController::ToggleShowDebugShapes() {
	bShowDebugShapes = !bShowDebugShapes;
}

void ALmPlayerController::ToggleShowLayerColors() {
	bShowLayerColors = !bShowLayerColors;
}

void ALmPlayerController::ToggleShowCharacterInfo() {
	bShowCharacterInfo = !bShowCharacterInfo;
}

void ALmPlayerController::ToggleSlowMotion() {
	bSlowMotion = !bSlowMotion;
	UGameplayStatics::SetGlobalTimeDilation(this, bSlowMotion ? 0.05f : 1.0f);
}

void ALmPlayerController::SelectPrevALSCharacter() {
	SelectedALSCharacterIndex = SelectedALSCharacterIndex - 1 > 0 ? SelectedALSCharacterIndex - 1 : AvailableDebugCharacters.Num() - 1;
	DebugFocusCharacter = AvailableDebugCharacters[SelectedALSCharacterIndex];
}

void ALmPlayerController::SelectNextALSCharacter() {
	SelectedALSCharacterIndex = SelectedALSCharacterIndex + 1 < AvailableDebugCharacters.Num() ? SelectedALSCharacterIndex + 1 : 0;
	DebugFocusCharacter = AvailableDebugCharacters[SelectedALSCharacterIndex];
}

void ALmPlayerController::OpenOverlayMenu() {
	bOverlayMenuOpen = true;

	if (!bSlowMotion)
		UGameplayStatics::SetGlobalTimeDilation(this, 0.35f);

	OverlaySwitcher->AddToViewport();
	UGameplayStatics::PlaySound2D(this, ClickSound, 1.25f, 1.0f, 0.2f);
}

void ALmPlayerController::CloseOverlayMenu() {
	bOverlayMenuOpen = false;

	if (!bSlowMotion)
		UGameplayStatics::SetGlobalTimeDilation(this, 1.0f);

	OverlaySwitcher->SelectOverlayState();
	OverlaySwitcher->RemoveFromViewport();
	UGameplayStatics::PlaySound2D(this, ClickSound, 1.25f, 1.0f, 0.2f);
}

void ALmPlayerController::CycleOverlayUp() {
	if (bOverlayMenuOpen && IsValid(OverlaySwitcher)) {
		OverlaySwitcher->CycleState(true);
		UGameplayStatics::PlaySound2D(this, ClickSound, 1.25f, 1.0f, 0.2f);
	}
}

void ALmPlayerController::CycleOverlayDown() {
	if (bOverlayMenuOpen && IsValid(OverlaySwitcher)) {
		OverlaySwitcher->CycleState(false);
		UGameplayStatics::PlaySound2D(this, ClickSound, 1.25f, 1.0f, 0.2f);
	}
}

FLmDebugInfo ALmPlayerController::GetDebugInfo_Implementation() {
	return FLmDebugInfo(DebugFocusCharacter, bDebugView, bShowHud, bShowTraces, bShowDebugShapes, bShowLayerColors, bSlowMotion, bShowCharacterInfo && !bOverlayMenuOpen);
}