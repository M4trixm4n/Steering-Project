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

	PrimaryActorTick.bCanEverTick          = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	PathFindingComp = CreateDefaultSubobject<UPathFindingComponent>(TEXT("PathFinding"));
	SeekComp = CreateDefaultSubobject<USeekMode>(TEXT("SeekMode"));
	ArrivalComp = CreateDefaultSubobject<UArrivalMode>(TEXT("ArrivalMode"));
}

void ASteeringProjectCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

void ASteeringProjectCharacter::BeginPlay() {
	Super::BeginPlay();
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("AIStart"), FoundActors);
	if (FoundActors.Num() > 0) {
		PathFindingComp->CurrentIntersection = Cast<AIntersection>(FoundActors[0]);
	}
}
