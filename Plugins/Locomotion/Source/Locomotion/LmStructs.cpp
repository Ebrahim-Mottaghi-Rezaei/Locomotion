

#include "LmStructs.h"
#include "LmLogger.h"
#include "LmHelpers.h"
#include <GameFramework/Character.h>
#include <UObject/UObjectBaseUtility.h>
#include <Animation/AnimMontage.h>

FLmComponentAndTransform::FLmComponentAndTransform() {
	Component = nullptr;
	Transform = FTransform();
}

FLmComponentAndTransform::FLmComponentAndTransform(FTransform transform, UPrimitiveComponent* component) {
	Transform = transform;
	Component = component;
}

FString FLmComponentAndTransform::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Component Name: %s, Transform: %s"), *Component->GetName(), *Transform.ToString());

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FLmDynamicMontageParams::FLmDynamicMontageParams() {
	Animation = nullptr;
	BlendInTime = 0.0f;
	BlendOutTime = 0.0f;
	PlayRate = 0.0f;
	StartTime = 0.0f;
}

FLmDynamicMontageParams::FLmDynamicMontageParams(UAnimSequenceBase* animation, float blendInTime, float blendOutTime, float playRate, float startTime) {
	Animation = animation;
	BlendInTime = blendInTime;
	BlendOutTime = blendOutTime;
	PlayRate = playRate;
	StartTime = startTime;
}

FString FLmDynamicMontageParams::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Animation: %s, PlayRate: %s, StartTime: %s, Blend=[In: %s, Out: %s]"),
		*Animation->GetName(), *FString::SanitizeFloat(PlayRate), *FString::SanitizeFloat(StartTime), *FString::SanitizeFloat(BlendInTime), *FString::SanitizeFloat(BlendOutTime));

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FLmLeanAmount::FLmLeanAmount() {
	FrontBack = 0.0f;
	LeftRight = 0.0f;
}

FLmLeanAmount::FLmLeanAmount(float FB, float LR) {
	FrontBack = FB;
	LeftRight = LR;
}

FString FLmLeanAmount::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Lean | FrontBack: %s, RightLeft: %s"), *FString::SanitizeFloat(FrontBack), *FString::SanitizeFloat(LeftRight));

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FLmMantleAsset::FLmMantleAsset() : AnimMontage(nullptr), PositionCorrectionCurve(nullptr), LowHeight(0), LowPlayRate(0), LowStartPosition(0), HighHeight(0), HighPlayRate(0), HighStartPosition(0) {}

FLmMantleAsset::FLmMantleAsset(UAnimMontage* AnimMontage, UCurveVector* PositionCorrectionCurve,
	const FVector StartingOffset, const float LowHeight, const float LowPlayRate, const float LowStartPosition, const float HighHeight,
	const float HighPlayRate, const float HighStartPosition) {
	this->AnimMontage = AnimMontage;
	this->PositionCorrectionCurve = PositionCorrectionCurve;
	this->StartingOffset = StartingOffset;
	this->LowHeight = LowHeight;
	this->LowPlayRate = LowPlayRate;
	this->LowStartPosition = LowStartPosition;
	this->HighHeight = HighHeight;
	this->HighPlayRate = HighPlayRate;
	this->HighStartPosition = HighStartPosition;
}

FString FLmMantleAsset::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("AnimMontage: %s, PositionCorrectionCurve: %s,\nStartingOffset: %s,Height: [Low: %s, High: %s], PlayRate: [Low: %s, High: %s], StaringPosition: [Low: %s , High: %s]"), *AnimMontage->GetName(), *PositionCorrectionCurve->GetName(), *StartingOffset.ToString(), *FString::SanitizeFloat(LowHeight), *FString::SanitizeFloat(HighHeight), *FString::SanitizeFloat(LowPlayRate), *FString::SanitizeFloat(HighPlayRate), *FString::SanitizeFloat(LowStartPosition), *FString::SanitizeFloat(HighStartPosition));

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FLmMantleParams::FLmMantleParams() {
	PlayRate = 1.0f;
}

FLmMantleParams::FLmMantleParams(UAnimMontage* animMontage, UCurveVector* positionCorrectionCurve, float startingPosition, FVector startingOffset, float playRate) {
	AnimMontage = animMontage;
	PositionCorrectionCurve = positionCorrectionCurve;
	StartingOffset = startingOffset;
	StartingPosition = startingPosition;
	PlayRate = playRate;
}

