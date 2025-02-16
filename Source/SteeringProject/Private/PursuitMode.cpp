// Fill out your copyright notice in the Description page of Project Settings.


#include "PursuitMode.h"

#include "SteeringGameState.h"
#include "Vehicle.h"
#include "SteeringProject/SteeringProjectCharacter.h"

FVector UPursuitMode::ComputeNewVector() {
	AVehicle *Vehicle = Cast<AVehicle>(Cast<ASteeringGameState>(GetWorld()->GetGameState())->SeekMode->GetOwner());
	FVector ComputedVehicleTarget =  Vehicle->GetActorLocation();
	ComputedVehicleTarget += Cast<ASteeringGameState>(GetWorld()->GetGameState())->PreviousVelocity * 1.5;
	const FVector DesiredVelocity = (ComputedVehicleTarget - GetOwner()->GetActorLocation()).GetSafeNormal() * Cast<ASteeringProjectCharacter>(GetOwner())->MaxSpeed;
	return DesiredVelocity - PreviousVelocity;
}

void UPursuitMode::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	ASteeringProjectCharacter *Owner = Cast<ASteeringProjectCharacter>(GetOwner());
	if (bModeIsActive) {
		if (Target != Cast<ASteeringGameState>(GetWorld()->GetGameState())->GetTarget())
			Target = Cast<ASteeringGameState>(GetWorld()->GetGameState())->GetTarget();
		FVector SteeringDirection = ComputeNewVector();
		FVector SteeringForce     = SteeringDirection.GetClampedToMaxSize(Owner->MaxForce);
		FVector Acceleration      = SteeringForce / Owner->Mass;
		FVector Velocity          = (PreviousVelocity + Acceleration).GetClampedToMaxSize(Owner->MaxSpeed);
		Velocity.Z                = 0.f;
		FVector Result   = Owner->GetActorLocation() + Velocity * DeltaTime;
		PreviousVelocity = Velocity;
		Owner->SetActorLocation(Result);
		FRotator SteeringRotation = Velocity.ToOrientationRotator();
		FRotator CurrentRotation  = Owner->GetActorRotation();
		FRotator NewRotation      = FMath::RInterpTo(CurrentRotation, SteeringRotation, DeltaTime, 5);
		NewRotation.Pitch         = 0.f;
		Owner->SetActorRotation(NewRotation);
	}
}
