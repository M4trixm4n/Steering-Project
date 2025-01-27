// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbstractMode.generated.h"


UCLASS(meta=(BlueprintSpawnableComponent), Abstract)
class UAbstractMode: public UActorComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbstractMode ();

	UPROPERTY(EditAnywhere)
	bool bModeIsActive;
	UPROPERTY(EditAnywhere)
	FVector Target;

protected:
	// Called when the game starts
	virtual void BeginPlay () override;

	virtual FVector ComputeNewVector() PURE_VIRTUAL(UAbstractMode::ComputeNewVector, {return {0, 0, 0};});
	UFUNCTION(BlueprintCallable)
	void DisableMode();
	UFUNCTION(BlueprintCallable)
	void EnableMode();

public:
	// Called every frame
	virtual void TickComponent (
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction *ThisTickFunction
	) override;


};