FString FLmMantleParams::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("AnimMontage: %s, PositionCorrectionCurve: %s, StatingOffset: %s, StatingPosition: %s, PlayRate: %s"), *AnimMontage->GetName(), *PositionCorrectionCurve->GetName(), *StartingOffset.ToString(), *FString::SanitizeFloat(StartingPosition), *FString::SanitizeFloat(PlayRate));

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FLmTurnInPlaceAsset::FLmTurnInPlaceAsset() : AnimatedAngle(0), PlayRate(0), ScaleTurnAngle(0) {
	Animation = nullptr;
}

FString FLmTurnInPlaceAsset::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Animation: %s, Slot Name: %s, AnimatedAngle: %s, PlayRate: %s, ScaleTurnAngle: %s"), *Animation->GetName(), *SlotName.ToString(), *FString::SanitizeFloat(AnimatedAngle), *FString::SanitizeFloat(PlayRate), *ULmHelpers::Bool2String(ScaleTurnAngle));

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FLmVelocityBlend::FLmVelocityBlend() : F(0.0f), B(0.0f), L(0.0f), R(0.0f) {}

FLmVelocityBlend::FLmVelocityBlend(const float f, const float b, const float l, const float r) : F(f), B(b), L(l), R(r) {}

FString FLmVelocityBlend::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Front: %s, Back: %s, Right: %s, Left: %s"), *FString::SanitizeFloat(F), *FString::SanitizeFloat(B), *FString::SanitizeFloat(R), *FString::SanitizeFloat(L));

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FLmCurrentState::FLmCurrentState() {
	PawnMovementMode = MOVE_None;
}

FString FLmCurrentState::ToString(bool bPrintToLog) {

	const auto r = FString::Printf(TEXT("MovementMode: %s, MovementState: %s, PrevMovementState: %s, MovementAction: %s, RotationMode: %s, ActualGait: %s, ActualStance: %s, ViewMode: %s, OverlayState: %s"),
		*UEnum::GetValueAsString(PawnMovementMode),
		*UEnum::GetValueAsString(MovementState),
		*UEnum::GetValueAsString(PrevMovementState),
		*UEnum::GetValueAsString(MovementAction),
		*UEnum::GetValueAsString(RotationMode),
		*UEnum::GetValueAsString(ActualGait),
		*UEnum::GetValueAsString(ActualStance),
		*UEnum::GetValueAsString(ViewMode),
		*UEnum::GetValueAsString(OverlayState));

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;

}

FLmEssentialValues::FLmEssentialValues() : bIsMoving(false), bHasMovementInput(false), Speed(0),
MovementInputAmount(0), AimYawRate(0) {}

FLmEssentialValues::FLmEssentialValues(const FVector velocity, const FVector acceleration, const FVector movementInput, const bool isMoving, const bool hasMovementInput, const float speed, const float movementInputAmount, const FRotator aimingRotation, const float aimYawRate) {
	Velocity = velocity;
	Acceleration = acceleration;
	AimingRotation = aimingRotation;
	MovementInput = movementInput;
	Speed = speed;
	MovementInputAmount = movementInputAmount;
	AimYawRate = aimYawRate;
	bIsMoving = isMoving;
	bHasMovementInput = hasMovementInput;
}

FString FLmEssentialValues::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Velocity: %ls \nAcceleration: %ls,\nAimingRotation: %ls\nMovementInput: %ls\nSpeed: %f\nMovementInputAmount: %f\nAimYawRate: %f\nIsMoving: %ls\nHasMovementInput: %ls\n"), *Velocity.ToString(), *Acceleration.ToString(), *AimingRotation.ToString(), *MovementInput.ToString(), Speed, MovementInputAmount, AimYawRate, *ULmHelpers::Bool2String(bIsMoving), *ULmHelpers::Bool2String(bHasMovementInput));

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FLmDebugInfo::FLmDebugInfo() {
	DebugFocusCharacter = nullptr;
}

