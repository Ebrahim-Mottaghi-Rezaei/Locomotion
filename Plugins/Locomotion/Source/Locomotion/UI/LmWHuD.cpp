#include "LmWHuD.h"
#include <Blueprint/WidgetLayoutLibrary.h>
#include <Layout/Geometry.h>
#include "Components/CanvasPanelSlot.h"
#include "Locomotion/GameplayFramework/Camera/Interfaces/LmCameraInterface.h"
#include "Locomotion/GameplayFramework/Character/Interfaces/LmCharacterInterface.h"
#include "Locomotion/GameplayFramework/Character/Interfaces/LmControllerInterface.h"


void ULmWHuD::NativeTick(const FGeometry& MovieSceneBlends, const float InDeltaTime) {
	Super::NativeTick( MovieSceneBlends , InDeltaTime );

	dt = InDeltaTime;

	const auto PC = GetOwningPlayer();
	if ( PC->GetClass()->ImplementsInterface( ULmControllerInterface::StaticClass() ) ) {
		const auto Info     = ILmControllerInterface::Execute_GetDebugInfo( PC );
		DebugFocusCharacter = Info.DebugFocusCharacter;
		bDebugView          = Info.bDebugView;
		bShowHUD            = Info.bShowHUD;
		bShowTraces         = Info.bShowTraces;
		bShowDebugShapes    = Info.bShowDebugShapes;
		bShowLayerColors    = Info.bShowLayerColors;
		bSlowMotion         = Info.bSlowMotion;
		bShowCharacterInfo  = Info.bShowCharacterInfo;
	}

	if ( GetCharacterInfoVisibility() == ESlateVisibility::Visible ) {
		if ( IsValid( DebugFocusCharacter ) )
			if ( DebugFocusCharacter->GetClass()->ImplementsInterface( ULmCameraInterface::StaticClass() ) ) {
				const auto Transform = ILmCameraInterface::Execute_Get3PPivotTarget( DebugFocusCharacter );

				FVector2D ScreenPosition;
				UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition( PC , Transform.GetLocation() + FVector( 0 , 0 , 100 ) , ScreenPosition , false );
				UWidgetLayoutLibrary::SlotAsCanvasSlot( MovingPanel )->SetPosition( ScreenPosition );
			}
	}
}


void ULmWHuD::SetMovingPanel(UCanvasPanel* Panel) {
	MovingPanel = Panel;
}


ESlateVisibility ULmWHuD::GetHudVisibility() const {
	return bShowHUD ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
}


ESlateVisibility ULmWHuD::GetCharacterInfoVisibility() const {
	return IsValid( DebugFocusCharacter ) && bShowCharacterInfo ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
}


FSlateColor ULmWHuD::GetShowHudColor() const {
	return bShowHUD ? EnabledColor : DisabledColor;
}


FSlateColor ULmWHuD::GetSlowMotionColor() const {
	return bSlowMotion ? EnabledColor : DisabledColor;
}


FSlateColor ULmWHuD::GetDebugViewColor() const {
	return bDebugView ? EnabledColor : DisabledColor;
}


FSlateColor ULmWHuD::GetShowTracesColor() const {
	return bShowTraces ? EnabledColor : DisabledColor;
}


FSlateColor ULmWHuD::GetShowDebugShapesColor() const {
	return bShowDebugShapes ? EnabledColor : DisabledColor;
}


FSlateColor ULmWHuD::GetShowLayerShapesColor() const {
	return bShowLayerColors ? EnabledColor : DisabledColor;
}


FSlateColor ULmWHuD::GetShowCharacterInfoColor() const {
	return bShowCharacterInfo ? EnabledColor : DisabledColor;
}


FString ULmWHuD::GetDebugCharacterName() const {
	return IsValid( DebugFocusCharacter ) ? DebugFocusCharacter->GetName() : FString( TEXT( "ULmWHuD::GetDebugCharacterName | No Valid Character Selected" ) );
}


FString ULmWHuD::GetCharacterStates() const {
	if ( bShowCharacterInfo && IsValid( DebugFocusCharacter ) && DebugFocusCharacter->GetClass()->ImplementsInterface( ULmCharacterInterface::StaticClass() ) ) {
		const auto State = ILmCharacterInterface::Execute_GetCurrentState( DebugFocusCharacter );

		return FString::Printf( TEXT( "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s" ) ,
		                        *UEnum::GetDisplayValueAsText( State.PawnMovementMode ).ToString() ,
		                        *UEnum::GetDisplayValueAsText( State.MovementState ).ToString() ,
		                        *UEnum::GetDisplayValueAsText( State.MovementAction ).ToString() ,
		                        *UEnum::GetDisplayValueAsText( State.RotationMode ).ToString() ,
		                        *UEnum::GetDisplayValueAsText( State.ActualGait ).ToString() ,
		                        *UEnum::GetDisplayValueAsText( State.ActualStance ).ToString() ,
		                        *UEnum::GetDisplayValueAsText( State.ViewMode ).ToString() ,
		                        *UEnum::GetDisplayValueAsText( State.OverlayState ).ToString()
		                      );
	}

	return FString( TEXT( "" ) );
}


FString ULmWHuD::GetAnimCurvesNames() const {
	if ( !IsValid( DebugFocusCharacter ) )
		return FString( "ULmWHuD::GetAnimCurvesNames::DebugFocusCharacter is not valid" );

	if ( !IsValid( DebugFocusCharacter->GetMesh()->GetAnimInstance() ) )
		return FString( "ULmWHuD::GetAnimCurvesNames::AnimInstance is not valid" );

	const auto*   AnimInstance = DebugFocusCharacter->GetMesh()->GetAnimInstance();
	TArray<FName> CurveNames;
	AnimInstance->GetActiveCurveNames( EAnimCurveType::AttributeCurve , CurveNames );
	FString Value;

	for ( FName Name : CurveNames ) {
		Value.Append( Name.ToString() );
		Value.Append( FString( TEXT( "\n" ) ) );
	}

	return Value;
}


FText ULmWHuD::GetAnimCurvesValues() const {
	if ( !IsValid( DebugFocusCharacter ) )
		return FText::FromString( TEXT( "ULmWHuD::GetAnimCurvesValues::DebugFocusCharacter is not valid" ) );

	if ( !IsValid( DebugFocusCharacter->GetMesh()->GetAnimInstance() ) )
		return FText::FromString( "ULmWHuD::GetAnimCurvesValues::AnimInstance is not valid" );

	const auto* AnimInstance = DebugFocusCharacter->GetMesh()->GetAnimInstance();
	if ( !IsValid( AnimInstance ) )
		return FText();

	FString       Value;
	TArray<FName> CurveNames;
	AnimInstance->GetActiveCurveNames( EAnimCurveType::AttributeCurve , CurveNames );
	for ( const FName Name : CurveNames ) {
		Value.Append( FString::SanitizeFloat( AnimInstance->GetCurveValue( Name ) ) );
		Value.Append( TEXT( "\n" ) );
	}

	return FText::FromString( Value );
}


FText ULmWHuD::GetFrameRate() const {
	return FText::FromString( FString::SanitizeFloat( FMath::Floor( 1.0f / dt ) ) );
}
