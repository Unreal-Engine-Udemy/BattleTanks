// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTanks/Public/Tank.h"
#include "Components/InputComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* Eventinstidgator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	auto DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		OnDeathEvent.Broadcast();
	}

	return FPlatformMath::RoundToFloat(DamageToApply);
}

float ATank::GetHealthPercnet() const
{
	return float(CurrentHealth) / float(StartingHealth);
}
