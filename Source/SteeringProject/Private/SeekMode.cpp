// Fill out your copyright notice in the Description page of Project Settings.


#include "SeekMode.h"
#include "Vehicle.h"
#include "GameFramework/PawnMovementComponent.h"

FVector USeekMode::ComputeNewVector() {
	const FVector DesiredVelocity = (Target - GetOwner()->GetActorLocation()).GetSafeNormal() * Cast<AVehicle>(GetOwner())->MaxSpeed;
	return DesiredVelocity - PreviousVelocity;
}
