#pragma once

#include "ALSStructs.h"
#include "ALSLogger.h"
#include "ALSHelpers.h"
#include <GameFramework/Character.h>
#include <UObject/UObjectBaseUtility.h>

FALSComponentAndTransform::FALSComponentAndTransform() {
	Component = nullptr;
	Transform = FTransform();
}

FALSComponentAndTransform::FALSComponentAndTransform(FTransform transform, UPrimitiveComponent* component) {
	Transform = transform;
	Component = component;
}

FString FALSComponentAndTransform::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Component Name: %s, Transform: %s"), *Component->GetName(), *Transform.ToString());

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FALSDynamicMontageParams::FALSDynamicMontageParams() : Animation(nullptr), BlendInTime(0), BlendOutTime(0), PlayRate(0), StartTime(0) {}

FALSDynamicMontageParams::FALSDynamicMontageParams(UAnimSequenceBase* animation, float blendInTime, float blendOutTime,
	float playRate, float startTime) {
	Animation = animation;
	BlendInTime = blendInTime;
	BlendOutTime = blendOutTime;
	PlayRate = playRate;
	StartTime = startTime;
}

FString FALSDynamicMontageParams::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Animation: %s, PlayRate: %s, StartTime: %s, Blend=[In: %s, Out: %s]"),
		*Animation->GetName(), *FString::SanitizeFloat(PlayRate), *FString::SanitizeFloat(StartTime), *FString::SanitizeFloat(BlendInTime), *FString::SanitizeFloat(BlendOutTime));

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FALSLeanAmount::FALSLeanAmount() {
	FrontBack = 0.0f;
	LeftRight = 0.0f;
}

FALSLeanAmount::FALSLeanAmount(float FB, float LR) {
	FrontBack = FB;
	LeftRight = LR;
}

FString FALSLeanAmount::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Lean | FrontBack: %s, RightLeft: %s"), *FString::SanitizeFloat(FrontBack), *FString::SanitizeFloat(LeftRight));

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FALSMantleAsset::FALSMantleAsset() : AnimMontage(nullptr), PositionCorrectionCurve(nullptr), LowHeight(0), LowPlayRate(0), LowStartPosition(0), HighHeight(0), HighPlayRate(0), HighStartPosition(0) {}

FALSMantleAsset::FALSMantleAsset(UAnimMontage* AnimMontage, UCurveVector* PositionCorrectionCurve,
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

FString FALSMantleAsset::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("AnimMontage: %s, StartingOffset: %s,Height: [Low: %s, High: %s], PlayRate: [Low: %s, High: %s], StaringPosition: [Low: %s , High: %s], PositionCorrectionCurve: %s"), *AnimMontage->GetName(), *StartingOffset.ToString(), *FString::SanitizeFloat(LowHeight), *FString::SanitizeFloat(HighHeight), *FString::SanitizeFloat(LowPlayRate), *FString::SanitizeFloat(HighPlayRate), *FString::SanitizeFloat(LowStartPosition), *FString::SanitizeFloat(HighStartPosition), *StartingOffset.ToString());

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FALSMantleParams::FALSMantleParams() {
	PlayRate = 1.0f;
}

FALSMantleParams::FALSMantleParams(UAnimMontage* animMontage, UCurveVector* positionCorrectionCurve, float startingPosition, FVector startingOffset, float playRate) {
	AnimMontage = animMontage;
	PositionCorrectionCurve = positionCorrectionCurve;
	StartingOffset = startingOffset;
	StartingPosition = startingPosition;
	PlayRate = playRate;
}

FString FALSMantleParams::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("AnimMontage: %s, PositionCorrectionCurve: %s, StatingOffset: %s, StatingPosition: %s, PlayRate: %s"), *AnimMontage->GetName(), *PositionCorrectionCurve->GetName(), *StartingOffset.ToString(), *FString::SanitizeFloat(StartingPosition), *FString::SanitizeFloat(PlayRate));

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FALSTurnInPlaceAsset::FALSTurnInPlaceAsset() : AnimatedAngle(0), PlayRate(0), ScaleTurnAngle(0) {
	Animation = nullptr;
}

FString FALSTurnInPlaceAsset::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Animation: %s, Slot Name: %s, AnimatedAngle: %s, PlayRate: %s, ScaleTurnAngle: %s"), *Animation->GetName(), *SlotName.ToString(), *FString::SanitizeFloat(AnimatedAngle), *FString::SanitizeFloat(PlayRate), *UALSHelpers::Bool2String(ScaleTurnAngle));

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FALSVelocityBlend::FALSVelocityBlend() : F(0.0f), B(0.0f), L(0.0f), R(0.0f) {}

