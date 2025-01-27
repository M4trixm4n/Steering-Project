// Fill out your copyright notice in the Description page of Project Settings.


#include "EvadeMode.h"

FVector UEvadeMode::ComputeNewVector() {
	return Super::ComputeNewVector() * -1;
}
