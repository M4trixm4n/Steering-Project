// Copyright Epic Games, Inc. All Rights Reserved.

#include "SteeringProjectPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "SteeringProjectCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "SteeringGameState.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ASteeringProjectPlayerController::ASteeringProjectPlayerController() {
	bShowMouseCursor   = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination  = FVector::ZeroVector;
	FollowTime         = 0.f;
}

void ASteeringProjectPlayerController::BeginPlay() {
	// Call the base class  
	Super::BeginPlay();
	CachedDestination = FVector::ZeroVector;
	Cast<ASteeringGameState>(GetWorld()->GetGameState())->SetTarget(CachedDestination);
}

void ASteeringProjectPlayerController::SetupInputComponent() {
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			GetLocalPlayer())) {
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this,
		                                   &ASteeringProjectPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this,
		                                   &ASteeringProjectPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this,
		                                   &ASteeringProjectPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this,
		                                   &ASteeringProjectPlayerController::OnSetDestinationReleased);
	} else {
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void ASteeringProjectPlayerController::OnInputStarted() {
	StopMovement();
	
	FHitResult Hit;
	bool bHitSuccessful = false;

	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful) {
		CachedDestination = Hit.Location;
	}
	Cast<ASteeringGameState>(GetWorld()->GetGameState())->SetTarget(CachedDestination);
	ASteeringGameState *GameState = Cast<ASteeringGameState>(GetWorld()->GetGameState());
	if (GameState->CircuitMode->bModeIsActive || GameState->OneWayMode->bModeIsActive || GameState->TwoWayMode->bModeIsActive) {
		GameState->CircuitPoints.Add(CachedDestination);
	}
}

// Triggered every frame when the input is held down
void ASteeringProjectPlayerController::OnSetDestinationTriggered() {
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
}

void ASteeringProjectPlayerController::OnSetDestinationReleased() {
	// If it was a short press
	if (FollowTime <= ShortPressThreshold) {
		// We move there and spawn some particles
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator,
		                                               FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}
