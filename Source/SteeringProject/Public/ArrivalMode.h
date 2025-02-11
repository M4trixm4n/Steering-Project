// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SeekMode.h"
#include "ArrivalMode.generated.h"

/**
 * 
 */
UCLASS()
class STEERINGPROJECT_API UArrivalMode: public UAbstractMode {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	double SlowingDistance = 500.f;

protected:
	virtual FVector ComputeNewVector() override;
};
