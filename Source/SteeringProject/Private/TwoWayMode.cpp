// Fill out your copyright notice in the Description page of Project Settings.


#include "TwoWayMode.h"

#include "SteeringGameState.h"
#include "VectorTypes.h"
#include "Vehicle.h"

FVector UTwoWayMode::ComputeNewVector() {
	// Set Target
	if (Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPoints.Num()) {
		Target = Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPoints[Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex];
	} else {
		return FVector(0, 0, 0);
	}
	// Get distance between target and self
	Target.Z = 0.f;
	const double Dist = UE::Geometry::Distance({Target.X, Target.Y, 0.f}, GetOwner()->GetActorLocation()) - 90;

	// if in range and on first trip
	if (Dist < 50 && FirstTrip) {
		Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex++;
		if (Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPoints.Num() == Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex) {
			FirstTrip = false;
			Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex -= 2;
			if (Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex < 0) {
				Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex = 0;
			}
		}
	}
	// if in range and on second trip
	else if (Dist < 50 && !FirstTrip && Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex != 0) {
		Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex--;
	}
	// if on last point
	if (Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex == 0 && !FirstTrip) {
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

void UTwoWayMode::RestartCircuit() {
	Super::RestartCircuit();
	FirstTrip = true;
}
