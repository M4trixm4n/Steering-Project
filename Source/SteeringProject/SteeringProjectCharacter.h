// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SteeringProjectCharacter.generated.h"

UCLASS(Blueprintable)
class ASteeringProjectCharacter: public ACharacter {
	GENERATED_BODY()

public:
	ASteeringProjectCharacter();
	
	UPROPERTY(EditAnywhere)
	float Mass = 50.0f;
	UPROPERTY(EditAnywhere)
	float MaxForce = 400.0f;
	UPROPERTY(EditAnywhere)
	float MaxSpeed = 400.0f;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

};
