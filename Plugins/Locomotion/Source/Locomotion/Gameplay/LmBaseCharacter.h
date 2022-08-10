

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../LmEnums.h"
#include <Engine/DataTable.h>
#include "../LmStructs.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Components/TimelineComponent.h>
#include "LmCharacterInterface.h"
#include "LmCameraInterface.h"
#include "LmBaseCharacter.generated.h"

UCLASS(Category = "Locomotion")
class LOCOMOTION_API ALmBaseCharacter : public ACharacter, public ILmCharacterInterface, public ILmCameraInterface {
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ALmBaseCharacter();

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		FName ProfileName = FName("ALS_Character");

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		UTimelineComponent* mantleTimeline;

	//You should look it up in the GameTraceChannel in DefaultEngine.ini
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		TEnumAsByte<ECollisionChannel> ECC_Climbable = ECollisionChannel::ECC_GameTraceChannel2;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion")
		TEnumAsByte<ECollisionChannel> CameraCollisionCheckChannel = ECollisionChannel::ECC_Camera;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Input", meta = (ClampMin = "0.1", ClampMax = "0.5", UIMin = "0.1", UIMax = "0.5"))
		float DoubleTapTime = 0.1f;
	///Category=Input
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Input")
		ELmInputProcessingMode SprintProcessingMode;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Input")
		ELmButtonPressType CameraActionPressType;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Input")
		ELmRotationMode DesiredRotationMode = ELmRotationMode::Lm_LookingDirection;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Input")
		ELmGait DesiredGait = ELmGait::Lm_Running;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Input")
		ELmStance DesiredStance = ELmStance::Lm_Standing;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Input")
		float LookUpDownRate = 1.25f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Input")
		float LookLeftRightRate = 1.25f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Input")
		uint8 timesPressedStance = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Input")
		bool bBreakFall;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Input")
		bool bSprintHeld;

	///Category=Essential Information
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		FVector Acceleration = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		bool bIsMoving = false;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		bool bHasMovementInput = false;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		FRotator LastVelocityRotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		FRotator LastMovementInputRotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		float Speed = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		float MovementInputAmount = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|General")
		float AimYawRate = 0.0f;

	///Category=Camera System
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Camera")
		float ThirdPersonFOV = 90.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Camera")
		float FirstPersonFOV = 90.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Camera")
		bool bRightShoulder = true;

	///Category=State Values
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|State Values")
		ELmMovementState MovementState = ELmMovementState::Lm_None;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|State Values")
		ELmMovementState PrevMovementState = ELmMovementState::Lm_None;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|State Values")
		ELmMovementAction MovementAction = ELmMovementAction::Lm_None;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|State Values")
		ELmRotationMode RotationMode = ELmRotationMode::Lm_LookingDirection;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|State Values")
		ELmGait Gait = ELmGait::Lm_Walking;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|State Values")
		ELmStance Stance = ELmStance::Lm_Standing;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|State Values")
		ELmViewMode ViewMode = ELmViewMode::Lm_TPS;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Locomotion")
		ELmOverlayState OverlayState = ELmOverlayState::Lm_Default;

	///Category=Movement System
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Movement")
		FDataTableRowHandle MovementModel;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Movement")
		FLmMovementSettingsState MovementData;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Movement")
		FLmMovementSettings CurrentMovementSettings;

	///Category=Rotation System
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Rotation System")
		FRotator TargetRotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Rotation System")
		FRotator InAirRotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Rotation System")
		float YawOffset;

	///Category=Mantle System
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Mantle")
		UCurveFloat* MantleTimelineCurve;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Mantle")
		FLmMantleParams MantleParams;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Mantle")
		FLmComponentAndTransform MantleLedgeLS;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Mantle")
		FTransform MantleTarget = FTransform::Identity;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Mantle")
		FTransform MantleActualStartOffset = FTransform::Identity;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Mantle")
		FTransform MantleAnimatedStartOffset = FTransform::Identity;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Mantle")
		FLmMantleTraceSettings GroundedTraceSettings;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Mantle")
		FLmMantleTraceSettings AutomaticTraceSettings;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Mantle")
		FLmMantleTraceSettings FallingTraceSettings;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Mantle")
		UCurveVector* HighMantle;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Locomotion|Mantle")
		UCurveVector* LowMantle;

