// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UTankTurret();

	void Rotate(float DeltaRotate);
	
private:

	UPROPERTY(EditAnywhere, Category = Rotate)
	float MaxRotateSpeed = 30.f; // in degrees per second


};
