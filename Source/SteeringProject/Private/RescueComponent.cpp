// Fill out your copyright notice in the Description page of Project Settings.


#include "RescueComponent.h"

#include "Hospital.h"
#include "Victim.h"

URescueComponent::URescueComponent() {
	PrimaryComponentTick.bCanEverTick = true;

}

void URescueComponent::BeginPlay() {
	Super::BeginPlay();

}

void URescueComponent::TickComponent(float DeltaTime,
                                     ELevelTick TickType,
                                     FActorComponentTickFunction *ThisTickFunction
		) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	GetWorld()->SweepMultiByChannel(OutResults, GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation(),
	                                FQuat::Identity,
	                                ECollisionChannel::ECC_Camera, CollisionSphere);
	for (auto Hit : OutResults) {
		if (!bCarryingVictim) {
			AVictim *Victim = Cast<AVictim>(Hit.GetActor());
			if (!Victim) continue;
			bCarryingVictim = true;
			Victim->Destroy();
		} else {
			AHospital *Hospital = Cast<AHospital>(Hit.GetActor());
			if (!Hospital) continue;
			bCarryingVictim = false;
		}
	}
}
