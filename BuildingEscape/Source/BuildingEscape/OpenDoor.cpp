// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//..
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


void UOpenDoor::OpenDoor()
{
	// Find the owning Actor
	AActor* Owner = GetOwner();

	// Create a rotator
	FRotator ActorRotation = Owner->GetActorRotation();

	// Set the rotation value
	ActorRotation.Yaw += 90;

	// Set the door rotation
	Owner->SetActorRotation(ActorRotation);
	IsDoorOpen = true;
}

void UOpenDoor::CloseDoor()
{
	// Find the owning Actor
	AActor* Owner = GetOwner();

	// Create a rotator
	FRotator ActorRotation = Owner->GetActorRotation();

	// Set the rotation value
	ActorRotation.Yaw -= 90;

	// Set the door rotation
	Owner->SetActorRotation(ActorRotation);
	IsDoorOpen = false;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens) && !IsDoorOpen)
	{
		// When the ActorThatOpens is in the volume and the door is close
		OpenDoor();
	}
	if (!PressurePlate->IsOverlappingActor(ActorThatOpens) && IsDoorOpen)
	{
		// When the ActorThatOpens is NOT in the volume and the door is open
		CloseDoor();
	}
}

