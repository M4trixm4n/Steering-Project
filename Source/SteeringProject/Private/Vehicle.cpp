// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle.h"

#include "AbstractMode.h"
#include "ArrivalMode.h"
#include "EvadeMode.h"
#include "FleeMode.h"
#include "LevelEditor.h"
#include "PursuitMode.h"
#include "SeekMode.h"
#include "SteeringGameState.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AVehicle::AVehicle () {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	Camera->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	Camera->SetWorldLocation(FVector(0, 0, 4000));
}

// Called when the game starts or when spawned
void AVehicle::BeginPlay () {

	UActorComponent *SeekComp = NewObject<UActorComponent>(this, USeekMode::StaticClass(), "SeekMode");
	SeekComp->RegisterComponent();
	this->AddInstanceComponent(SeekComp);
	UActorComponent *FleeComp = NewObject<UActorComponent>(this, UFleeMode::StaticClass(), "FleeMode");
	FleeComp->RegisterComponent();
	this->AddInstanceComponent(FleeComp);
	UActorComponent *ArrivalComp = NewObject<UActorComponent>(this, UArrivalMode::StaticClass(), "ArrivalMode");
	ArrivalComp->RegisterComponent();
	this->AddInstanceComponent(ArrivalComp);
	
	// Broadcast edit notifications so that level editor details are refreshed (e.g. components tree)
	FLevelEditorModule& LevelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	LevelEditor.BroadcastComponentsEdited();

	ASteeringGameState* GameState = Cast<ASteeringGameState>(GetWorld()->GetGameState());
	GameState->SeekMode = Cast<USeekMode>(SeekComp);
	GameState->FleeMode = Cast<UFleeMode>(FleeComp);
	GameState->ArrivalMode = Cast<UArrivalMode>(ArrivalComp);

}

// Called every frame
void AVehicle::Tick (float DeltaTime) {
	Super::Tick(DeltaTime);

}
