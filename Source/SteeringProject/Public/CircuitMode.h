// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractMode.h"
#include "CircuitMode.generated.h"

/**
 * 
 */
UCLASS()
class STEERINGPROJECT_API UCircuitMode: public UAbstractMode {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ResetCircuit ();

	UFUNCTION(BlueprintCallable)
	virtual void RestartCircuit ();

protected:
	virtual FVector ComputeNewVector() override;
};
