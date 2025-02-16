// Fill out your copyright notice in the Description page of Project Settings.


#include "CircuitMode.h"

#include "SteeringGameState.h"
#include "VectorTypes.h"
#include "Vehicle.h"

void UCircuitMode::ResetCircuit() {
	Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPoints.Empty();
	Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex = 0;
}

void UCircuitMode::RestartCircuit() {
	Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex = 0;
}

FVector UCircuitMode::ComputeNewVector() {
	// Target point
	if (Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPoints.Num()) {
		Target = Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPoints[Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex];
	} else {
		return FVector(0, 0, 0);
	}
	// If reached, change index, change target
	Target.Z = 0.f;
	const double Dist = UE::Geometry::Distance({Target.X, Target.Y, 0.f}, GetOwner()->GetActorLocation()) - 90;
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Index : ") + Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex);
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Array Size : ") + Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPoints.Num());
	if (Dist < 50) {
		Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex++;
		if (Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPoints.Num() == Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex) {
			Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex = 0;
		}
		// Target = Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPoints[Cast<ASteeringGameState>(GetWorld()->GetGameState())->CircuitPointIndex];
	}
	const FVector DesiredVelocity = (Target - GetOwner()->GetActorLocation()).GetSafeNormal() * Cast<AVehicle>(GetOwner())->MaxSpeed;
	return DesiredVelocity - PreviousVelocity;
}
