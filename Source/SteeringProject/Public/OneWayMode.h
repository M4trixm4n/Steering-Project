// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CircuitMode.h"
#include "OneWayMode.generated.h"

/**
 * 
 */
UCLASS()
class STEERINGPROJECT_API UOneWayMode: public UCircuitMode {
	GENERATED_BODY()

protected:
	virtual FVector ComputeNewVector() override;
};
