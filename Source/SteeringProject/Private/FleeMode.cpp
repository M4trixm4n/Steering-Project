// Fill out your copyright notice in the Description page of Project Settings.


#include "FleeMode.h"

FVector3d UFleeMode::ComputeNewVector () {
	return Super::ComputeNewVector() * -1;
}
