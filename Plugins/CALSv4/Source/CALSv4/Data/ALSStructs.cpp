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

FALSMantleAsset::FALSMantleAsset() {}

FALSMantleAsset::FALSMantleAsset(UAnimMontage* AnimMontage, UCurveVector* PositionCorrectionCurve, const FVector StartingOffset, const float LowHeight, const float LowPlayRate, const float LowStartPosition, const float HighHeight, const float HighPlayRate, const float HighStartPosition) {
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

FALSMantleParams::FALSMantleParams() {}

FALSMantleParams::FALSMantleParams(UAnimMontage* animMontage, UCurveVector* positionCorrectionCurve, float startingPosition, FVector startingOffset, float playRate) {
	AnimMontage = animMontage;
	PositionCorrectionCurve = positionCorrectionCurve;
	StartingOffset = startingOffset;
	StartingPosition = startingPosition;
	PlayRate = playRate;
}

FALSVelocityBlend::FALSVelocityBlend() : F(0.0f), B(0.0f), L(0.0f), R(0.0f) {}

FALSVelocityBlend::FALSVelocityBlend(const float f, const float b, const float l, const float r) : F(f), B(b), L(l), R(r) {}

FALSCurrentState::FALSCurrentState() {
	PawnMovementMode = MOVE_None;
}

FALSCameraParameters::FALSCameraParameters() {
	TP_FOV = 0;
	FP_FOV = 0;
	bRightShoulder = true;
}

FALSTraceParams::FALSTraceParams() {
	TraceChannel = TraceTypeQuery1;
	TraceOrigin = FVector();
	TraceRadius = 10.0f;
}

FALSCameraBehaviourResult::FALSCameraBehaviourResult() {
	Location = FVector();
	Rotation = FRotator::ZeroRotator;
	FOV = 0.0f;
}

FALSCameraBehaviourResult::FALSCameraBehaviourResult(FVector location, FRotator rotation, float fov) {
	Location = location;
	Rotation = rotation;
	FOV = fov;
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