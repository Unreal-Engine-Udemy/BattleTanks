// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTanks/Public/Tank.h"
#include "BattleTanks/Public/TankAimingComponent.h"
#include "BattleTanks/Public/TankBarrelComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

// This function must be called in Tank_BP!
void ATank::SetBarrelReference(UTankBarrelComponent* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

// This function must be called in Tank_BP!
void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Firing weapon!"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

