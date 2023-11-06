#include "LmWOverlayStateSwitcher.h"
#include <Blueprint/UserWidget.h>
#include <Components/CanvasPanelSlot.h>
#include <Components/TextBlock.h>
#include <GameFramework/Character.h>
#include <Misc/EnumRange.h>
#include "LmWOverlayStateButton.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Locomotion/GameplayFramework/Camera/Interfaces/LmCameraInterface.h"
#include "Locomotion/GameplayFramework/Character/Interfaces/LmCharacterInterface.h"


void ULmWOverlayStateSwitcher::NativeOnInitialized() {
	for ( const ELmOverlayState Value : TEnumRange<ELmOverlayState>() )
		OverlayStates.Add( Value );
}


void ULmWOverlayStateSwitcher::NativeConstruct() {
	Super::NativeConstruct();

	auto* Character = GetOwningPlayer()->GetCharacter();
	if ( Character->GetClass()->ImplementsInterface( ULmCharacterInterface::StaticClass() ) ) {
		NewOverlayState = ILmCharacterInterface::Execute_GetCurrentState( Character ).OverlayState;

		if ( VerticalBox->GetChildrenCount() == 0 )
			CreateButtons();

		UpdateButtonFocus();
	}
}


void ULmWOverlayStateSwitcher::NativeTick(const FGeometry& MovieSceneBlends, const float InDeltaTime) {
	Super::NativeTick( MovieSceneBlends , InDeltaTime );

	//local player controller
	const auto PC = GetOwningPlayer()->GetPawn();

	if ( PC->GetClass()->ImplementsInterface( ULmCameraInterface::StaticClass() ) ) {
		const FTransform Transform = ILmCameraInterface::Execute_Get3PPivotTarget( PC );

		FVector2D ScreenPosition;
		UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition( GetOwningPlayer() , Transform.GetLocation() + FVector( 0 , 0 , 100 ) , ScreenPosition , false );
		UWidgetLayoutLibrary::SlotAsCanvasSlot( MovablePanels )->SetPosition( ScreenPosition );
	}
}


void ULmWOverlayStateSwitcher::SelectOverlayState() const {
	auto* Character = GetOwningPlayer()->GetCharacter();
	if ( Character->GetClass()->ImplementsInterface( ULmCharacterInterface::StaticClass() ) ) {
		ILmCharacterInterface::Execute_SetOverlayState( Character , NewOverlayState );
	}
}


void ULmWOverlayStateSwitcher::CreateButtons() {
	//Lm_Barrel is the last element in the ELmOverlayState enum. if any other states added
	for ( const ELmOverlayState value : TEnumRange<ELmOverlayState>() ) {
		const auto button = static_cast<ULmWOverlayStateButton*>(CreateWidget( GetOwningPlayer() , OverlayStateButtonTemplate ));
		button->GetText()->SetText( FText::FromString( UEnum::GetDisplayValueAsText( value ).ToString() ) );
		VerticalBox->AddChildToVerticalBox( button );
		OverlayStateButtons.Add( FLmOverlayStateParams( button , value ) );
	}
}


void ULmWOverlayStateSwitcher::UpdateButtonFocus() {
	for ( const auto Element : OverlayStateButtons )
		if ( IsValid( Element.Widget ) )
			Element.Widget->SetVisualParameters( Element.State == NewOverlayState );
}


void ULmWOverlayStateSwitcher::SetUIElements(UCanvasPanel* MovablePanel, UVerticalBox* VBox) {
	MovablePanels = MovablePanel;
	VerticalBox   = VBox;
}


void ULmWOverlayStateSwitcher::CycleState(const bool bUp) {
	if ( bUp )
		SelectedIndex = SelectedIndex + 1 < OverlayStates.Num() ? SelectedIndex + 1 : 0;
	else
		SelectedIndex = SelectedIndex - 1 >= 0 ? SelectedIndex - 1 : OverlayStates.Num() - 1;

	NewOverlayState = OverlayStates[SelectedIndex];

	UpdateButtonFocus();
}
