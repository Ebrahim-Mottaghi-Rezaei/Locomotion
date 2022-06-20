

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../ALSEnums.h"
#include <Engine/DataTable.h>
#include "../ALSStructs.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Components/TimelineComponent.h>
#include "ALSCharacterInterface.h"
#include "ALSCameraInterface.h"
#include "ALSBaseCharacter.generated.h"

UCLASS()
class CALSV4_API AALSBaseCharacter : public ACharacter, public IALSCharacterInterface, public IALSCameraInterface {
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AALSBaseCharacter();

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System")
		uint8 AnimationFrameRate = 30;

	//You should look it up in the GameTraceChannel in DefaultEngine.ini
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System")
		TEnumAsByte<ECollisionChannel> ECC_Climbable = ECollisionChannel::ECC_GameTraceChannel2;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System")
		TEnumAsByte<ECollisionChannel> ECC_Visibility = ECollisionChannel::ECC_Visibility;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Input", meta = (ClampMin = "0.1", ClampMax = "0.5", UIMin = "0.1", UIMax = "0.5"))
		float DoubleTapTime = 0.1f;
	///Category=Input
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Input")
		EALSInputProcessingMode SprintProcessingMode = EALSInputProcessingMode::ALS_DoublePress;

	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Input")
		EALSButtonPressType CameraActionPressType;

	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Input")
		EALSRotationMode DesiredRotationMode = EALSRotationMode::ALS_LookingDirection;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Input")
		EALSGait DesiredGait = EALSGait::ALS_Running;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Input")
		EALSStance DesiredStance = EALSStance::ALS_Standing;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Input")
		float LookUpDownRate = 1.25f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Input")
		float LookLeftRightRate = 1.25f;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Input")
		uint8 timesPressedStance = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Input")
		bool bBreakFall;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Input")
		bool bSprintHeld;

	///Category=Essential Information
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Essential Information")
		FVector Acceleration = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Essential Information")
		bool bIsMoving = false;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Essential Information")
		bool bHasMovementInput = false;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Essential Information")
		FRotator LastVelocityRotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Essential Information")
		FRotator LastMovementInputRotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Essential Information")
		float Speed = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Essential Information")
		float MovementInputAmount = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Essential Information")
		float AimYawRate = 0.0f;

	///Category=Camera System
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Camera System")
		float ThirdPersonFOV = 90.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Camera System")
		float FirstPersonFOV = 90.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Advanced Locomotion System|Camera System")
		bool bRightShoulder = true;

	///Category=State Values
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|State Values")
		EALSMovementState MovementState = EALSMovementState::ALS_None;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|State Values")
		EALSMovementState PrevMovementState = EALSMovementState::ALS_None;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|State Values")
		EALSMovementAction MovementAction = EALSMovementAction::ALS_None;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|State Values")
		EALSRotationMode RotationMode = EALSRotationMode::ALS_LookingDirection;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|State Values")
		EALSGait Gait = EALSGait::ALS_Walking;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|State Values")
		EALSStance Stance = EALSStance::ALS_Standing;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|State Values")
		EALSViewMode ViewMode = EALSViewMode::ALS_TPS;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|State Values")
		EALSOverlayState OverlayState = EALSOverlayState::ALS_Default;

	///Category=Movement System
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Movement System")
		FDataTableRowHandle MovementModel;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Movement System")
		FALSMovementSettingsState MovementData;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Movement System")
		FALSMovementSettings CurrentMovementSettings;

	///Category=Rotation System
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Rotation System")
		FRotator TargetRotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Rotation System")
		FRotator InAirRotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Rotation System")
		float YawOffset;

	///Category=Mantle System
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Mantle System")
		UCurveFloat* MantleTimelineCurve;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Mantle System")
		FALSMantleParams MantleParams;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Mantle System")
		FALSComponentAndTransform MantleLedgeLS;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Mantle System")
		FTransform MantleTarget = FTransform::Identity;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Mantle System")
		FTransform MantleActualStartOffset = FTransform::Identity;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Mantle System")
		FTransform MantleAnimatedStartOffset = FTransform::Identity;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Mantle System")
		FALSMantleTraceSettings GroundedTraceSettings;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Mantle System")
		FALSMantleTraceSettings AutomaticTraceSettings;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Mantle System")
		FALSMantleTraceSettings FallingTraceSettings;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Mantle System")
		UCurveVector* HighMantle;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Advanced Locomotion System|Mantle System")
		UCurveVector* LowMantle;

