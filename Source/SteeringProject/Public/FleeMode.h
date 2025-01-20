// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SeekMode.h"
#include "FleeMode.generated.h"

/**
 * 
 */
UCLASS()
class STEERINGPROJECT_API UFleeMode: public USeekMode {
	GENERATED_BODY()

protected:
	virtual FVector3d ComputeNewVector () override;

};