FALSVelocityBlend::FALSVelocityBlend(const float f, const float b, const float l, const float r) : F(f), B(b), L(l), R(r) {}

FString FALSVelocityBlend::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Front: %s, Back: %s, Right: %s, Left: %s"), *FString::SanitizeFloat(F), *FString::SanitizeFloat(B), *FString::SanitizeFloat(R), *FString::SanitizeFloat(L));

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FAnimCurveCreationData::FAnimCurveCreationData() {}

FString FAnimCurveCreationData::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Frame Number: %d, Curve Value: %s"), FrameNumber, *FString::SanitizeFloat(CurveValue));

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FALSAnimCurveCreationParams::FALSAnimCurveCreationParams() {}

FString FALSAnimCurveCreationParams::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Curve Name: %s, KeyEach Frame: %s"), *CurveName.ToString(), *UALSHelpers::Bool2String(KeyEachFrame));

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FALSCurrentState::FALSCurrentState() {
	PawnMovementMode = MOVE_None;
}

FString FALSCurrentState::ToString(bool bPrintToLog) {

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
		UALSLogger::LogInfo(r);

	return r;

}

FALSEssentialValues::FALSEssentialValues() : bIsMoving(false), bHasMovementInput(false), Speed(0),
MovementInputAmount(0), AimYawRate(0) {}

FALSEssentialValues::FALSEssentialValues(const FVector velocity, const FVector acceleration, const FVector movementInput, const bool isMoving, const bool hasMovementInput, const float speed, const float movementInputAmount, const FRotator aimingRotation, const float aimYawRate) {
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

FString FALSEssentialValues::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Velocity: %ls \nAcceleration: %ls,\nAimingRotation: %ls\nMovementInput: %ls\nSpeed: %f\nMovementInputAmount: %f\nAimYawRate: %f\nIsMoving: %ls\nHasMovementInput: %ls\n"), *Velocity.ToString(), *Acceleration.ToString(), *AimingRotation.ToString(), *MovementInput.ToString(), Speed, MovementInputAmount, AimYawRate, *UALSHelpers::Bool2String(bIsMoving), *UALSHelpers::Bool2String(bHasMovementInput));

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FALSDebugInfo::FALSDebugInfo() {
	DebugFocusCharacter = nullptr;
}

FALSDebugInfo::FALSDebugInfo(ACharacter* FocusedDebugCharacter, const bool DebugView, const bool ShowHUD, const bool ShowTraces,
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

FString FALSDebugInfo::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Debugging Character: %s, DebugView: %s, HUD: %s, Traces: %s, Debug Shapes: %s, Layer Colors: %s, Slow Motion: %s, Character Info: %s"),
		*DebugFocusCharacter->GetName(),
		*UALSHelpers::Bool2String(bDebugView, TEXT("Enabled"), TEXT("Disabled")),
		*UALSHelpers::Bool2String(bShowHUD, TEXT("Enabled"), TEXT("Disabled")),
		*UALSHelpers::Bool2String(bShowTraces, TEXT("Enabled"), TEXT("Disabled")),
		*UALSHelpers::Bool2String(bShowDebugShapes, TEXT("Enabled"), TEXT("Disabled")),
		*UALSHelpers::Bool2String(bShowLayerColors, TEXT("Enabled"), TEXT("Disabled")),
		*UALSHelpers::Bool2String(bSlowMotion, TEXT("Enabled"), TEXT("Disabled")),
		*UALSHelpers::Bool2String(bShowCharacterInfo, TEXT("Enabled"), TEXT("Disabled"))
	);

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FALSCameraParameters::FALSCameraParameters() {
	TP_FOV = 0;
	FP_FOV = 0;
	bRightShoulder = true;
}

FALSCameraParameters::FALSCameraParameters(float tP_FOV, float fp_FOV, bool rightShoulder) {
	TP_FOV = tP_FOV;
	FP_FOV = fp_FOV;
	bRightShoulder = rightShoulder;
}

FString FALSCameraParameters::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("TP FOV: %s, FP FOV: %s, Cam Shoulder? %s"), *FString::SanitizeFloat(TP_FOV), *FString::SanitizeFloat(FP_FOV), *UALSHelpers::Bool2String(bRightShoulder, TEXT("Right"), TEXT("Left")));

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FALSTraceParams::FALSTraceParams() {
	TraceChannel = TraceTypeQuery1;
	TraceOrigin = FVector();
	TraceRadius = 10.0f;
}

FALSTraceParams::FALSTraceParams(TEnumAsByte<ETraceTypeQuery> traceChannel, FVector traceOrigin, float traceRadius) {
	TraceChannel = traceChannel;
	TraceOrigin = traceOrigin;
	TraceRadius = traceRadius;
}

