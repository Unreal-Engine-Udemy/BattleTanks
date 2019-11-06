// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

/// Forward declarations
class UTankBarrelComponent; 
class UTankTurret;
class AProjectile;

// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;

public:	
	
	void LogAiming(FString&& Name, FVector* Location);

	void AimAt(FVector& Location);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrelComponent* BarrelToSet, UTankTurret* TurretToSet);

private:

	bool IsBarrelMoving();

	UTankBarrelComponent* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector& AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 50000; // 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.f;

	double LastFireTime = 0;

	FVector LastAimingPosition = FVector(0);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

};
