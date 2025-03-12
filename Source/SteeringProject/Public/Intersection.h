// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Directions.h"
#include "GameFramework/Actor.h"
#include "Intersection.generated.h"

UCLASS()
class STEERINGPROJECT_API AIntersection: public AActor {
	GENERATED_BODY()

public:
	enum class ENeededMode {
		Seek,
		Arrival,
		None
	};

	struct FAction {
		ENeededMode Mode;
		FVector Destination = FVector::ZeroVector;

		bool operator! () const {
			return Destination == FVector::ZeroVector;
		}
	};
	
	AIntersection();
	
	UPROPERTY(EditAnywhere)
	AIntersection *North = nullptr;
	UPROPERTY(EditAnywhere)
	AIntersection *East = nullptr;
	UPROPERTY(EditAnywhere)
	AIntersection *South = nullptr;
	UPROPERTY(EditAnywhere)
	AIntersection *West = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	FVector GetFromSouthPoint () const;
	FVector GetFromWestPoint () const;
	FVector GetFromNorthPoint () const;
	FVector GetFromEastPoint () const;
	FVector GetToSouthPoint () const;
	FVector GetToWestPoint () const;
	FVector GetToNorthPoint () const;
	FVector GetToEastPoint () const;
	FVector GetSouthWestPoint () const;
	FVector GetNorthWestPoint () const;
	FVector GetNorthEastPoint () const;
	FVector GetSouthEastPoint () const;

	bool DirectionExists (const EDirection Direction) const;
	static bool GoingStraight (EDirection CurrentDirection, EDirection NextDirection);
	static bool TurningLeft (EDirection CurrentDirection, EDirection NextDirection);
	static bool TurningRight (EDirection CurrentDirection, EDirection NextDirection);
	TArray<FAction> GetIntersectionActions (EDirection CurrentDirection, EDirection NextDirection) const;

	AIntersection *GetIntersectionInDirection (EDirection Direction) const;
	
};
