// Fill out your copyright notice in the Description page of Project Settings.


#include "EvadeMode.h"

FVector3d UEvadeMode::ComputeNewVector () {
	return Super::ComputeNewVector() * -1;
}
