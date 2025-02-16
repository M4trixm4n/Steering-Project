// Copyright Epic Games, Inc. All Rights Reserved.

#include "SteeringProjectCharacter.h"

#include "EvadeMode.h"
// #include "LevelEditor.h"
#include "PursuitMode.h"
#include "SteeringGameState.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ASteeringProjectCharacter::ASteeringProjectCharacter() {
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw   = false;
	bUseControllerRotationRoll  = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate              = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane         = true;
	GetCharacterMovement()->bSnapToPlaneAtStart       = true;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick          = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASteeringProjectCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

void ASteeringProjectCharacter::BeginPlay() {
	Super::BeginPlay();
	
	UActorComponent *PursuitComp = NewObject<UActorComponent>(this, UPursuitMode::StaticClass(), "PursuitMode");
	PursuitComp->RegisterComponent();
	this->AddInstanceComponent(PursuitComp);
	UActorComponent *EvadeComp = NewObject<UActorComponent>(this, UEvadeMode::StaticClass(), "EvadeMode");
	EvadeComp->RegisterComponent();
	this->AddInstanceComponent(EvadeComp);
	
	// FLevelEditorModule& LevelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	// LevelEditor.BroadcastComponentsEdited();

	ASteeringGameState* GameState = Cast<ASteeringGameState>(GetWorld()->GetGameState());
	GameState->PursuitMode = Cast<UPursuitMode>(PursuitComp);
	GameState->EvadeMode = Cast<UEvadeMode>(EvadeComp);
}
