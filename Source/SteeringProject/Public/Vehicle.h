// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArrivalMode.h"
#include "PathFindingComponent.h"
#include "SeekMode.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Vehicle.generated.h"

UCLASS(Blueprintable, BlueprintType)
class STEERINGPROJECT_API AVehicle: public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVehicle();

	UPROPERTY(EditAnywhere)
	float Mass = 40.0f;
	UPROPERTY(EditAnywhere)
	float MaxForce = 25.0f;
	UPROPERTY(EditAnywhere)
	float MaxSpeed = 400.0f;

	UPROPERTY(EditAnywhere)
	UCameraComponent *Camera;

	UPROPERTY(BlueprintReadOnly)
	USeekMode *SeekComp;

	UPROPERTY(BlueprintReadOnly)
	UArrivalMode *ArrivalComp;

	UPROPERTY(EditAnywhere)
	UPathFindingComponent *PathFindingComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
