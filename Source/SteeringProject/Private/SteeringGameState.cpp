// Fill out your copyright notice in the Description page of Project Settings.


#include "SteeringGameState.h"

void ASteeringGameState::SetTarget(const FVector NewTarget) {
	Target = NewTarget;
}

FVector ASteeringGameState::GetTarget() const {
	return Target;
}
