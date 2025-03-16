// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrivalMode.h"
#include <variant>
#include "Vehicle.h"
#include "SteeringProject/SteeringProjectCharacter.h"

FVector UArrivalMode::ComputeNewVector() {
	FVector Result = FVector::ZeroVector;
	
	std::variant<AVehicle *, ASteeringProjectCharacter *> Owner;
	AVehicle *tmp = Cast<AVehicle>(GetOwner());
	if (tmp) Owner = tmp;
	ASteeringProjectCharacter *tmp2 = Cast<ASteeringProjectCharacter>(GetOwner());
	if (tmp2) Owner = tmp2;

	std::visit([&](auto owner) {
		FVector TargetOffset = Target - owner->GetActorLocation();
		double Distance = TargetOffset.Length();
		double RampedSpeed = owner->MaxSpeed * (Distance / SlowingDistance);
		RampedSpeed = FMath::Clamp(RampedSpeed, 200, owner->MaxSpeed);
		double ClippedSpeed = FMath::Min(RampedSpeed, owner->MaxSpeed);
		FVector DesiredVelocity = TargetOffset.GetSafeNormal() * ClippedSpeed;
		Result = DesiredVelocity - PreviousVelocity;
	}, Owner);
	
	return Result;
}
