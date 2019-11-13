// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks/Public/Tank.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "BattleTanks/Public/TankAimingComponent.h"
#include "BattleTanks/Public/TankAIController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

}

void ATankAIController::Tick(float DeltaTime)
{
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (ensure(PlayerTank))
	{
		//  move towards player
		MoveToActor(PlayerTank, AcceptanceRadius, true, true, false, 0 );

		//Aim towards player 
		AimingComponent->AimAt(Forward<FVector&>(PlayerTank->GetActorLocation()));

		// Fire if ready
		if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
		{
			AimingComponent->Fire();
		}
	}
	
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))
		{
			return;
		}

		// Subsribe local method to tank death event
		PossessedTank->OnDeathEvent.AddUObject(this, &ATankAIController::OnPossessedTankDeath);

	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn() )
	{
		return;
	}

	GetPawn()->DetachFromControllerPendingDestroy();
	UE_LOG(LogTemp, Warning, TEXT("Tank dies and detached!"));
}
