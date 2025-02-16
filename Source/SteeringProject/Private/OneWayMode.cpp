// Fill out your copyright notice in the Description page of Project Settings.


#include "OneWayMode.h"

#include "SteeringGameState.h"
#include "VectorTypes.h"
#include "Vehicle.h"

FVector UOneWayMode::ComputeNewVector() {
	// Set Target
	if (Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPoints.Num()) {
		Target = Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPoints[Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex];
	} else {
		return FVector(0, 0, 0);
	}
	// Get distance between target and self
	Target.Z = 0.f;
	const double Dist = UE::Geometry::Distance({Target.X, Target.Y, 0.f}, GetOwner()->GetActorLocation()) - 90;

	// if in range and not on last point
	if (Dist < 50 &&
		Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPoints.Num()-1 != Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex) {
		Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex++;
		if (Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPoints.Num() == Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex) {
			Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex = 0;
		}
	}
	// if on last point
	if (Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPoints.Num()-1 == Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex) {
		// Arrival
		FVector TargetOffset = Target - GetOwner()->GetActorLocation();
		double Distance = TargetOffset.Length();
		double RampedSpeed = Cast<AVehicle>(GetOwner())->MaxSpeed * (Distance / 700.f); // Slowing Distance = 700
		double ClippedSpeed = FMath::Min(RampedSpeed, Cast<AVehicle>(GetOwner())->MaxSpeed);
		FVector DesiredVelocity = TargetOffset.GetSafeNormal() * ClippedSpeed;
		return DesiredVelocity - PreviousVelocity;
	}
	const FVector DesiredVelocity = (Target - GetOwner()->GetActorLocation()).GetSafeNormal() * Cast<AVehicle>(GetOwner())->MaxSpeed;
	return DesiredVelocity - PreviousVelocity;
}
