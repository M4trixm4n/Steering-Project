// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractMode.h"

#include "SteeringGameState.h"

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
	if (bModeIsActive && Target != Cast<ASteeringGameState>(GetWorld()->GetGameState())->GetTarget()) {
		Target = Cast<ASteeringGameState>(GetWorld()->GetGameState())->GetTarget();
		UE_LOG(LogTemp, Warning, TEXT ("TargetChanged"));
	}
}
