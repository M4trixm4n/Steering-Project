// Fill out your copyright notice in the Description page of Project Settings.

#include "Vehicle.h"
#include "ArrivalMode.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AVehicle::AVehicle () {
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

void AVehicle::BeginPlay () {
	Super::BeginPlay();
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("PlayerStart"), FoundActors);
	if (FoundActors.Num() > 0) {
		PathFindingComp->CurrentIntersection = Cast<AIntersection>(FoundActors[0]);
	}

}

void AVehicle::Tick (float DeltaTime) {
	Super::Tick(DeltaTime);
}
