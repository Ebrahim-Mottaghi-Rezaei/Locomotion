#include "ALSPlayerController.h"
#include "ALSBaseCharacter.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "InputCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "CALSv4/Core/CameraSystem/ALSPlayerCameraManager.h"
#include <CALSv4/Core/Utilities/ALSDebug.h>
#include <CALSv4/Core/Utilities/ALSHelpers.h>
#include "Kismet/GameplayStatics.h"

void AALSPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto* hudWidget = static_cast<UALSHudWidget*>(CreateWidget(this, ALSHudWidget));
	hudWidget->AddToViewport();

	DebugFocusCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	//Search for all ALS Characters and populate array.
	//Used to switch target character when viewing character info in the HUD
	TArray<AActor*> alsCharacters;
	UGameplayStatics::GetAllActorsOfClass(this, AALSBaseCharacter::StaticClass(), alsCharacters);
	for (AActor* c : alsCharacters)
		AvailableDebugCharacters.Add(static_cast<AALSBaseCharacter*>(c));
}

void AALSPlayerController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	auto* cameraManager = static_cast<AALSPlayerCameraManager*>(PlayerCameraManager);
	if (IsValid(cameraManager)) {
		cameraManager->OnPossess(InPawn);
	} else {
		ALSDebug::LogError(FString::Printf(TEXT("Camera Manager is invalid.")));
	}
}

void AALSPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	// Attaching Debug Keys to the game.
	InputComponent->BindKey(EKeys::Tab, IE_Pressed, this, &AALSPlayerController::ToggleShowHud);
	InputComponent->BindKey(EKeys::V, IE_Pressed, this, &AALSPlayerController::ToggleDebugView);
	InputComponent->BindKey(EKeys::T, IE_Pressed, this, &AALSPlayerController::ToggleShowTraces);
	InputComponent->BindKey(EKeys::Y, IE_Pressed, this, &AALSPlayerController::ToggleShowDebugShapes);
	InputComponent->BindKey(EKeys::U, IE_Pressed, this, &AALSPlayerController::ToggleShowLayerColors);
	InputComponent->BindKey(EKeys::I, IE_Pressed, this, &AALSPlayerController::ToggleShowCharacterInfo);
	InputComponent->BindKey(EKeys::Z, IE_Pressed, this, &AALSPlayerController::ToggleSlowMotion);
	InputComponent->BindKey(EKeys::Comma, IE_Pressed, this, &AALSPlayerController::SelectPrevItem);
	InputComponent->BindKey(EKeys::Period, IE_Pressed, this, &AALSPlayerController::SelectNextItem);

	InputComponent->BindAction(TEXT("OpenOverlayMenu"), IE_Pressed, this, &AALSPlayerController::OpenOverlayMenu);
	InputComponent->BindAction(TEXT("CloseOverlayMenu"), IE_Released, this, &AALSPlayerController::CloseOverlayMenu);

	InputComponent->BindAction(TEXT("CycleOverlayUp"), IE_Pressed, this, &AALSPlayerController::OpenOverlayMenu);
	InputComponent->BindAction(TEXT("CycleOverlayDown"), IE_Released, this, &AALSPlayerController::CloseOverlayMenu);
}

void AALSPlayerController::ToggleShowHud() {
	bShowHud = !bShowHud;
}

void AALSPlayerController::ToggleDebugView() {
	bDebugView = !bDebugView;
}

void AALSPlayerController::ToggleShowTraces() {
	bShowTraces = !bShowTraces;
}

void AALSPlayerController::ToggleShowDebugShapes() {
	bShowDebugShapes = !bShowDebugShapes;
}

void AALSPlayerController::ToggleShowLayerColors() {
	bShowLayerColors = !bShowLayerColors;
}

void AALSPlayerController::ToggleShowCharacterInfo() {
	bShowCharacterInfo = !bShowCharacterInfo;
}

void AALSPlayerController::ToggleSlowMotion() {
	bSlowMotion = !bSlowMotion;
	UGameplayStatics::SetGlobalTimeDilation(this, bSlowMotion ? 0.15f : 1.0f);
}

void AALSPlayerController::SelectPrevItem() {
	//DebugFocusCharacter = TALSHelpers<ACharacter*>::GetItemInArray(AvailableDebugCharacters, DebugFocusCharacter, false);
}

void AALSPlayerController::SelectNextItem() {
	//DebugFocusCharacter = TALSHelpers<ACharacter*>::GetItemInArray(AvailableDebugCharacters, DebugFocusCharacter, true);
}

void AALSPlayerController::OpenOverlayMenu() {
	bOverlayMenuOpen = true;

	if (!bSlowMotion)
		UGameplayStatics::SetGlobalTimeDilation(this, 0.35f);

	OverlaySwitcher = (UALSOverlayStateSwitcherWidget*)CreateWidget(this, UALSOverlayStateSwitcherWidget::StaticClass());
	OverlaySwitcher->AddToViewport();
	UGameplayStatics::PlaySound2D(this, ClickSound, 1.25f, 1.0f, 0.2f);
}

void AALSPlayerController::CloseOverlayMenu() {
	bOverlayMenuOpen = false;

	if (!bSlowMotion)
		UGameplayStatics::SetGlobalTimeDilation(this, 1.0f);

	OverlaySwitcher->SelectOverlayState();
	OverlaySwitcher->RemoveFromViewport();
	UGameplayStatics::PlaySound2D(this, ClickSound, 1.25f, 1.0f, 0.2f);
}

void AALSPlayerController::CycleOverlayUp() {
	if (bOverlayMenuOpen && IsValid(OverlaySwitcher)) {
		OverlaySwitcher->CycleState(true);
		UGameplayStatics::PlaySound2D(this, ClickSound, 1.25f, 1.0f, 0.2f);
	}
}

void AALSPlayerController::CycleOverlayDown() {
	if (bOverlayMenuOpen && IsValid(OverlaySwitcher)) {
		OverlaySwitcher->CycleState(false);
		UGameplayStatics::PlaySound2D(this, ClickSound, 1.25f, 1.0f, 0.2f);
	}
}