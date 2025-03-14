// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Intersection.h"
#include "GameFramework/Actor.h"
#include "Road.generated.h"

UCLASS()
class STEERINGPROJECT_API ARoad: public AActor {
	GENERATED_BODY()

public:
	ARoad();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AIntersection *Intersection1 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AIntersection *Intersection2 = nullptr;

};
