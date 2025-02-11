// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Vehicle.generated.h"

UCLASS(Blueprintable)
class STEERINGPROJECT_API AVehicle: public ACharacter {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVehicle ();

	UPROPERTY(EditAnywhere)
	float Mass = 50.0f;
	UPROPERTY(EditAnywhere)
	float MaxForce = 10.0f;
	UPROPERTY(EditAnywhere)
	float MaxSpeed = 500.0f;

	UPROPERTY(EditAnywhere)
	UCameraComponent * Camera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay () override;
	
public:
	// Called every frame
	virtual void Tick (float DeltaTime) override;

};
