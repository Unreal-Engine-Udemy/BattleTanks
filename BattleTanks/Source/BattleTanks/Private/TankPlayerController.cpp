// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks/Public/Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "BattleTanks/Public/TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();

	if(!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank not possessed!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank %s possessed!"), *(ControlledTank->GetName()));
	}
	
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();

}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) { return; }
	
	FVector HitLocation; //out paramter 

	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
		
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	/// Find the crosshair position in terms of pixel XY
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FHitResult HitResult;
	bool bHit;
	bHit = GetHitResultAtScreenPosition(ScreenLocation, ECollisionChannel::ECC_Visibility, false, HitResult);
	if (bHit)
	{
		OutHitLocation = std::move(HitResult.Location);
		return true;
	}
	return false;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& OutHitLocation, FVector* Direction, FVector* CameraWorldLocation) const
{
	FHitResult HitResult;
	if ( GetWorld()->LineTraceSingleByChannel(
		HitResult,
		*CameraWorldLocation,
		*CameraWorldLocation + (LengthOfView * (*Direction)),
		ECollisionChannel::ECC_Visibility
	))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	return false;
}


