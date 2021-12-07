#pragma once

#include "ALSStructs.h"

FALSComponentAndTransform::FALSComponentAndTransform() {
	Component = nullptr;
	Transform = FTransform();
}

FALSComponentAndTransform::FALSComponentAndTransform(FTransform transform, UPrimitiveComponent* component) {
	Transform = transform;
	Component = component;
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

FALSLeanAmount::FALSLeanAmount() {
	FrontBack = 0.0f;
	LeftRight = 0.0f;
}

FALSLeanAmount::FALSLeanAmount(float FB, float LR) {
	FrontBack = FB;
	LeftRight = LR;
}

FALSMantleAsset::FALSMantleAsset() : AnimMontage(nullptr), PositionCorrectionCurve(nullptr), LowHeight(0), LowPlayRate(0), LowStartPosition(0), HighHeight(0), HighPlayRate(0), HighStartPosition(0) {
}

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

FALSTurnInPlaceAsset::FALSTurnInPlaceAsset() : AnimatedAngle(0), PlayRate(0), ScaleTurnAngle(0) {
	Animation = nullptr;
}

FALSVelocityBlend::FALSVelocityBlend() : F(0.0f), B(0.0f), L(0.0f), R(0.0f) {}

FALSVelocityBlend::FALSVelocityBlend(const float f, const float b, const float l, const float r) : F(f), B(b), L(l), R(r) {}

FAnimCurveCreationData::FAnimCurveCreationData() {}

FALSAnimCurveCreationParams::FALSAnimCurveCreationParams() {}

FALSCurrentState::FALSCurrentState() {
	PawnMovementMode = MOVE_None;
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

FString FALSEssentialValues::ToString() const {
	return FString::Printf(TEXT("Velocity: %ls \nAcceleration: %ls,\nAimingRotation: %ls\nMovementInput: %ls\nSpeed: %f\nMovementInputAmount: %f\nAimYawRate: %f\nIsMoving: %ls\nHasMovementInput: %ls\n"), *Velocity.ToString(), *Acceleration.ToString(), *AimingRotation.ToString(), *MovementInput.ToString(), Speed, MovementInputAmount, AimYawRate, bIsMoving ? TEXT("True") : TEXT("false"), bHasMovementInput ? TEXT("True") : TEXT("false"));
}

FALSDebugInfo::FALSDebugInfo() {
	DebugFocusCharacter = nullptr;
}

FALSDebugInfo::FALSDebugInfo(ACharacter * FocusedDebugCharacter, const bool DebugView, const bool ShowHUD, const bool ShowTraces,
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

FALSControlVectors::FALSControlVectors() {}

FALSControlVectors::FALSControlVectors(const FVector forward, const FVector right) : Forward(forward), Right(right) {}
