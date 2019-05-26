// Fill out your copyright notice in the Description page of Project Settings.

#include "MatchPuzzle.h"


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

	if (!PressurePlateRed)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing red pressure plate"), *GetOwner()->GetName())
	}
	
	if (!PressurePlateGreen)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing green pressure plate"), *GetOwner()->GetName())
	}

	if (!PressurePlateYellow)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing yellow pressure plate"), *GetOwner()->GetName())
	}
}


// Called every frame
void UMatchPuzzle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PressurePlateRed) { return; }
	if (!PressurePlateGreen) { return; }
	if (!PressurePlateYellow) { return; }

	if (Owner->GetName() == "PointLight1_Yellow_BP" && PressurePlateYellow->IsOverlappingActor(ActorThatOpens))
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *ActorThatOpens->GetName())
		YellowMatch.Broadcast();
		YellowMatched = true;
	}

	if (Owner->GetName() == "PointLight1_Green_BP" && PressurePlateGreen->IsOverlappingActor(ActorThatOpens))
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *ActorThatOpens->GetName())
		GreenMatch.Broadcast();
		GreenMatched = true;
	}

	if (Owner->GetName() == "PointLight1_Red_BP" && PressurePlateRed->IsOverlappingActor(ActorThatOpens))
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *ActorThatOpens->GetName())
		RedMatch.Broadcast();
		RedMatched = true;
	}

	if (YellowMatched && GreenMatched && RedMatched)
	{
		UE_LOG(LogTemp, Error, TEXT("All matched!"))
		AllMatch.Broadcast();
	}
}

