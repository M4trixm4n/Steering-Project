// Copyright Epic Games, Inc. All Rights Reserved.

#include "SteeringProjectCharacter.h"
#include "SteeringProjectGameMode.h"
#include "VectorTypes.h"
#include "UObject/ConstructorHelpers.h"
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
	SeekComp        = CreateDefaultSubobject<USeekMode>(TEXT("SeekMode"));
	ArrivalComp     = CreateDefaultSubobject<UArrivalMode>(TEXT("ArrivalMode"));
	RescueComp      = CreateDefaultSubobject<URescueComponent>(TEXT("Rescue"));
}

void ASteeringProjectCharacter::ChooseNextVictim() {
	auto Victims = Cast<ASteeringProjectGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetVictims();
	if (Victims.Num() < 3) return;
	auto Dist1 = UE::Geometry::Distance(GetActorLocation(), Victims[0]->GetActorLocation());
	auto Dist2 = UE::Geometry::Distance(GetActorLocation(), Victims[1]->GetActorLocation());
	auto Dist3 = UE::Geometry::Distance(GetActorLocation(), Victims[2]->GetActorLocation());
	if (Dist1 < Dist2 && Dist1 < Dist3) ChosenVictim = Victims[0];
	else if (Dist2 < Dist1 && Dist2 < Dist3) ChosenVictim = Victims[1];
	else ChosenVictim = Victims[2];
}

void ASteeringProjectCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	auto Victims = Cast<ASteeringProjectGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetVictims();

	if (RescueComp->bCarryingVictim) {
		auto Dist1                  = UE::Geometry::Distance(GetActorLocation(), HospitalRoads[0]->GetActorLocation());
		auto Dist2                  = UE::Geometry::Distance(GetActorLocation(), HospitalRoads[1]->GetActorLocation());
		PathFindingComp->TargetRoad = (Dist1 < Dist2) ? HospitalRoads[0] : HospitalRoads[1];
		ChosenVictim = nullptr;
	} else {
		if (!Victims.IsEmpty() && !IsValid(ChosenVictim)) {
			ChooseNextVictim();
			if (!IsValid(ChosenVictim)) return;
			auto FoundActors = TArray<AActor *>();
			ChosenVictim->GetOverlappingActors(FoundActors, {ARoad::StaticClass()});
			PathFindingComp->TargetRoad = Cast<ARoad>(FoundActors[0]);
		}
	}
}

void ASteeringProjectCharacter::BeginPlay() {
	Super::BeginPlay();

	TArray<AActor *> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("AIStart"), FoundActors);
	if (FoundActors.Num() > 0) {
		PathFindingComp->CurrentIntersection = Cast<AIntersection>(FoundActors[0])->East;
		PathFindingComp->CurrentDirection    = EDirection::East;
	}
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Hospital"), FoundActors);
	if (FoundActors.Num() == 2) {
		HospitalRoads[0] = Cast<ARoad>(FoundActors[0]);
		HospitalRoads[1] = Cast<ARoad>(FoundActors[1]);
	}
}
