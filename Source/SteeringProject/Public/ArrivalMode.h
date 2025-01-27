// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SeekMode.h"
#include "ArrivalMode.generated.h"

/**
 * 
 */
UCLASS()
class STEERINGPROJECT_API UArrivalMode: public USeekMode {
	GENERATED_BODY()

protected:
	virtual FVector ComputeNewVector() override;
};
