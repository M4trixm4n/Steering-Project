// Copyright Epic Games, Inc. All Rights Reserved.

#include "SteeringProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ASteeringProjectCharacter::ASteeringProjectCharacter() {
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw   = false;
	bUseControllerRotationRoll  = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate              = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane         = true;
	GetCharacterMovement()->bSnapToPlaneAtStart       = true;

	PrimaryActorTick.bCanEverTick          = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASteeringProjectCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

void ASteeringProjectCharacter::BeginPlay() {
	Super::BeginPlay();
	
	UActorComponent *Seek = NewObject<UActorComponent>(this, USeekMode::StaticClass(), "SeekMode");
	Seek->RegisterComponent();
	this->AddInstanceComponent(Seek);
	UActorComponent *Arrival = NewObject<UActorComponent>(this, UArrivalMode::StaticClass(), "ArrivalMode");
	Arrival->RegisterComponent();
	this->AddInstanceComponent(Arrival);
	
	SeekComp = Cast<USeekMode>(Seek);
	ArrivalComp = Cast<UArrivalMode>(Arrival);
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("AIStart"), FoundActors);
	if (FoundActors.Num() > 0) {
		PathFindingComp->CurrentIntersection = Cast<AIntersection>(FoundActors[0]);
	}
}
