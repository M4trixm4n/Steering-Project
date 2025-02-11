// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrivalMode.h"

#include "Vehicle.h"

FVector UArrivalMode::ComputeNewVector() {
	FVector TargetOffset = Target - GetOwner()->GetActorLocation();
	double Distance = TargetOffset.Length();
	double RampedSpeed = Cast<AVehicle>(GetOwner())->MaxSpeed * (Distance / SlowingDistance);
	double ClippedSpeed = FMath::Min(RampedSpeed, Cast<AVehicle>(GetOwner())->MaxSpeed);
	FVector DesiredVelocity = TargetOffset.GetSafeNormal() * ClippedSpeed;
	return DesiredVelocity - PreviousVelocity;
}
