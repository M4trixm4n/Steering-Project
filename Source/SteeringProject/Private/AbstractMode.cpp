// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractMode.h"
#include <variant>
#include "SteeringGameState.h"
#include "Vehicle.h"
#include "SteeringProject/SteeringProjectCharacter.h"

UAbstractMode::UAbstractMode() {
	PrimaryComponentTick.bCanEverTick = true;

	bModeIsActive = false;
}

void UAbstractMode::BeginPlay() {
	Super::BeginPlay();
}

void UAbstractMode::DisableMode() {
	std::variant<AVehicle *, ASteeringProjectCharacter *> Owner;
	AVehicle *tmp = Cast<AVehicle>(GetOwner());
	if (tmp) Owner = tmp;
	ASteeringProjectCharacter *tmp2 = Cast<ASteeringProjectCharacter>(GetOwner());
	if (tmp2) Owner = tmp2;
	if (bModeIsActive) {
		std::visit([&](auto owner) {
			bModeIsActive = false;
			if (!owner->PathFindingComp->PreviousVelocity.IsNearlyZero(0.1)) owner->PathFindingComp->PreviousVelocity =
					PreviousVelocity;
		}, Owner);
	}
}

void UAbstractMode::EnableMode() {
	std::variant<AVehicle *, ASteeringProjectCharacter *> Owner;
	AVehicle *tmp = Cast<AVehicle>(GetOwner());
	if (tmp) Owner = tmp;
	ASteeringProjectCharacter *tmp2 = Cast<ASteeringProjectCharacter>(GetOwner());
	if (tmp2) Owner = tmp2;
	std::visit([&](auto owner) {
		bModeIsActive = true;
		if (!owner->PathFindingComp->PreviousVelocity.IsNearlyZero(0.1))
			PreviousVelocity = owner->PathFindingComp->PreviousVelocity;
	}, Owner);
}

void UAbstractMode::TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction *ThisTickFunction
		) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	std::variant<AVehicle *, ASteeringProjectCharacter *> Owner;
	AVehicle *tmp = Cast<AVehicle>(GetOwner());
	if (tmp) Owner = tmp;
	ASteeringProjectCharacter *tmp2 = Cast<ASteeringProjectCharacter>(GetOwner());
	if (tmp2) Owner = tmp2;
	if (bModeIsActive) {
		std::visit([&](auto owner) {
			if (Target != owner->PathFindingComp->Target) Target = owner->PathFindingComp->Target;
			PreviousVelocity = owner->PathFindingComp->PreviousVelocity;
			FVector SteeringDirection = ComputeNewVector();
			FVector SteeringForce = SteeringDirection.GetClampedToMaxSize(owner->MaxForce);
			FVector Acceleration = SteeringForce / owner->Mass;
			FVector Velocity = (PreviousVelocity + Acceleration).GetClampedToMaxSize(owner->MaxSpeed);
			Velocity.Z = 0.f;
			FVector Result = owner->GetActorLocation() + Velocity * DeltaTime;
			PreviousVelocity = Velocity;
			owner->PathFindingComp->PreviousVelocity = Velocity;
			owner->SetActorLocation(Result);
			FRotator SteeringRotation = Velocity.ToOrientationRotator();
			FRotator CurrentRotation  = owner->GetActorRotation();
			FRotator NewRotation      = FMath::RInterpTo(CurrentRotation, SteeringRotation, DeltaTime, 5);
			NewRotation.Pitch         = 0.f;
			owner->SetActorRotation(NewRotation);
			// UE_LOG(LogTemp, Warning, TEXT ("Result : %lf, %lf, %lf"), Result.X, Result.Y, Result.Z);
		}, Owner);
	}
}