FLmDebugInfo::FLmDebugInfo(ACharacter* FocusedDebugCharacter, const bool DebugView, const bool ShowHUD, const bool ShowTraces,
	const bool ShowDebugShapes, const bool ShowLayerColors, const bool SlowMotion, const bool ShowCharacterInfo) {
	DebugFocusCharacter = FocusedDebugCharacter;
	bDebugView = DebugView;
	bShowHUD = ShowHUD;
	bShowTraces = ShowTraces;
	bShowDebugShapes = ShowDebugShapes;
	bShowLayerColors = ShowLayerColors;
	bSlowMotion = SlowMotion;
	bShowCharacterInfo = ShowCharacterInfo;
}

FString FLmDebugInfo::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Debugging Character: %s, DebugView: %s, HUD: %s, Traces: %s, Debug Shapes: %s, Layer Colors: %s, Slow Motion: %s, Character Info: %s"),
		*DebugFocusCharacter->GetName(),
		*ULmHelpers::Bool2String(bDebugView, TEXT("Enabled"), TEXT("Disabled")),
		*ULmHelpers::Bool2String(bShowHUD, TEXT("Enabled"), TEXT("Disabled")),
		*ULmHelpers::Bool2String(bShowTraces, TEXT("Enabled"), TEXT("Disabled")),
		*ULmHelpers::Bool2String(bShowDebugShapes, TEXT("Enabled"), TEXT("Disabled")),
		*ULmHelpers::Bool2String(bShowLayerColors, TEXT("Enabled"), TEXT("Disabled")),
		*ULmHelpers::Bool2String(bSlowMotion, TEXT("Enabled"), TEXT("Disabled")),
		*ULmHelpers::Bool2String(bShowCharacterInfo, TEXT("Enabled"), TEXT("Disabled"))
	);

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FLmCameraParameters::FLmCameraParameters() {
	TP_FOV = 0;
	FP_FOV = 0;
	bRightShoulder = true;
}

FLmCameraParameters::FLmCameraParameters(float tP_FOV, float fp_FOV, bool rightShoulder) {
	TP_FOV = tP_FOV;
	FP_FOV = fp_FOV;
	bRightShoulder = rightShoulder;
}

FString FLmCameraParameters::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("TP FOV: %s, FP FOV: %s, Cam Shoulder? %s"), *FString::SanitizeFloat(TP_FOV), *FString::SanitizeFloat(FP_FOV), *ULmHelpers::Bool2String(bRightShoulder, TEXT("Right"), TEXT("Left")));

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FLmTraceParams::FLmTraceParams() {
	TraceChannel = TraceTypeQuery1;
	TraceOrigin = FVector();
	TraceRadius = 10.0f;
}

FLmTraceParams::FLmTraceParams(TEnumAsByte<ETraceTypeQuery> traceChannel, FVector traceOrigin, float traceRadius) {
	TraceChannel = traceChannel;
	TraceOrigin = traceOrigin;
	TraceRadius = traceRadius;
}

FString FLmTraceParams::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Trace Channel: %s, Trace Origin: %s, Trace Radius: %s"), *UEnum::GetValueAsString(TraceChannel), *TraceOrigin.ToString(), *FString::SanitizeFloat(TraceRadius));

	if (bPrintToLog)
		ULmLogger::LogInfo(r, 0.0f);

	return r;
}

FLmCameraResult::FLmCameraResult() {
	Location = FVector::ZeroVector;
	Rotation = FRotator::ZeroRotator;
	FOV = 0.0f;
}

FLmCameraResult::FLmCameraResult(const FVector location, const  FRotator rotation, const  float fov) {
	Location = location;
	Rotation = rotation;
	FOV = fov;
}

FString FLmCameraResult::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Location: %s, Rotation: %s , FOV: %s"), *Location.ToString(), *Rotation.ToString(), *FString::SanitizeFloat(FOV));

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FLmControlVectors::FLmControlVectors() {}

FLmControlVectors::FLmControlVectors(const FVector forward, const FVector right) : Forward(forward), Right(right) {}

FString FLmControlVectors::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("[Forward= %s, Right= %s]"), *Forward.ToString(), *Right.ToString());

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FString FLmHitResult::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("bHit: %s, bBlockingHit: %s, bStartPenetrating: %s, Hit Component Name: %s, Distance: %s"), *ULmHelpers::Bool2String(bHit), *ULmHelpers::Bool2String(SweepHitResult.bBlockingHit), *ULmHelpers::Bool2String(SweepHitResult.bStartPenetrating), *SweepHitResult.Component->GetName(), *FString::SanitizeFloat(SweepHitResult.Distance));

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