FString FALSTraceParams::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Trace Channel: %s, Trace Origin: %s, Trace Radius: %s"), *UEnum::GetValueAsString(TraceChannel), *TraceOrigin.ToString(), *FString::SanitizeFloat(TraceRadius));

	if (bPrintToLog)
		UALSLogger::LogInfo(r, 0.0f);

	return r;
}

FALSCameraBehaviourResult::FALSCameraBehaviourResult() {
	Location = FVector::ZeroVector;
	Rotation = FRotator::ZeroRotator;
	FOV = 0.0f;
}

FALSCameraBehaviourResult::FALSCameraBehaviourResult(const FVector location, const  FRotator rotation, const  float fov) {
	Location = location;
	Rotation = rotation;
	FOV = fov;
}

FString FALSCameraBehaviourResult::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Location: %s, Rotation: %s , FOV: %s"), *Location.ToString(), *Rotation.ToString(), *FString::SanitizeFloat(FOV));

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FALSControlVectors::FALSControlVectors() {}

FALSControlVectors::FALSControlVectors(const FVector forward, const FVector right) : Forward(forward), Right(right) {}

FString FALSControlVectors::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("[Forward= %s, Right= %s]"), *Forward.ToString(), *Right.ToString());

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FString FALSHitResult::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("bHit: %s, bBlockingHit: %s, bStartPenetrating: %s, Hit Component Name: %s, Distance: %s"), *UALSHelpers::Bool2String(bHit), *UALSHelpers::Bool2String(SweepHitResult.bBlockingHit), *UALSHelpers::Bool2String(SweepHitResult.bStartPenetrating), *SweepHitResult.Component->GetName(), *FString::SanitizeFloat(SweepHitResult.Distance));

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FString FALSRotateInPlaceAsset::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Animation: %s, SlotName: %s, TurnRate: [Slow= %s, Fast= %s], PlayRateRange: [Slow= %s, Fast= %s]"), *Animation->GetName(), *SlotName.ToString(), *FString::SanitizeFloat(SlowTurnRate), *FString::SanitizeFloat(FastTurnRate), *FString::SanitizeFloat(SlowPlayRate), *FString::SanitizeFloat(FastPlayRate));

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FString FALSCameraSettings::ToString(bool bPrintToLog) {

	const auto r = FString::Printf(TEXT("TargetArmLength: %s, SocketOffset: %s, LagSpeed: %s, RotationLagSpeed: %s, DoCollitionTest: %s"),
		*FString::SanitizeFloat(TargetArmLength), *SocketOffset.ToString(), *FString::SanitizeFloat(LagSpeed), *FString::SanitizeFloat(RotationLagSpeed), *UALSHelpers::Bool2String(DoCollisionTest));

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FString FALSCameraSettingsGait::ToString(bool bPrintToLog) {

	const auto r = FString::Printf(TEXT("Walking: %s\nRunning: %s\nSprinting: %s\nCrouching: %s"), *Walking.ToString(), *Running.ToString(), *Sprinting.ToString(), *Crouching.ToString());

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FString FALSCameraSettingsState::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Velocity Direction: %s\nLooking Direction: %s\nAiming: %s"), *VelocityDirection.ToString(), *LookingDirection.ToString(), *Aiming.ToString());

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FString FALSMantleTraceSettings::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Ledge Height= [Min: %s ,Max: %s], TraceRadius= [Forward: %s, Downward: %s], Reach Distance: %s"), *FString::SanitizeFloat(MinLedgeHeight), *FString::SanitizeFloat(MaxLedgeHeight), *FString::SanitizeFloat(ForwardTraceRadius), *FString::SanitizeFloat(DownwardTraceRadius), *FString::SanitizeFloat(ReachDistance));

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FString FALSMovementSettings::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Speeds= [Walk: %s, Run: %s, Sprint: %s], MovementCurve: %s, Rotation RateCurve: %s"), *FString::SanitizeFloat(WalkSpeed), *FString::SanitizeFloat(RunSpeed), *FString::SanitizeFloat(SprintSpeed), *MovementCurve->GetName(), *RotationRateCurve->GetName());

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FString FALSMovementSettingsStance::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Standing: %s, Crouching: %s"), *Standing.ToString(), *Crouching.ToString());

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}

FString FALSMovementSettingsState::ToString(bool bPrintToLog) {
	const auto r = FString::Printf(TEXT("Velocity Direction: %s, Looking Direction: %s, AimingDirection: %s"), *VelocityDirection.ToString(), *LookingDirection.ToString(), *Aiming.ToString());

	if (bPrintToLog)
		UALSLogger::LogInfo(r);

	return r;
}
