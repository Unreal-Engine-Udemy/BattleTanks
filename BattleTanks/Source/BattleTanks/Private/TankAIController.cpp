// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks/Public/Tank.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "BattleTanks/Public/TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetPlayerTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank not possessed!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank %s possessed!"), *(ControlledTank->GetName()));
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerPawn);
}