	///Category=Ragdoll
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Ragdoll")
		bool bRagdollOnGround = false;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Ragdoll")
		bool bRagdollFaceUp = false;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Ragdoll")
		FVector LastRagdollVelocity = FVector::ZeroVector;

	///Category=Cached Variables
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Cached Vars")
		FVector PreviousVelocity = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "Locomotion|Cached Vars")
		float PreviousAimYaw = 0.0f;

	/// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;
	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void OnJumped_Implementation() override;
protected:
	///Category=Utility
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Utility")
		virtual FLmControlVectors GetControlVectors();
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Utility")
		virtual FVector GetCapsuleBaseLocation(float ZOffset);
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Utility")
		virtual FVector GetCapsuleLocationFromBase(FVector baseLocation, float zOffset);
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Utility")
		virtual float GetAnimCurveValue(FName curveName);
	///Category=Input
	void ReceiveMoveForwardBackwards(float value);
	void ReceiveMoveRightLeft(float value);
	virtual void PlayerMovementInput(const bool bIsForwardAxis);
	virtual void PlayerCameraYawInput(float value);
	virtual void PlayerCameraPitchInput(float value);
	virtual void PlayerJumpPressedInput();
	virtual void PlayerStanceActionInput(FKey key);
	virtual void PlayerWalkBegin();
	virtual void PlayerWalkEnd();
	virtual void PlayerSprintBegin();
	virtual void PlayerSprintEnd();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Input")
		virtual void ToggleRotationMode();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Input")
		virtual void ChangeRotationMode(ELmRotationMode newMode);
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Input")
		virtual void AimActionBegin();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Input")
		virtual void AimActionEnd();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Input")
		virtual void CameraActionBegin();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Input")
		virtual void CameraActionEnd();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Input")
		virtual void RagdollActionBegin();
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Input")
		virtual FVector GetPlayerMovementInput();
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Input")
		virtual FVector2D FixDiagonalGamePadValues(float inX, float inY);
	///Category=Essential Information
	virtual void SetEssentialValues();
	virtual void CacheValues();
	UFUNCTION(BlueprintGetter, Category = "Locomotion|General")
		virtual FVector CalculateAcceleration();
	///Category=State Change
	virtual void OnCharacterMovementModeChanged(EMovementMode PrevMovementMode, EMovementMode NewMovementMode, uint8 PrevCustomMode, uint8 NewCustomMode);
	virtual void OnMovementStateChanged(ELmMovementState NewMovementState);
	virtual void OnMovementActionChanged(ELmMovementAction NewMovementAction);
	virtual void OnStanceChanged(ELmStance NewStance);
	virtual void OnRotationModeChanged(ELmRotationMode NewRotationMode);
	virtual void OnGaitChanged(ELmGait NewActualGait);
	virtual void OnViewModeChanged(ELmViewMode NewViewMode);
	virtual void OnOverlayStateChanged(ELmOverlayState NewOverlayState);
	///Category=Movement System
	virtual void SetMovementModel();
	virtual void UpdateCharacterMovement();
	virtual void UpdateDynamicMovementSettings(ELmGait AllowedGait);
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Movement")
		virtual FLmMovementSettings GetTargetMovementSettings();
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Movement")
		virtual ELmGait GetAllowedGait();
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Movement")
		virtual ELmGait GetActualGait(ELmGait AllowedGait);
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Movement")
		virtual bool CanSprint();
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Movement")
		virtual float GetMappedSpeed();
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Movement")
		virtual UAnimMontage* GetRollAnimation();
	///Rotation System
	virtual void UpdateGroundedRotation();
	virtual void UpdateInAirRotation();
	virtual void SmoothCharacterRotation(FRotator Target, float TargetInterpSpeedConst, float ActorInterpSpeedSmooth);
	virtual void LimitRotation(float AimYawMin, float AimYawMax, float InterpSpeed);
	virtual FLmHitResult SetActorLocationRotationUpdateTarget(FVector NewLocation, FRotator NewRotation, bool bSweep, bool bTeleport);
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Rotation System")
		virtual float CalculateGroundedRotationRate();
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Rotation System")
		virtual bool CanUpdateMovingRotation();
	///Category=Mantle System
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Mantle")
		virtual bool MantleCheck(FLmMantleTraceSettings TraceSettings, TEnumAsByte<EDrawDebugTrace::Type> DebugType);
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Mantle")
		virtual void MantleStart(float MantleHeight, FLmComponentAndTransform MantleLedgeWS, ELmMantleType MantleType);
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Mantle")
		virtual void MantleUpdate(const float BlendIn);
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Mantle")
		virtual void MantleEnd();

	UFUNCTION(BlueprintGetter, Category = "Locomotion|Mantle")
		virtual bool CapsuleHasRoomCheck(UCapsuleComponent* Capsule, FVector TargetLocation, float HeightOffset, float RadiusOffset, TEnumAsByte<EDrawDebugTrace::Type> DebugType);
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Mantle")
		virtual FLmMantleAsset GetMantleAsset(ELmMantleType MantleType);
	///Category=Ragdoll System
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Ragdoll")
		virtual void RagdollStart();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Ragdoll")
		virtual void RagdollEnd();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Ragdoll")
		virtual void RagdollUpdate();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Ragdoll")
		virtual void ToggleRagdollMode();
	UFUNCTION(BlueprintCallable, Category = "Locomotion|Ragdoll")
		virtual void SetActorLocationDuringRagdoll();
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Ragdoll")
		virtual UAnimMontage* GetGetupAnimation(const bool bIsRagdollFacedUp);
	///Category=Debug
	virtual void DrawDebugShapes();
	UFUNCTION(BlueprintGetter, Category = "Locomotion|Debug")
		virtual TEnumAsByte<EDrawDebugTrace::Type> GetTraceDebugType(TEnumAsByte<EDrawDebugTrace::Type> showTraceType);

	///BreakFall CustomEvent
	virtual void BreakFall();
	///Roll CustomEvent
	virtual void Roll();

