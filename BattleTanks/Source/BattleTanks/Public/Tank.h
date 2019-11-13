// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BattleTanks/Public/TankTrack.h"
#include "Delegate.h"
#include "Tank.generated.h"

DECLARE_MULTICAST_DELEGATE(FDeathDelegate);

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	int32 CurrentHealth;

public:

	ATank();

	virtual void BeginPlay() override;

	FDeathDelegate OnDeathEvent;

	//called by the engine.
	virtual float TakeDamage(float amount, struct FDamageEvent const & DamageEvent, class AController* Eventinstidgator, AActor* DamageCauser) override;


	// Return percentage health between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercnet() const;
};
