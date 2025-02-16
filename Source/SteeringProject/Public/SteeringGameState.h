// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArrivalMode.h"
#include "CircuitMode.h"
#include "EvadeMode.h"
#include "FleeMode.h"
#include "OneWayMode.h"
#include "PursuitMode.h"
#include "SeekMode.h"
#include "TwoWayMode.h"
#include "GameFramework/GameStateBase.h"
#include "SteeringGameState.generated.h"

/**
 * 
 */
UCLASS()
class STEERINGPROJECT_API ASteeringGameState: public AGameStateBase {
	GENERATED_BODY()

public:
	FVector Target;

	void SetTarget(const FVector NewTarget);
	FVector GetTarget() const;

	FVector PreviousVelocity;

	TArray<FVector> CircuitPoints;
	int CircuitPointIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ModeComponents")
	USeekMode* SeekMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ModeComponents")
	UFleeMode* FleeMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ModeComponents")
	UPursuitMode* PursuitMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ModeComponents")
	UEvadeMode* EvadeMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ModeComponents")
	UArrivalMode* ArrivalMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ModeComponents")
	UCircuitMode* CircuitMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ModeComponents")
	UOneWayMode* OneWayMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ModeComponents")
	UTwoWayMode* TwoWayMode;

};
