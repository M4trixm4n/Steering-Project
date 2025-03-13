// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbstractMode.generated.h"


UCLASS(meta=(BlueprintSpawnableComponent), Abstract)
class UAbstractMode: public UActorComponent {
	GENERATED_BODY()

public:
	UAbstractMode ();

	UPROPERTY(EditAnywhere)
	bool bModeIsActive;
	UPROPERTY(EditAnywhere)
	FVector Target;
	UFUNCTION(BlueprintCallable)
	void DisableMode();
	UFUNCTION(BlueprintCallable)
	void EnableMode();

protected:
	virtual void BeginPlay () override;


	FVector PreviousVelocity = {0, 0, 0};

	virtual FVector ComputeNewVector() PURE_VIRTUAL(UAbstractMode::ComputeNewVector, {return {0, 0, 0};});

public:
	virtual void TickComponent (
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction *ThisTickFunction
	) override;


};
