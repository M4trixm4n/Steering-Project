// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CircuitMode.h"
#include "TwoWayMode.generated.h"

/**
 * 
 */
UCLASS()
class STEERINGPROJECT_API UTwoWayMode: public UCircuitMode {
	GENERATED_BODY()

protected:
	virtual FVector ComputeNewVector() override;

public:
	virtual void RestartCircuit() override;

protected:
	bool FirstTrip = true;
};
