// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	void BeginPlay() override;

private:

	virtual void Tick(float DeltaTime) override;

	// This is the distance the tank will stop away from its goal
	UPROPERTY(EditDefaultsOnly, Category = "Setup") // consiider EditDefaultsOnly
	float AcceptanceRadius = 5000; // 30m

	virtual void SetPawn(APawn* InPawn) override;

	UTankAimingComponent* AimingComponent = nullptr;

	UFUNCTION()
	void OnPossessedTankDeath();

};
