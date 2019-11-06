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
	float AcceptanceRadius = 3000; // 30m

	UTankAimingComponent* AimingComponent = nullptr;

};