public:

#pragma region IALS_Character_Interface_Overrides.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Character")
		FLmCurrentState GetCurrentState();
	virtual FLmCurrentState GetCurrentState_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Character")
		FLmEssentialValues GetEssentialValues();
	virtual FLmEssentialValues GetEssentialValues_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Character")
		void SetMovementState(ELmMovementState NewMovementState);
	virtual void SetMovementState_Implementation(ELmMovementState NewMovementState) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Character")
		void SetMovementAction(ELmMovementAction NewMovementAction);
	virtual void SetMovementAction_Implementation(ELmMovementAction NewMovementAction) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Character")
		void SetRotationMode(ELmRotationMode NewRotationMode);
	virtual void SetRotationMode_Implementation(ELmRotationMode NewRotationMode) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Character")
		void SetGait(ELmGait NewGait);
	virtual void SetGait_Implementation(ELmGait NewGait) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Character")
		void SetViewMode(ELmViewMode NewViewMode);
	virtual void SetViewMode_Implementation(ELmViewMode NewViewMode) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Character")
		void SetOverlayState(ELmOverlayState NewOverlayState);
	virtual	void SetOverlayState_Implementation(ELmOverlayState NewOverlayState) override;
#pragma endregion


#pragma region IALS_Camera_Interface_Overrides.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Camera")
		FLmCameraParameters GetCameraParameters();
	virtual FLmCameraParameters GetCameraParameters_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Camera")
		FVector GetFPCameraTarget();
	virtual FVector GetFPCameraTarget_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Camera")
		FTransform Get3PPivotTarget();
	virtual FTransform Get3PPivotTarget_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Locomotion|Camera")
		FLmTraceParams Get3PTraceParameters();
	virtual FLmTraceParams Get3PTraceParameters_Implementation() override;
#pragma endregion

protected:
	TEnumAsByte<ETraceTypeQuery> ETT_CameraCollisionChannel;
private:
	TEnumAsByte<ETraceTypeQuery> ETT_Climbable;

	TArray<AActor*> IgnoredActors;

	UAnimInstance* animInstance;

	FTimerHandle timerHandle_Landing;

	FTimerHandle StanceAction_th;
	uint8 StanceActionInputCounter;

	FTimerHandle ResetBreakFall_th;

	uint8 SprintTapCounter;
	FTimerHandle Sprint_Handle;

	FTimerHandle cameraAction_th;

	float forwardInputValue;
	float rightInputValue;


	//Previous States
	ELmStance prevStance;
	ELmMovementAction PrevMovementAction;
	ELmRotationMode prevRotationMode;
	ELmGait prevGait;
	ELmViewMode prevViewMode;
	ELmOverlayState prevOverlayState;
	//Previous States
};