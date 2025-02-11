// Copyright Epic Games, Inc. All Rights Reserved.

#include "SteeringProjectGameMode.h"

#include "SteeringGameState.h"
#include "SteeringProjectPlayerController.h"
#include "SteeringProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASteeringProjectGameMode::ASteeringProjectGameMode() {
	// use our custom PlayerController class
	PlayerControllerClass = ASteeringProjectPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
			TEXT("/Game/Steering/BP_Vehicle"));
	if (PlayerPawnBPClass.Class != nullptr) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(
			TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if (PlayerControllerBPClass.Class != NULL) {
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	GameStateClass = ASteeringGameState::StaticClass();
}
