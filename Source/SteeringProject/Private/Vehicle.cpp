// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle.h"
#include "ArrivalMode.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AVehicle::AVehicle () {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<UBoxComponent>("Root");
	RootComponent->SetRelativeLocation(FVector(-30, -30, 45));
	RootComponent->SetRelativeScale3D(FVector(2, 2, 2));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	Camera->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	Camera->SetWorldLocation(FVector(0, 0, 4000));

	PathFindingComp = CreateDefaultSubobject<UPathFindingComponent>(TEXT("PathFinding"));
	SeekComp = CreateDefaultSubobject<USeekMode>(TEXT("SeekMode"));
	ArrivalComp = CreateDefaultSubobject<UArrivalMode>(TEXT("ArrivalMode"));
}

// Called when the game starts or when spawned
void AVehicle::BeginPlay () {
	Super::BeginPlay();
	
	// PathFindingComp->Activate();
	// UActorComponent *Seek = NewObject<UActorComponent>(this, USeekMode::StaticClass(), "SeekMode");
	// Seek->RegisterComponent();
	// this->AddInstanceComponent(Seek);
	// UActorComponent *Arrival = NewObject<UActorComponent>(this, UArrivalMode::StaticClass(), "ArrivalMode");
	// Arrival->RegisterComponent();
	// this->AddInstanceComponent(Arrival);
	
	// Broadcast edit notifications so that level editor details are refreshed (e.g. components tree)
	// FLevelEditorModule& LevelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	// LevelEditor.BroadcastComponentsEdited();

	// SeekComp = Cast<USeekMode>(Seek);
	// ArrivalComp = Cast<UArrivalMode>(Arrival);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("PlayerStart"), FoundActors);
	if (FoundActors.Num() > 0) {
		PathFindingComp->CurrentIntersection = Cast<AIntersection>(FoundActors[0]);
	}

}

// Called every frame
void AVehicle::Tick (float DeltaTime) {
	
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT ("Enable Mode Previous Velocity"));


}
