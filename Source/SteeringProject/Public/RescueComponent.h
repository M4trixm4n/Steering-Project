// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RescueComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEERINGPROJECT_API URescueComponent: public UActorComponent {
	GENERATED_BODY()

public:
	URescueComponent();

protected:
	virtual void BeginPlay() override;

public:
	FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(250.0f);
	TArray<FHitResult> OutResults;
	bool bCarryingVictim = false;
	
	virtual void TickComponent(float DeltaTime,
	                           ELevelTick TickType,
	                           FActorComponentTickFunction *ThisTickFunction
			) override;

};
