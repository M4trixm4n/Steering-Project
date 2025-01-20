// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractMode.h"

// Sets default values for this component's properties
UAbstractMode::UAbstractMode () {
	PrimaryComponentTick.bCanEverTick = true;

	bModeIsActive = false;
}


// Called when the game starts
void UAbstractMode::BeginPlay () {
	Super::BeginPlay();

	// ...

}


// Called every frame
void UAbstractMode::TickComponent (
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction *ThisTickFunction
) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
