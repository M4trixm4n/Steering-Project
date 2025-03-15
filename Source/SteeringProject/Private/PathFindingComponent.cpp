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
	
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, CurrentAction.Destination.ToString());
	if (Path.Num() == 0) {
		FindPath();
		TargetRoad = nullptr;
	}
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, std::to_string(UE::Geometry::Distance(CurrentAction.Destination,
							   {GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, 0.f})).c_str());
	if (UE::Geometry::Distance(CurrentAction.Destination,
	                           {GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, 0.f}) < 60) {
		CurrentAction.Destination = FVector::ZeroVector;
	}
	if (Actions.IsEmpty() && !Path.IsEmpty()) {
		Path.RemoveAt(0);
		DrawDebugPoint(GetWorld(), CurrentIntersection->GetActorLocation(), 10.0f, FColor::Blue, false, 30.f);
		if (!Path.IsEmpty()) {
			Actions = CurrentIntersection->GetIntersectionActions(CurrentDirection, Path[0]);
			CurrentDirection = Path[0];
			CurrentIntersection = CurrentIntersection->GetIntersectionInDirection(CurrentDirection);
		} else {
			Actions = CurrentIntersection->GetIntersectionActions(CurrentDirection, EDirection::None);
			// CurrentIntersection = CurrentIntersection->GetIntersectionInDirection(CurrentDirection);
			// CurrentDirection = Path[0];
		}
	}
	if (!CurrentAction && !Actions.IsEmpty()) {
		CurrentAction = Actions[0];
		Actions.RemoveAt(0);
		EnableCorrectMode();
		Target = CurrentAction.Destination;
	}
}

void UPathFindingComponent::FindPath() {
	if (!TargetRoad) return;
	TArray<FPath> Paths = {{TArray({CurrentIntersection}), 0.0f}};
	while (true) {
		Actions;
		FPath Shortest = Paths[0];
		Paths.RemoveAt(0);
		// if reached target do stuff
		if (Shortest.Path.Last() == TargetRoad->Intersection1 || Shortest.Path.Last() == TargetRoad->Intersection2) {
			if (Shortest.Path.Last() == TargetRoad->Intersection1) {
				Shortest.Path.Add(TargetRoad->Intersection2);
			} else if (Shortest.Path.Last() == TargetRoad->Intersection2) {
				Shortest.Path.Add(TargetRoad->Intersection1);
			}
			Path = ConvertPathToDirection(Shortest);
			// Actions.Empty();
			return;
		}
		// add paths to each adjacent intersection
		FPath TmpShortest;
		if (Shortest.Path.Last()->North && !Shortest.Path.Contains(Shortest.Path.Last()->North)) {
			TmpShortest = Shortest.Copy();
			TmpShortest.Cost += UE::Geometry::Distance(Shortest.Path.Last()->GetActorLocation(),
			                                           Shortest.Path.Last()->North->GetActorLocation());
			TmpShortest.Path.Add(Shortest.Path.Last()->North);
			Paths.Add(TmpShortest);
		}
		if (Shortest.Path.Last()->East && !Shortest.Path.Contains(Shortest.Path.Last()->East)) {
			TmpShortest = Shortest.Copy();
			TmpShortest.Cost += UE::Geometry::Distance(Shortest.Path.Last()->GetActorLocation(),
			                                           Shortest.Path.Last()->East->GetActorLocation());
			TmpShortest.Path.Add(Shortest.Path.Last()->East);
			Paths.Add(TmpShortest);
		}
		if (Shortest.Path.Last()->South && !Shortest.Path.Contains(Shortest.Path.Last()->South)) {
			TmpShortest = Shortest.Copy();
			TmpShortest.Cost += UE::Geometry::Distance(Shortest.Path.Last()->GetActorLocation(),
			                                           Shortest.Path.Last()->South->GetActorLocation());
			TmpShortest.Path.Add(Shortest.Path.Last()->South);
			Paths.Add(TmpShortest);
		}
		if (Shortest.Path.Last()->West && !Shortest.Path.Contains(Shortest.Path.Last()->West)) {
			TmpShortest = Shortest.Copy();
			TmpShortest.Cost += UE::Geometry::Distance(Shortest.Path.Last()->GetActorLocation(),
			                                           Shortest.Path.Last()->West->GetActorLocation());
			TmpShortest.Path.Add(Shortest.Path.Last()->West);
			Paths.Add(TmpShortest);
		}
		// sort Paths
		Paths.Sort();
	}
}

TArray<EDirection> UPathFindingComponent::ConvertPathToDirection(FPath NewPath) const {
	TArray<EDirection> Directions = {};
	Directions.Add(CurrentDirection);

	AIntersection *Current = nullptr;
	if (NewPath.Path[0]) Current = NewPath.Path[0];
	for (int i = 1; i < NewPath.Path.Num(); i++) {
		if (Current == NewPath.Path[i]->North) Directions.Add(EDirection::South);
		else if (Current == NewPath.Path[i]->East) Directions.Add(EDirection::West);
		else if (Current == NewPath.Path[i]->South) Directions.Add(EDirection::North);
		else if (Current == NewPath.Path[i]->West) Directions.Add(EDirection::East);
		else {
		}
		Current = NewPath.Path[i];
	}

	return Directions;
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
