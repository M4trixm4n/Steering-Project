// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle.h"

#include "AbstractMode.h"
#include "ArrivalMode.h"
#include "EvadeMode.h"
#include "FleeMode.h"
#include "PursuitMode.h"
#include "SeekMode.h"

// Sets default values
AVehicle::AVehicle () {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVehicle::BeginPlay () {
	Super::BeginPlay();

	UActorComponent *SeekComp     = AActor::AddComponentByClass(USeekMode::StaticClass(), false, FTransform(), true);
	AActor::FinishAddComponent(SeekComp, false, FTransform());
	UActorComponent *FleeComp = AActor::AddComponentByClass(UFleeMode::StaticClass(), false, FTransform(), true);
	AActor::FinishAddComponent(FleeComp, false, FTransform());
	UActorComponent *PursuitComp = AActor::AddComponentByClass(UPursuitMode::StaticClass(), false, FTransform(), true);
	AActor::FinishAddComponent(PursuitComp, false, FTransform());
	UActorComponent *EvadeComp = AActor::AddComponentByClass(UEvadeMode::StaticClass(), false, FTransform(), true);
	AActor::FinishAddComponent(EvadeComp, false, FTransform());
	UActorComponent *ArrivalComp = AActor::AddComponentByClass(UArrivalMode::StaticClass(), false, FTransform(), true);
	AActor::FinishAddComponent(ArrivalComp, false, FTransform());
}

// Called every frame
void AVehicle::Tick (float DeltaTime) {
	Super::Tick(DeltaTime);

}
