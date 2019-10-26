// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrelComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrelComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 2.0F;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 33.F;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevation = 0.F;

	void Elevate(float RelativeSpeed);
	
};