//FLmFootLock::FLmFootLock() {}
//
//FLmFootLock::FLmFootLock(float alpha, FVector location, FRotator rotation) {
//	Alpha = alpha;
//	LocRot = FTransform(rotation, location, FVector(1.0f, 1.0f, 1.0f));
//}

FString FLmRotateInPlaceAsset::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Animation: %s, SlotName: %s, TurnRate: [Slow= %s, Fast= %s], PlayRateRange: [Slow= %s, Fast= %s]"), *Animation->GetName(), *SlotName.ToString(), *FString::SanitizeFloat(SlowTurnRate), *FString::SanitizeFloat(FastTurnRate), *FString::SanitizeFloat(SlowPlayRate), *FString::SanitizeFloat(FastPlayRate));

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FString FLmCameraSettings::ToString(bool bPrintToLog) {

	const auto r = FString::Printf(TEXT("TargetArmLength: %s, SocketOffset: %s, LagSpeed: %s, RotationLagSpeed: %s, DoCollitionTest: %s"),
		*FString::SanitizeFloat(TargetArmLength), *SocketOffset.ToString(), *FString::SanitizeFloat(LagSpeed), *FString::SanitizeFloat(RotationLagSpeed), *ULmHelpers::Bool2String(DoCollisionTest));

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FString FLmCameraSettingsGait::ToString(bool bPrintToLog) {

	const auto r = FString::Printf(TEXT("Walking: %s\nRunning: %s\nSprinting: %s\nCrouching: %s"), *Walking.ToString(), *Running.ToString(), *Sprinting.ToString(), *Crouching.ToString());

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FString FLmCameraSettingsState::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Velocity Direction: %s\nLooking Direction: %s\nAiming: %s"), *VelocityDirection.ToString(), *LookingDirection.ToString(), *Aiming.ToString());

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FString FLmMantleTraceSettings::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Ledge Height= [Min: %s ,Max: %s], TraceRadius= [Forward: %s, Downward: %s], Reach Distance: %s"), *FString::SanitizeFloat(MinLedgeHeight), *FString::SanitizeFloat(MaxLedgeHeight), *FString::SanitizeFloat(ForwardTraceRadius), *FString::SanitizeFloat(DownwardTraceRadius), *FString::SanitizeFloat(ReachDistance));

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FString FLmMovementSettings::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Speeds= [Walk: %s, Run: %s, Sprint: %s], MovementCurve: %s, Rotation RateCurve: %s"), *FString::SanitizeFloat(WalkSpeed), *FString::SanitizeFloat(RunSpeed), *FString::SanitizeFloat(SprintSpeed), *MovementCurve->GetName(), *RotationRateCurve->GetName());

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FString FLmMovementSettingsStance::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Standing: %s, Crouching: %s"), *Standing.ToString(), *Crouching.ToString());

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FString FLmMovementSettingsState::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Velocity Direction: %s, Looking Direction: %s, AimingDirection: %s"), *VelocityDirection.ToString(), *LookingDirection.ToString(), *Aiming.ToString());

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FLmFootLock::FLmFootLock() {}

FLmFootLock::FLmFootLock(FVector location, FRotator rotation, float alpha) {
	Alpha = alpha;
	Location = location;
	Rotation = rotation;
}

FString FLmFootLock::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Alpha: %s ,Loc: %s , Rot: %s"), *FString::SanitizeFloat(Alpha), *Location.ToString(), *Rotation.ToString());

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;
}

FLmFootOffset::FLmFootOffset() {}

FLmFootOffset::FLmFootOffset(FVector target_location, FVector offset_location, FRotator offset_rotation) {
	LocationTarget = target_location;
	LocationOffset = offset_location;
	RotationOffset = offset_rotation;
}

FString FLmFootOffset::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("OffsetLoc: %s , OffsetRot: %s, TargetLoc: %s"), *LocationOffset.ToString(), *RotationOffset.ToString(), *LocationTarget.ToString());

	if (bPrintToLog)
		ULmLogger::LogInfo(r);

	return r;

}
