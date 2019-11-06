// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTanks/Public/TankMovementComponent.h"
#include "BattleTanks/Public/TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (Throw != 0)
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	}

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (Throw > 0)
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(-Throw);
	}

}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	if (Throw > 0)
	{
		LeftTrack->SetThrottle(-Throw);
		RightTrack->SetThrottle(Throw);
	}

}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call super as we're replacing the functionality 
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention); 

	IntendMoveForward(ForwardThrow);

	auto ResultantVector = FVector::CrossProduct(TankForward, AIForwardIntention);

	if (ResultantVector.Z < 0) //turn right
	{
		IntendTurnRight((ResultantVector.Size()));
	}
	else
	{
		IntendTurnLeft((ResultantVector.Size()));
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s vecotring to %s"), *TankName, *MoveVeclocityString);
}
