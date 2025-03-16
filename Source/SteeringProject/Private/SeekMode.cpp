// Fill out your copyright notice in the Description page of Project Settings.


#include "SeekMode.h"
#include <variant>
#include "Vehicle.h"
#include "SteeringProject/SteeringProjectCharacter.h"

FVector USeekMode::ComputeNewVector() {
	FVector Result = FVector::ZeroVector;
	
	std::variant<AVehicle *, ASteeringProjectCharacter *> Owner;
	AVehicle *tmp = Cast<AVehicle>(GetOwner());
	if (tmp) Owner = tmp;
	ASteeringProjectCharacter *tmp2 = Cast<ASteeringProjectCharacter>(GetOwner());
	if (tmp2) Owner = tmp2;
	
	std::visit([&](auto owner) {
		const FVector DesiredVelocity = (Target - owner->GetActorLocation()).GetSafeNormal() * owner->MaxSpeed;
		Result = DesiredVelocity - PreviousVelocity;
	}, Owner);

	return Result;
}
