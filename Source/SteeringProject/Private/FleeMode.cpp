// Fill out your copyright notice in the Description page of Project Settings.


#include "FleeMode.h"

FVector UFleeMode::ComputeNewVector() {
	return Super::ComputeNewVector() * -1;
}
