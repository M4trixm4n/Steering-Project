// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArrivalMode.h"
#include "Directions.h"
#include "Intersection.h"
#include "Road.h"
#include "Components/ActorComponent.h"
#include "PathFindingComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEERINGPROJECT_API UPathFindingComponent: public UActorComponent {
	GENERATED_BODY()

	struct FPath {
		TArray<AIntersection *> Path;
		float Cost;

		FPath Copy () const {
			return FPath(Path, Cost);
		}

		bool operator< (const FPath &Other) const {
			return Cost < Other.Cost;
		}
	};

public:
	UPathFindingComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	USeekMode *SeekComp = nullptr;
	UPROPERTY()
	UArrivalMode *ArrivalComp = nullptr;
	bool bIsPlayer = false;

public:
	virtual void TickComponent(float DeltaTime,
	                           ELevelTick TickType,
	                           FActorComponentTickFunction *ThisTickFunction
			) override;

	UPROPERTY()
	AIntersection *CurrentIntersection = nullptr;
	
	EDirection CurrentDirection = EDirection::North;
	TArray<EDirection> Path;
	TArray<AIntersection::FAction> Actions;
	AIntersection::FAction CurrentAction = {};
	
	void FindPath();
	TArray<EDirection> ConvertPathToDirection(FPath NewPath) const;
	void EnableCorrectMode () const;

	FVector PreviousVelocity;
	FVector Target;
	UPROPERTY()
	ARoad *TargetRoad = nullptr;
	
};
