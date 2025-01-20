// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle.h"

#include "AbstractMode.h"
#include "ArrivalMode.h"
#include "EvadeMode.h"
#include "FleeMode.h"
#include "LevelEditor.h"
#include "PursuitMode.h"
#include "SeekMode.h"

// Sets default values
AVehicle::AVehicle () {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVehicle::BeginPlay () {

	UActorComponent *SeekComp = NewObject<UActorComponent>(this, USeekMode::StaticClass(), "SeekMode");
	SeekComp->RegisterComponent();
	this->AddInstanceComponent(SeekComp);
	UActorComponent *FleeComp = NewObject<UActorComponent>(this, UFleeMode::StaticClass(), "FleeMode");
	FleeComp->RegisterComponent();
	this->AddInstanceComponent(FleeComp);
	UActorComponent *PursuitComp = NewObject<UActorComponent>(this, UPursuitMode::StaticClass(), "PursuitMode");
	PursuitComp->RegisterComponent();
	this->AddInstanceComponent(PursuitComp);
	UActorComponent *EvadeComp = NewObject<UActorComponent>(this, UEvadeMode::StaticClass(), "EvadeMode");
	EvadeComp->RegisterComponent();
	this->AddInstanceComponent(EvadeComp);
	UActorComponent *ArrivalComp = NewObject<UActorComponent>(this, UArrivalMode::StaticClass(), "ArrivalMode");
	ArrivalComp->RegisterComponent();
	this->AddInstanceComponent(ArrivalComp);
	
	// Broadcast edit notifications so that level editor details are refreshed (e.g. components tree)
	FLevelEditorModule& LevelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	LevelEditor.BroadcastComponentsEdited();
}

// Called every frame
void AVehicle::Tick (float DeltaTime) {
	Super::Tick(DeltaTime);

}
