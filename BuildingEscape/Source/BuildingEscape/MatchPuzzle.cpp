// Fill out your copyright notice in the Description page of Project Settings.

#include "MatchPuzzle.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UMatchPuzzle::UMatchPuzzle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMatchPuzzle::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName())
	}
}


// Called every frame
void UMatchPuzzle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PressurePlate) { return; }

	if (Owner->GetName() == "PointLight1_Red_BP")
	{
		if (PressurePlate->IsOverlappingActor(ActorThatMatches) && !RedMatched)
		{
			UE_LOG(LogTemp, Error, TEXT("%s"), *ActorThatMatches->GetName())
			RedMatch.Broadcast();
			RedMatched = true;
		}
		else if(!PressurePlate->IsOverlappingActor(ActorThatMatches))
		{
			UnMatch.Broadcast();
			RedMatched = false;
		}
	}
	

	if (Owner->GetName() == "PointLight1_Yellow_BP")
	{
		if (PressurePlate->IsOverlappingActor(ActorThatMatches) && !YellowMatched)
		{
			UE_LOG(LogTemp, Error, TEXT("%s"), *ActorThatMatches->GetName())
			YellowMatch.Broadcast();
			YellowMatched = true;
		}
		else if(!PressurePlate->IsOverlappingActor(ActorThatMatches))
		{
			UnMatch.Broadcast();
			YellowMatched = false;
		}
	}

	if (Owner->GetName() == "PointLight1_Green_BP")
	{
		if (PressurePlate->IsOverlappingActor(ActorThatMatches) && !GreenMatched)
		{
			UE_LOG(LogTemp, Error, TEXT("%s"), *ActorThatMatches->GetName())
			GreenMatch.Broadcast();
			GreenMatched = true;
		}
		else if(!PressurePlate->IsOverlappingActor(ActorThatMatches))
		{
			UnMatch.Broadcast();
			GreenMatched = false;
		}
	}
	
}