	///Category=Ragdoll
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Ragdoll System")
		bool bRagdollOnGround = false;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Ragdoll System")
		bool bRagdollFaceUp = false;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Ragdoll System")
		FVector LastRagdollVelocity = FVector::ZeroVector;

	///Category=Cached Variables
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Cached Variables")
		FVector PreviousVelocity = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "Advanced Locomotion System|Cached Variables")
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
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Utility")
		virtual FALSControlVectors GetControlVectors();
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Utility")
		virtual FVector GetCapsuleBaseLocation(float ZOffset);
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Utility")
		virtual FVector GetCapsuleLocationFromBase(FVector baseLocation, float zOffset);
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Utility")
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
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character Base|Input")
		virtual void ToggleRotationMode();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character Base|Input")
		virtual void ChangeRotationMode(EALSRotationMode newMode);
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character Base|Input")
		virtual void AimActionBegin();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character Base|Input")
		virtual void AimActionEnd();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character Base|Input")
		virtual void CameraActionBegin();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character Base|Input")
		virtual void CameraActionEnd();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character Base|Input")
		virtual void RagdollActionBegin();
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Input")
		virtual FVector GetPlayerMovementInput();
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Input")
		virtual FVector2D FixDiagonalGamePadValues(float inX, float inY);
	///Category=Essential Information
	virtual void SetEssentialValues();
	virtual void CacheValues();
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Essential Information")
		virtual FVector CalculateAcceleration();
	///Category=State Change
	virtual void OnCharacterMovementModeChanged(EMovementMode PrevMovementMode, EMovementMode NewMovementMode, uint8 PrevCustomMode, uint8 NewCustomMode);
	virtual void OnMovementStateChanged(EALSMovementState NewMovementState);
	virtual void OnMovementActionChanged(EALSMovementAction NewMovementAction);
	virtual void OnStanceChanged(EALSStance NewStance);
	virtual void OnRotationModeChanged(EALSRotationMode NewRotationMode);
	virtual void OnGaitChanged(EALSGait NewActualGait);
	virtual void OnViewModeChanged(EALSViewMode NewViewMode);
	virtual void OnOverlayStateChanged(EALSOverlayState NewOverlayState);
	///Category=Movement System
	virtual void SetMovementModel();
	virtual void UpdateCharacterMovement();
	virtual void UpdateDynamicMovementSettings(EALSGait AllowedGait);
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Movement System")
		virtual FALSMovementSettings GetTargetMovementSettings();
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Movement System")
		virtual EALSGait GetAllowedGait();
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Movement System")
		virtual EALSGait GetActualGait(EALSGait AllowedGait);
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Movement System")
		virtual bool CanSprint();
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Movement System")
		virtual float GetMappedSpeed();
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Movement System")
		virtual UAnimMontage* GetRollAnimation();
	///Rotation System
	virtual void UpdateGroundedRotation();
	virtual void UpdateInAirRotation();
	virtual void SmoothCharacterRotation(FRotator Target, float TargetInterpSpeedConst, float ActorInterpSpeedSmooth);
	virtual void AddToCharacterRotation(FRotator DeltaRotation);
	virtual void LimitRotation(float AimYawMin, float AimYawMax, float InterpSpeed);
	virtual FALSHitResult SetActorLocationRotationUpdateTarget(FVector NewLocation, FRotator NewRotation, bool bSweep, bool bTeleport);
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Rotation System")
		virtual float CalculateGroundedRotationRate();
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Rotation System")
		virtual bool CanUpdateMovingRotation();
	///Category=Mantle System
	UFUNCTION(BlueprintCallable)
		virtual bool MantleCheck(FALSMantleTraceSettings TraceSettings, TEnumAsByte<EDrawDebugTrace::Type> DebugType);
	UFUNCTION(BlueprintCallable)
		virtual void MantleStart(float MantleHeight, FALSComponentAndTransform MantleLedgeWS, EALSMantleType MantleType);
	UFUNCTION(BlueprintCallable)
		virtual void MantleUpdate(const float BlendIn);
	UFUNCTION(BlueprintCallable)
		virtual void MantleEnd();

	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Mantle System")
		virtual bool CapsuleHasRoomCheck(UCapsuleComponent* Capsule, FVector TargetLocation, float HeightOffset, float RadiusOffset, TEnumAsByte<EDrawDebugTrace::Type> DebugType);
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Mantle System")
		virtual FALSMantleAsset GetMantleAsset(EALSMantleType MantleType);
	///Category=Ragdoll System
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character Base|Ragdoll System")
		virtual void RagdollStart();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character Base|Ragdoll System")
		virtual void RagdollEnd();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character Base|Ragdoll System")
		virtual void RagdollUpdate();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character Base|Ragdoll System")
		virtual void ToggleRagdollMode();
	UFUNCTION(BlueprintCallable, Category = "Advanced Locomotion System|Character Base|Ragdoll System")
		virtual void SetActorLocationDuringRagdoll();
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Ragdoll System")
		virtual UAnimMontage* GetGetupAnimation(const bool bIsRagdollFacedUp);
	///Category=Debug
	virtual void DrawDebugShapes();
	UFUNCTION(BlueprintGetter, Category = "Advanced Locomotion System|Character Base|Debug")
		virtual TEnumAsByte<EDrawDebugTrace::Type> GetTraceDebugType(TEnumAsByte<EDrawDebugTrace::Type> showTraceType);

	///BreakFall CustomEvent
	virtual void BreakFall();
	///Roll CustomEvent
	virtual void Roll();

