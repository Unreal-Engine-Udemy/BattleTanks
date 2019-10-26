// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "BattleTanks/Public/TankAimingComponent.h"
#include "Components/SceneComponent.h"
#include "BattleTanks/Public/TankBarrelComponent.h"
#include "BattleTanks/Public/TankTurret.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::LogAiming(FString&& Name, FVector* Location)
{
	FVector BarrelLocation = Barrel->GetComponentLocation();
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at location %s from %s"), *Name, (*(*Location).ToString()), *BarrelLocation.ToString());
}

void UTankAimingComponent::SetBarrelReference(UTankBarrelComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector& Location, float LaunchSpeed)
{
	if (!Barrel) return;
	if (!Turret) return;

	FVector LaunchDirection;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the out launce velocity
	bool bHaveSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchDirection,
		StartLocation,
		Location,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveSolution)
	{
		LogAiming(GetName(), &LaunchDirection);
		auto AimDirection = LaunchDirection.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector& AimDirection)
{
	/// Work out difference between current barrel orientation and desired rotation
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto BarrelDeltaRotator = AimAsRotator - BarrelRotation;

	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto TurretDeltaRotator = AimAsRotator - TurretRotation;

	Barrel->Elevate(BarrelDeltaRotator.Pitch);
	Turret->Rotate(TurretDeltaRotator.Yaw);


}

