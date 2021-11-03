#pragma once

#include "CoreMinimal.h"
#include "CALSv4/Core/Interfaces/ALSCameraInterface.h"
#include "CALSv4/Core/Interfaces/ALSCharacterInterface.h"
#include "CALSv4/Data/ALSStructs.h"
#include "Components/TimelineComponent.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ALSBaseCharacter.generated.h"

UCLASS()
class CALSV4_API AALSBaseCharacter : public ACharacter, public IALSCameraInterface, public IALSCharacterInterface {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AALSBaseCharacter();

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS")
		uint8 AnimationFrameRate = 30.0;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Input")
		float LookUpDownRate = 1.25f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Input")
		float LookLeftRightRate = 1.25f;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "C++ ALS|Input")
		float CurrentForwardInput;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "C++ ALS|Input")
		float CurrentRightInput;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Movement System")
		FDataTableRowHandle MovementModel;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Movement System")
		FALSMovementSettings CurrentMovementSettings;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Mantle System")
		FALSMantleTraceSettings AutomaticTraceSettings;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Mantle System")
		FALSMantleTraceSettings GroundedTraceSettings;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Mantle System")
		FALSMantleTraceSettings FallingTraceSettings;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Mantle System")
		UCurveVector* HighMantle;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "C++ ALS|Mantle System")
		UCurveVector* LowMantle;
