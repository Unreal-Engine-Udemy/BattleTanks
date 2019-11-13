// Fill out your copyright notice in the Description page of Project Settings.

#include "UObject/ConstructorHelpers.h"
#include "BattleTanks/Public/TankTurret.h"

void UTankTurret::Rotate(float DeltaRotate)
{
	DeltaRotate = FMath::Clamp<float>(DeltaRotate, -1, +1);

	auto YawChange = DeltaRotate * MaxRotateSpeed * GetWorld()->DeltaTimeSeconds;
	float NewYaw = RelativeRotation.Yaw + YawChange;

	SetRelativeRotation(FRotator(0, NewYaw, 0));

}