// Fill out your copyright notice in the Description page of Project Settings.

#include "UObject/ConstructorHelpers.h"
#include "BattleTanks/Public/TankTurret.h"

UTankTurret::UTankTurret()
{
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Tank/tank_fbx_Turret'"));
	//UStaticMesh* Asset = MeshAsset.Object;

	//this->SetStaticMesh(Asset);
}

void UTankTurret::Rotate(float DeltaRotate)
{
	DeltaRotate = FMath::Clamp<float>(DeltaRotate, -1, +1);

	auto YawChange = DeltaRotate * MaxRotateSpeed * GetWorld()->DeltaTimeSeconds;
	float NewYaw = RelativeRotation.Yaw + YawChange;

	SetRelativeRotation(FRotator(0, NewYaw, 0));

}