#include "LmPlayerController.h"
#include <Sound/SoundWave.h>

#include "EnhancedInputComponent.h"
#include "LmBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Locomotion/EnhancedInput/LmControllerInputConfiguration.h"
#include "Locomotion/GameplayFramework/Camera/LmPlayerCameraManager.h"
#include "Locomotion/Logging/LMLogger.h"
#include "Locomotion/UI/LmWOverlayStateSwitcher.h"


ALmPlayerController::ALmPlayerController() {
	bOverlayMenuOpen    = false;
	OverlaySwitcher     = nullptr;
	DebugFocusCharacter = nullptr;
	bShowHud            = false;
	bDebugView          = false;
	bShowTraces         = false;
	bShowDebugShapes    = false;
	bShowLayerColors    = false;
	bShowCharacterInfo  = false;
	bSlowMotion         = false;

	SelectedLmCharacterIndex = 0;
	static ConstructorHelpers::FObjectFinder<USoundWave> ClickSoundAsset( TEXT( "SoundWave'/Game/AdvancedLocomotionV4/Audio/UI/Click.Click'" ) );
	if ( ClickSoundAsset.Succeeded() )
		ClickSound = ClickSoundAsset.Object;
	else
		ULmLogger::LogError( "ClickSound not found." );

	PlayerCameraManagerClass = ALmPlayerCameraManager::StaticClass();

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> inputMappings( TEXT( "/Script/EnhancedInput.InputMappingContext'/Locomotion/Blueprints/Input/IMC_Locomotion.IMC_Locomotion'" ) );
	if ( inputMappings.Succeeded() )
		InputMappings = inputMappings.Object;
	else
		ULmLogger::LogError( "InputMappings not found." );

	static ConstructorHelpers::FObjectFinder<ULmControllerInputConfiguration>
	inputActions( TEXT( "/Script/Locomotion.LmControllerInputConfiguration'/Locomotion/Blueprints/Input/Actions/ControllerActions/DA_LmControllerInputActions.DA_LmControllerInputActions'" ) );
	if ( inputActions.Succeeded() )
		InputActions = inputActions.Object;
	else
		ULmLogger::LogError( "LmControllerInputConfiguration Data Asset not found." );

	PlayerCameraManagerClass = ALmPlayerCameraManager::StaticClass();
}


void ALmPlayerController::BeginPlay() {
	Super::BeginPlay();

	DebugFocusCharacter = UGameplayStatics::GetPlayerCharacter( this , 0 );

	if ( IsValid( HudTemplate ) )
		CreateWidget( this , HudTemplate )->AddToViewport();
	else
		ULmLogger::LogError( TEXT( "Locomotion HUD Template is null. Please set it in BP_LmPlayerController blueprint." ) );

	//Search for all LmCharacters and populate the array.
	//Used to switch target character when viewing character info in the HUD
	TArray<AActor*> lmCharacters;
	UGameplayStatics::GetAllActorsOfClass( GetWorld() , ALmBaseCharacter::StaticClass() , lmCharacters );
	for ( AActor* c : lmCharacters )
		AvailableDebugCharacters.Add( static_cast<ALmBaseCharacter*>(c) );

	OverlaySwitcher = static_cast<ULmWOverlayStateSwitcher*>(CreateWidget( this , OverlayStateSwitcherTemplate ));
}


void ALmPlayerController::OnPossess(APawn* InPawn) {
	Super::OnPossess( InPawn );

	auto* cameraManager = static_cast<ALmPlayerCameraManager*>(PlayerCameraManager);
	if ( IsValid( cameraManager ) ) {
		cameraManager->OnPossess( InPawn );
	} else {
		ULmLogger::LogError( TEXT( "Camera Manager is invalid." ) );
	}
}


void ALmPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	// Attaching Debug Keys to the game.
	if ( bBindDefaultInputKeys ) {
		//Checking the player input validity
		if ( !IsValid( InputComponent ) )
			return;

		// Get the local player subsystem
		const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>( GetLocalPlayer() );
		if ( bClearExistingKeyBindings ) {
			// Clear out existing mapping, and add our mapping
			Subsystem->ClearAllMappings();
		}

		Subsystem->AddMappingContext( InputMappings , 0 );

		// Get the EnhancedInputComponent
		const auto PEI = Cast<UEnhancedInputComponent>( InputComponent );

		//Movement Input
		PEI->BindAction( InputActions->ToggleHUD , ETriggerEvent::Triggered , this , &ALmPlayerController::ToggleShowHud );
		PEI->BindAction( InputActions->ToggleDebugView , ETriggerEvent::Triggered , this , &ALmPlayerController::ToggleDebugView );
		PEI->BindAction( InputActions->ToggleShowTraces , ETriggerEvent::Triggered , this , &ALmPlayerController::ToggleShowTraces );
		PEI->BindAction( InputActions->ToggleDebugShapes , ETriggerEvent::Triggered , this , &ALmPlayerController::ToggleShowDebugShapes );
		PEI->BindAction( InputActions->ToggleLayerColors , ETriggerEvent::Triggered , this , &ALmPlayerController::ToggleShowLayerColors );
		PEI->BindAction( InputActions->ToggleCharacterInfo , ETriggerEvent::Triggered , this , &ALmPlayerController::ToggleShowCharacterInfo );
		PEI->BindAction( InputActions->ToggleSlowMotion , ETriggerEvent::Triggered , this , &ALmPlayerController::ToggleSlowMotion );
		PEI->BindAction( InputActions->ToggleOverlayMenu , ETriggerEvent::Triggered , this , &ALmPlayerController::ToggleOverlayMenu );
		PEI->BindAction( InputActions->CycleDebugCharacters , ETriggerEvent::Triggered , this , &ALmPlayerController::SelectLmDebugCharacter );
		PEI->BindAction( InputActions->CycleOverlayMenuItems , ETriggerEvent::Triggered , this , &ALmPlayerController::CycleOverlayItems );
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
	UGameplayStatics::SetGlobalTimeDilation( this , bSlowMotion ? 0.05f : 1.0f );
}


void ALmPlayerController::CycleDebugCharacter(const bool bNext) {
	if ( bNext ) {
		SelectedLmCharacterIndex = SelectedLmCharacterIndex + 1 < AvailableDebugCharacters.Num() ? SelectedLmCharacterIndex + 1 : 0;
		DebugFocusCharacter      = AvailableDebugCharacters[SelectedLmCharacterIndex];
	} else {
		SelectedLmCharacterIndex = SelectedLmCharacterIndex - 1 > 0 ? SelectedLmCharacterIndex - 1 : AvailableDebugCharacters.Num() - 1;
		DebugFocusCharacter      = AvailableDebugCharacters[SelectedLmCharacterIndex];
	}
}


void ALmPlayerController::SelectLmDebugCharacter(const FInputActionValue& Value) {
	CycleDebugCharacter( Value.Get<float>() > 0 );
}


void ALmPlayerController::ToggleOverlayMenu(const FInputActionValue& Value) {
	Value.Get<bool>() ? OpenOverlayMenu() : CloseOverlayMenu();
}


void ALmPlayerController::CycleOverlayItems(const FInputActionValue& Value) {
	Value.Get<float>() < 0 ? CycleOverlayUp() : CycleOverlayDown();
}


void ALmPlayerController::OpenOverlayMenu() {
	bOverlayMenuOpen = true;

	if ( !bSlowMotion )
		UGameplayStatics::SetGlobalTimeDilation( this , 0.35f );

	OverlaySwitcher->AddToViewport();
	UGameplayStatics::PlaySound2D( this , ClickSound , 1.25f , 1.0f , 0.2f );
}


void ALmPlayerController::CloseOverlayMenu() {
	bOverlayMenuOpen = false;

	if ( !bSlowMotion )
		UGameplayStatics::SetGlobalTimeDilation( this , 1.0f );

	OverlaySwitcher->SelectOverlayState();
	OverlaySwitcher->RemoveFromParent();
	UGameplayStatics::PlaySound2D( this , ClickSound , 1.25f , 1.0f , 0.2f );
}


void ALmPlayerController::CycleOverlayUp() {
	if ( bOverlayMenuOpen && IsValid( OverlaySwitcher ) ) {
		OverlaySwitcher->CycleState( true );
		UGameplayStatics::PlaySound2D( this , ClickSound , 1.25f , 1.0f , 0.2f );
	}
}


void ALmPlayerController::CycleOverlayDown() {
	if ( bOverlayMenuOpen && IsValid( OverlaySwitcher ) ) {
		OverlaySwitcher->CycleState( false );
		UGameplayStatics::PlaySound2D( this , ClickSound , 1.25f , 1.0f , 0.2f );
	}
}


FLmDebugInfo ALmPlayerController::GetDebugInfo_Implementation() {
	return FLmDebugInfo( DebugFocusCharacter , bDebugView , bShowHud , bShowTraces , bShowDebugShapes , bShowLayerColors , bSlowMotion , bShowCharacterInfo && !bOverlayMenuOpen );
}