public:

#pragma region IALS_Character_Interface_Overrides.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Character Base|Character")
		FALSCurrentState GetCurrentState();
	virtual FALSCurrentState GetCurrentState_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Character Base|Character")
		FALSEssentialValues GetEssentialValues();
	virtual FALSEssentialValues GetEssentialValues_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Character Base|Character")
		void SetMovementState(EALSMovementState NewMovementState);
	virtual void SetMovementState_Implementation(EALSMovementState NewMovementState) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Character Base|Character")
		void SetMovementAction(EALSMovementAction NewMovementAction);
	virtual void SetMovementAction_Implementation(EALSMovementAction NewMovementAction) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Character Base|Character")
		void SetRotationMode(EALSRotationMode NewRotationMode);
	virtual void SetRotationMode_Implementation(EALSRotationMode NewRotationMode) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Character Base|Character")
		void SetGait(EALSGait NewGait);
	virtual void SetGait_Implementation(EALSGait NewGait) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Character Base|Character")
		void SetViewMode(EALSViewMode NewViewMode);
	virtual void SetViewMode_Implementation(EALSViewMode NewViewMode) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Character Base|Character")
		void SetOverlayState(EALSOverlayState NewOverlayState);
	virtual	void SetOverlayState_Implementation(EALSOverlayState NewOverlayState) override;
#pragma endregion


#pragma region IALS_Camera_Interface_Overrides.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Character Base|Camera System")
		FALSCameraParameters GetCameraParameters();
	virtual FALSCameraParameters GetCameraParameters_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Character Base|Camera System")
		FVector GetFPCameraTarget();
	virtual FVector GetFPCameraTarget_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Character Base|Camera System")
		FTransform Get3PPivotTarget();
	virtual FTransform Get3PPivotTarget_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Advanced Locomotion System|Character Base|Camera System")
		FALSTraceParams Get3PTraceParameters();
	virtual FALSTraceParams Get3PTraceParameters_Implementation() override;
#pragma endregion

private:
	float DeltaTimeX;
	TArray<AActor*> IgnoredActors;

	ETraceTypeQuery ETT_Climbable;
	ETraceTypeQuery ETT_Visibility;

	FTimeline mantleTimeline;
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
	EALSStance prevStance;
	EALSMovementAction PrevMovementAction;
	EALSRotationMode prevRotationMode;
	EALSGait prevGait;
	EALSViewMode prevViewMode;
	EALSOverlayState prevOverlayState;
	//Previous States
};
