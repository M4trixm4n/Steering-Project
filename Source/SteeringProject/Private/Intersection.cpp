// Fill out your copyright notice in the Description page of Project Settings.


#include "Intersection.h"

AIntersection::AIntersection() {
	PrimaryActorTick.bCanEverTick = true;

}

void AIntersection::BeginPlay() {
	Super::BeginPlay();

}

void AIntersection::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

FVector AIntersection::GetFromSouthPoint() const {
	return FVector(GetActorLocation().X - 150, GetActorLocation().Y + 75, 0);
}

FVector AIntersection::GetFromWestPoint() const {
	return FVector(GetActorLocation().X - 75, GetActorLocation().Y - 150, 0);
}

FVector AIntersection::GetFromNorthPoint() const {
	return FVector(GetActorLocation().X + 150, GetActorLocation().Y - 75, 0);
}

FVector AIntersection::GetFromEastPoint() const {
	return FVector(GetActorLocation().X + 75, GetActorLocation().Y + 150, 0);
}

FVector AIntersection::GetToSouthPoint() const {
	return FVector(GetActorLocation().X - 150, GetActorLocation().Y - 75, 0);
}

FVector AIntersection::GetToWestPoint() const {
	return FVector(GetActorLocation().X + 75, GetActorLocation().Y - 150, 0);
}

FVector AIntersection::GetToNorthPoint() const {
	return FVector(GetActorLocation().X + 150, GetActorLocation().Y + 75, 0);
}

FVector AIntersection::GetToEastPoint() const {
	return FVector(GetActorLocation().X - 75, GetActorLocation().Y + 150, 0);
}

FVector AIntersection::GetSouthWestPoint() const {
	return FVector(GetActorLocation().X - 75, GetActorLocation().Y - 75, 0);
}

FVector AIntersection::GetNorthWestPoint() const {
	return FVector(GetActorLocation().X + 75, GetActorLocation().Y - 75, 0);
}

FVector AIntersection::GetNorthEastPoint() const {
	return FVector(GetActorLocation().X + 75, GetActorLocation().Y + 75, 0);
}

FVector AIntersection::GetSouthEastPoint() const {
	return FVector(GetActorLocation().X - 75, GetActorLocation().Y + 75, 0);
}

bool AIntersection::DirectionExists(const EDirection Direction) const {
	switch (Direction) {
		case EDirection::North:
			return North != nullptr;
		case EDirection::East:
			return East != nullptr;
		case EDirection::South:
			return South != nullptr;
		case EDirection::West:
			return West != nullptr;
		case EDirection::None:
			return true;
	}
	return false;
}

bool AIntersection::GoingStraight(EDirection CurrentDirection, EDirection NextDirection) {
	return CurrentDirection == NextDirection;
}

bool AIntersection::TurningLeft(EDirection CurrentDirection, EDirection NextDirection) {
	return static_cast<int>(CurrentDirection) - 1 == static_cast<int>(NextDirection) || (CurrentDirection ==
		EDirection::North && NextDirection == EDirection::West);
}

bool AIntersection::TurningRight(EDirection CurrentDirection, EDirection NextDirection) {
	return static_cast<int>(CurrentDirection) + 1 == static_cast<int>(NextDirection) || (CurrentDirection ==
		EDirection::West && NextDirection == EDirection::North);
}

TArray<AIntersection::FAction> AIntersection::GetIntersectionActions(EDirection CurrentDirection,
                                                                     EDirection NextDirection
		) const {

	TArray<FAction> Actions;

	if (NextDirection == EDirection::None) {
		switch (CurrentDirection) {
			case EDirection::North:
				Actions.Add({ENeededMode::Arrival, GetFromSouthPoint()});
			break;
			case EDirection::East:
				Actions.Add({ENeededMode::Arrival, GetFromWestPoint()});
			break;
			case EDirection::South:
				Actions.Add({ENeededMode::Arrival, GetFromNorthPoint()});
			break;
			case EDirection::West:
				Actions.Add({ENeededMode::Arrival, GetFromEastPoint()});
			break;
			case EDirection::None:
				break;
		}
		return Actions;
	}
	
	if (!DirectionExists(NextDirection)) return Actions;

	ENeededMode InitialApproach = ENeededMode::Arrival;
	if (GoingStraight(CurrentDirection, NextDirection)) {
		InitialApproach = ENeededMode::Seek;
	}

	switch (CurrentDirection) {
		case EDirection::North:
			Actions.Add({InitialApproach, GetFromSouthPoint()});
			break;
		case EDirection::East:
			Actions.Add({InitialApproach, GetFromWestPoint()});
			break;
		case EDirection::South:
			Actions.Add({InitialApproach, GetFromNorthPoint()});
			break;
		case EDirection::West:
			Actions.Add({InitialApproach, GetFromEastPoint()});
			break;
		case EDirection::None:
			break;
	}

	// if (!GoingStraight(CurrentDirection, NextDirection)) {
	if (TurningLeft(CurrentDirection, NextDirection)) {
		switch (CurrentDirection) {
			case EDirection::North:
				Actions.Add({ENeededMode::Arrival, GetSouthEastPoint()});
				break;
			case EDirection::East:
				Actions.Add({ENeededMode::Arrival, GetSouthWestPoint()});
				break;
			case EDirection::South:
				Actions.Add({ENeededMode::Arrival, GetNorthWestPoint()});
				break;
			case EDirection::West:
				Actions.Add({ENeededMode::Arrival, GetNorthEastPoint()});
				break;
			case EDirection::None:
				break;
		}
	}

	// if (TurningLeft(CurrentDirection, NextDirection)) {
	// 	switch (CurrentDirection) {
	// 		case EDirection::North:
	// 			Actions.Add({ENeededMode::Arrival, GetNorthWestPoint()});
	// 			break;
	// 		case EDirection::East:
	// 			Actions.Add({ENeededMode::Arrival, GetNorthEastPoint()});
	// 			break;
	// 		case EDirection::South:
	// 			Actions.Add({ENeededMode::Arrival, GetSouthEastPoint()});
	// 			break;
	// 		case EDirection::West:
	// 			Actions.Add({ENeededMode::Arrival, GetSouthWestPoint()});
	// 			break;
	// 		case EDirection::None:
	// 			break;
	// 	}
	// }

	switch (NextDirection) {
		case EDirection::North:
			Actions.Add({InitialApproach, GetToNorthPoint()});
			break;
		case EDirection::East:
			Actions.Add({InitialApproach, GetToEastPoint()});
			break;
		case EDirection::South:
			Actions.Add({InitialApproach, GetToSouthPoint()});
			break;
		case EDirection::West:
			Actions.Add({InitialApproach, GetToWestPoint()});
			break;
		case EDirection::None:
			break;
	}

	return Actions;
}

AIntersection *AIntersection::GetIntersectionInDirection(EDirection Direction) const {
	switch (Direction) {
		case EDirection::North:
			return North;
		case EDirection::East:
			return East;
		case EDirection::South:
			return South;
		case EDirection::West:
			return West;
		case EDirection::None:
			return nullptr;
	}
	return nullptr;
}
