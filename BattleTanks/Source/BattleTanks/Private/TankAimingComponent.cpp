// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "BattleTanks/Public/TankAimingComponent.h"
#include "Components/SceneComponent.h"
#include "BattleTanks/Public/Projectile.h"
#include "BattleTanks/Public/TankBarrelComponent.h"
#include "BattleTanks/Public/TankTurret.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (AmmoCount == 0)
	{
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::LogAiming(FString&& Name, FVector* Location)
{
	//FVector BarrelLocation = Barrel->GetComponentLocation();
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at location %s from %s"), *Name, (*(*Location).ToString()), *BarrelLocation.ToString());
}

void UTankAimingComponent::AimAt(FVector& Location)
{
	if (!ensure(Barrel)) return;
	if (!ensure(Turret)) return;

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
		auto AimDirection = LaunchDirection.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		LastAimingPosition = std::move(AimDirection);
	}
}


void UTankAimingComponent::Initialise(UTankBarrelComponent* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	if (Barrel->GetForwardVector().Equals(LastAimingPosition, 0.1F))
	{
		return false;
	}
	else
	{
		return true;
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

	if (TurretDeltaRotator.Yaw > 180)
	{
		TurretDeltaRotator.Yaw -= 360;
	}
	else if (TurretDeltaRotator.Yaw < -180)
	{
		TurretDeltaRotator.Yaw += 360;
	}

	Turret->Rotate(TurretDeltaRotator.Yaw);

}

void UTankAimingComponent::Fire()
{
	
	if (FiringStatus != EFiringStatus::Reloading && FiringStatus != EFiringStatus::OutOfAmmo)
	{
		if (!ensure(Barrel)) return ;
		if (!ensure(ProjectileBlueprint)) return;
		UE_LOG(LogTemp, Warning, TEXT("Firing weapon!"));

		/// Create projectile at end of barrel and launch it
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), FRotator(0));
		Projectile->LaunchProjectile(Barrel->GetForwardVector(), LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
		AmmoCount -= 1;

	}
}
