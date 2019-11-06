// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"  // must be last include 

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	void Tick(float DeltaTime) override;

	void BeginPlay() override;

private:

	// move the barrel towards the aim reticule
	void AimTowardsCrossHair();

	// get hit location of the aim reticule
	bool GetSightRayHitLocation( FVector &OutHitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333;

	UPROPERTY(EditAnywhere)
	float LengthOfView = 1000000;

	bool GetLookVectorHitLocation(FVector& OutHitLocation, FVector* Direction, FVector* CameraWorldLocation) const;

	UTankAimingComponent* AimingComponent = nullptr;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Steup")
	void FoundAimingComponent(UTankAimingComponent* AimComRef);
	
};
