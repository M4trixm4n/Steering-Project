// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractMode.h"

#include "SteeringGameState.h"
#include "VectorUtil.h"
#include "Vehicle.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values for this component's properties
UAbstractMode::UAbstractMode() {
	PrimaryComponentTick.bCanEverTick = true;

	bModeIsActive = false;
}


// Called when the game starts
void UAbstractMode::BeginPlay() {
	Super::BeginPlay();
	// ...

}

void UAbstractMode::DisableMode() {
	bModeIsActive = false;
}

void UAbstractMode::EnableMode() {
	bModeIsActive = true;
}

// Called every frame
void UAbstractMode::TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction *ThisTickFunction
		) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AVehicle *Owner = Cast<AVehicle>(GetOwner());
	if (bModeIsActive) {
		if (Target != Cast<ASteeringGameState>(GetWorld()->GetGameState())->GetTarget()) Target = Cast<ASteeringGameState>(GetWorld()->GetGameState())->GetTarget();
		FVector SteeringDirection = ComputeNewVector();
		FVector SteeringForce = SteeringDirection.GetClampedToMaxSize(Owner->MaxForce);
		FVector Acceleration = SteeringForce / Owner->Mass;
		FVector Velocity = (PreviousVelocity + Acceleration).GetClampedToMaxSize(Owner->MaxSpeed);
		Velocity.Z = 0.f;
		// FVector Velocity = (Owner->GetMovementComponent()->Velocity + Acceleration * DeltaTime).GetClampedToMaxSize(Owner->MaxSpeed);
		// FVector Result = Owner->GetActorLocation() + Velocity * DeltaTime;
		FVector Result = Owner->GetActorLocation() + Velocity * DeltaTime;
		PreviousVelocity = Velocity;
		Owner->SetActorLocation(Result);
		FRotator SteeringRotation = Velocity.ToOrientationRotator();
		FRotator CurrentRotation = Owner->GetActorRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, SteeringRotation, DeltaTime, 5);
		NewRotation.Pitch = 0.f;
		Owner->SetActorRotation(NewRotation);
		UE_LOG(LogTemp, Warning, TEXT ("Steering Direction : %lf, %lf, %lf"), SteeringDirection.X, SteeringDirection.Y, SteeringDirection.Z);
		UE_LOG(LogTemp, Warning, TEXT ("SteeringForce : %lf, %lf, %lf"), SteeringForce.X, SteeringForce.Y, SteeringForce.Z);
		UE_LOG(LogTemp, Warning, TEXT ("Acceleration : %lf, %lf, %lf"), Acceleration.X, Acceleration.Y, Acceleration.Z);
		UE_LOG(LogTemp, Warning, TEXT ("Previous Velocity : %lf, %lf, %lf"), PreviousVelocity.X, PreviousVelocity.Y, PreviousVelocity.Z);
		UE_LOG(LogTemp, Warning, TEXT ("Velocity : %lf, %lf, %lf"), Velocity.X, Velocity.Y, Velocity.Z);
		UE_LOG(LogTemp, Warning, TEXT ("Result : %lf, %lf, %lf"), Result.X, Result.Y, Result.Z);
	}
}
