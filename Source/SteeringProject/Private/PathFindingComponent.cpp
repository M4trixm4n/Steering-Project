// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFindingComponent.h"

#include "VectorTypes.h"
#include "Vehicle.h"
#include "SteeringProject/SteeringProjectCharacter.h"


UPathFindingComponent::UPathFindingComponent() {
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate                     = true;
}

void UPathFindingComponent::BeginPlay() {
	Super::BeginPlay();

	AVehicle *Player = Cast<AVehicle>(GetOwner());
	if (Player) {
		bIsPlayer   = true;
		SeekComp    = Player->SeekComp;
		ArrivalComp = Player->ArrivalComp;
	} else {
		ASteeringProjectCharacter *AI = Cast<ASteeringProjectCharacter>(GetOwner());
		SeekComp                      = AI->SeekComp;
		ArrivalComp                   = AI->ArrivalComp;
	}
}

void UPathFindingComponent::TickComponent(float DeltaTime,
                                          ELevelTick TickType,
                                          FActorComponentTickFunction *ThisTickFunction
		) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Path.Num() <= 1) FindPath();
	if (Actions.IsEmpty()) {
		CurrentIntersection = CurrentIntersection->GetIntersectionInDirection(CurrentDirection);
		Path.RemoveAt(0);
		Actions             = CurrentIntersection->GetIntersectionActions(CurrentDirection, Path[0]);
		CurrentDirection    = Path[0];
		DrawDebugPoint(GetWorld(), CurrentIntersection->GetActorLocation(), 10.0f, FColor::Blue, false, 30.f);
	}
	if (!CurrentAction) {
		CurrentAction = Actions[0];
		Actions.RemoveAt(0);
		EnableCorrectMode();
		Target = CurrentAction.Destination;
	}
	if (UE::Geometry::Distance(CurrentAction.Destination,
	                           {GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, 0.f}) < 60) {
		CurrentAction.Destination = FVector::ZeroVector;
	}
}

void UPathFindingComponent::FindPath() {
	Path.Append({EDirection::North, EDirection::West, EDirection::South, EDirection::East});
}

void UPathFindingComponent::EnableCorrectMode() const {
	if (CurrentAction.Mode == AIntersection::ENeededMode::Seek) {
		SeekComp->EnableMode();
		ArrivalComp->DisableMode();
	} else if (CurrentAction.Mode == AIntersection::ENeededMode::Arrival) {
		ArrivalComp->EnableMode();
		SeekComp->DisableMode();
	}
}
