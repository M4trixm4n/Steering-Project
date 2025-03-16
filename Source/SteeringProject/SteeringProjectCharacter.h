// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArrivalMode.h"
#include "PathFindingComponent.h"
#include "RescueComponent.h"
#include "SeekMode.h"
#include "Victim.h"
#include "SteeringProjectCharacter.generated.h"

UCLASS(Blueprintable)
class ASteeringProjectCharacter: public APawn {
	GENERATED_BODY()

public:
	ASteeringProjectCharacter();
	
	UPROPERTY(EditAnywhere)
	float Mass = 50.0f;
	UPROPERTY(EditAnywhere)
	float MaxForce = 400.0f;
	UPROPERTY(EditAnywhere)
	float MaxSpeed = 400.0f;
	
	UPROPERTY(BlueprintReadOnly)
	USeekMode *SeekComp;

	UPROPERTY(BlueprintReadOnly)
	UArrivalMode *ArrivalComp;
	
	UPROPERTY(BlueprintReadOnly)
	URescueComponent *RescueComp;
	
	UPROPERTY(EditAnywhere)
	UPathFindingComponent *PathFindingComp;

	ARoad *HospitalRoads[2];
	void ChooseNextVictim ();
	UPROPERTY()
	AVictim *ChosenVictim = nullptr;

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

};
