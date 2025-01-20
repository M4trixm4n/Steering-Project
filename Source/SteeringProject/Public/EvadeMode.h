// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PursuitMode.h"
#include "EvadeMode.generated.h"

/**
 * 
 */
UCLASS()
class STEERINGPROJECT_API UEvadeMode: public UPursuitMode {
	GENERATED_BODY()

protected:
	virtual FVector3d ComputeNewVector () override;
};
