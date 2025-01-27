// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractMode.h"
#include "SeekMode.generated.h"

/**
 * 
 */
UCLASS()
class STEERINGPROJECT_API USeekMode: public UAbstractMode {
	GENERATED_BODY()

protected:
	virtual FVector ComputeNewVector() override;

};