private:
	FTimeline mantleTimeline;
	UAnimInstance* animInstance;
	FTimerHandle timerHandle_ResetBrakingFactor;

	//Category=Input
	EALSRotationMode DesiredRotationMode = EALSRotationMode::ALS_LookingDirection;
	EALSGait DesiredGait = EALSGait::ALS_Running;
	EALSStance DesiredStance = EALSStance::ALS_Standing;
	uint8 timesPressedStance;
	bool bBreakFall;
	bool bSprintHeld;
	//Category=Essential Information
	FVector Acceleration;
	bool bIsMoving;
	bool bHasMovementInput;
	FRotator LastVelocityRotation;
	FRotator LastMovementInputRotation;
	float Speed;
	float MovementInputAmount;
	float AimYawRate;

	//Category=Camera System
	float ThirdPersonFOV = 90.0f;
	float FirstPersonFOV = 90.0f;
	bool bRightShoulder;

	//Category=State Values
	EALSMovementState MovementState = EALSMovementState::ALS_None;
	EALSMovementState PrevMovementState = EALSMovementState::ALS_None;
	EALSMovementAction MovementAction = EALSMovementAction::ALS_None;
	EALSRotationMode RotationMode = EALSRotationMode::ALS_LookingDirection;
	EALSGait Gait = EALSGait::ALS_Walking;
	EALSStance Stance = EALSStance::ALS_Standing;
	EALSViewMode ViewMode = EALSViewMode::ALS_TPS;
	EALSOverlayState OverlayState = EALSOverlayState::ALS_Default;

	//Category=Movement System
	FALSMovementSettingsState MovementData;

	//Category=Rotation System
	FRotator TargetRotation;
	FRotator InAirRotation;
	float YawOffset;

	//Category=Mantle System
	FALSMantleParams MantleParams;
	FALSComponentAndTransform MantleLedgeLS;
	FTransform MantleTarget;
	FTransform MantleActualStartOffset;
	FTransform MantleAnimatedStartOffset;

	//Category=Ragdoll
	bool bRagdollOnGround;
	bool bRagdollFaceUp;
	FVector LastRagdollVelocity;

	//Category=Cached Variables
	FVector PreviousVelocity;
	float PreviousAimYaw;

	//Used in code
	float frameDeltaTime;
	TArray<AActor*> ignoredActors;
	ETraceTypeQuery ECC_Climbable;

	// Called when the game starts or when spawned
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
	//Category=Utility
	virtual FALSControlVectors GetControlVectors();
	virtual FVector GetCapsuleBaseLocation(float ZOffset);
	virtual FVector GetCapsuleLocationFromBase(FVector baseLocation, float zOffset);
	virtual float GetAnimCurveValue(FName curveName);
	//Category=Input
	void ReceiveMoveForwardBackwards(float value);
	void ReceiveMoveRightLeft(float value);
	virtual void PlayerMovementInput(const bool bIsForwardAxis);
	virtual void PlayerCameraYawInput(float value);
	virtual void PlayerCameraPitchInput(float value);
	virtual void PlayerJumpPressedInput(FKey key);
	virtual void PlayerStanceActionInput(FKey key);
	virtual FVector GetPlayerMovementInput();
	virtual FVector2D FixDiagonalGamePadValues(float inX, float inY);
	//Category=Essential Information
	virtual void SetEssentialValues();
	virtual void CacheValues();
	virtual FVector CalculateAcceleration();
	//Category=State Change
	virtual void OnBeginPlay();
	virtual void OnCharacterMovementModeChanged(EMovementMode PrevMovementMode, EMovementMode NewMovementMode, uint8 PrevCustomMode, uint8 NewCustomMode);
	virtual void OnMovementStateChanged(EALSMovementState NewMovementState);
	virtual void OnMovementActionChanged(EALSMovementAction NewMovementAction);
	virtual void OnStanceChanged(EALSStance NewStance);
	virtual void OnRotationModeChanged(EALSRotationMode NewRotationMode);
	virtual void OnGaitChanged(EALSGait NewActualGait);
	virtual void OnViewModeChanged(EALSViewMode NewViewMode);
	virtual void OnOverlayStateChanged(EALSOverlayState NewOverlayState);
	//Category=Movement System
	virtual void SetMovementModel();
	virtual void UpdateCharacterMovement();
	virtual void UpdateDynamicMovementSettings(EALSGait AllowedGait);
	virtual FALSMovementSettings GetTargetMovementSettings();
	virtual EALSGait GetAllowedGait();
	virtual EALSGait GetActualGait(EALSGait AllowedGait);
	virtual bool CanSprint();
	virtual float GetMappedSpeed();
	virtual UAnimMontage* GetRollAnimation();
	//Rotation System
	virtual void UpdateGroundedRotation();
	virtual void UpdateInAirRotation();
	virtual void SmoothCharacterRotation(FRotator Target, float TargetInterpSpeedConst, float ActorInterpSpeedSmooth);
	virtual void AddToCharacterRotation(FRotator DeltaRotation);
	virtual void LimitRotation(float AimYawMin, float AimYawMax, float InterpSpeed);
	virtual FALSHitResult SetActorLocationRotationUpdateTarget(FVector NewLocation, FRotator NewRotation, bool bSweep, bool bTeleport);
	virtual float CalculateGroundedRotationRate();
	virtual bool CanUpdateMovingRotation();
	//Category=Mantle System
	virtual bool MantleCheck(FALSMantleTraceSettings TraceSettings, TEnumAsByte<EDrawDebugTrace::Type> DebugType);
	virtual void MantleStart(float MantleHeight, FALSComponentAndTransform MantleLedgeWS, EALSMantleType MantleType);
	virtual void MantleEnd();
	virtual  void MantleUpdate(float BlendIn);
	virtual bool CapsuleHasRoomCheck(UCapsuleComponent* Capsule, FVector TargetLocation, float HeightOffset, float RadiusOffset, TEnumAsByte<EDrawDebugTrace::Type> DebugType);
	virtual FALSMantleAsset GetMantleAsset(EALSMantleType MantleType);
	//Category=Ragdoll System
	virtual void RagdollStart();
	virtual void RagdollEnd();
	virtual void RagdollUpdate();
	virtual void SetActorLocationDuringRagdoll();
	virtual UAnimMontage* GetGetupAnimation(const bool bIsRagdollFacedUp);
	//Category=Debug
	virtual void DrawDebugShapes();
	virtual TEnumAsByte<EDrawDebugTrace::Type> GetTraceDebugType(TEnumAsByte<EDrawDebugTrace::Type> showTraceType);

	//Custom Events
	virtual void BreakFall();
	virtual void Roll();

	//IALSCharacter Interface Implementations
	virtual void SetMovementState_Implementation(EALSMovementState NewMovementState) override;
	virtual void SetMovementAction_Implementation(EALSMovementAction NewMovementAction) override;
	virtual void SetRotationMode_Implementation(EALSRotationMode NewRotationMode) override;
	virtual void SetGait_Implementation(EALSGait NewGait) override;
	virtual void SetViewMode_Implementation(EALSViewMode NewViewMode) override;
	virtual void SetOverlayState_Implementation(EALSOverlayState NewOverlayState) override;

	//
	virtual void ResetBrakingFrictionTimer();
	virtual void ResetPressCounterTimer(uint8& counter);
};