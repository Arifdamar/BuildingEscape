// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "Classes/Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"

#define OUT


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

	// Find the owning Actor
	Owner = GetOwner();

	

	// Create a rotator
	ActorRotation = Owner->GetActorRotation();
}


void UOpenDoor::OpenDoor()
{
	// Set the rotation value
	ActorRotation.Yaw += 90;

	// Set the door rotation
	Owner->SetActorRotation(ActorRotation);
	IsDoorOpen = true;
}


void UOpenDoor::CloseDoor()
{
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
	if (GetTotalMassOfActorsOnPlate() > 50.0f)
	{
		if (!IsDoorOpen)
		{
			// When the ActorThatOpens is in the volume and the door is close
			OpenDoor();
		}
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	else if (IsDoorOpen && GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		// When the ActorThatOpens is NOT in the volume and the door is open
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;

	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("It's : %s"), *Actor->GetName())
	}

	return TotalMass;
}