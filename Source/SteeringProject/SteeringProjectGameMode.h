// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Victim.h"
#include "GameFramework/GameModeBase.h"
#include "SteeringProjectGameMode.generated.h"

UCLASS(minimalapi)
class ASteeringProjectGameMode: public AGameModeBase {
	GENERATED_BODY()

public:
	ASteeringProjectGameMode();

	UFUNCTION(BlueprintImplementableEvent)
	TArray<AVictim *> GetVictims () const;
	
};
