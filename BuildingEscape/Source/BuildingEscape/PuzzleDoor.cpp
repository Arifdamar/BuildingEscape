// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleDoor.h"


// Sets default values for this component's properties
UPuzzleDoor::UPuzzleDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPuzzleDoor::BeginPlay()
{
	Super::BeginPlay();

	if (!PointLightRed)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing red point light"), *GetOwner()->GetName())
	}

	if (!PointLightGreen)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing green point light"), *GetOwner()->GetName())
	}

	if (!PointLightYellow)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing yellow point light"), *GetOwner()->GetName())
	}
	
}


// Called every frame
void UPuzzleDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PointLightRed) { return; }
	if (!PointLightGreen) { return; }
	if (!PointLightYellow) { return; }
	FLinearColor RedColor = PointLightRed->GetLightColor();		  // (R=127,G=0,B=0,A=129)
	FLinearColor GreenColor = PointLightGreen->GetLightColor();   // (R=0,G=127,B=0,A=129)
	FLinearColor YellowColor = PointLightYellow->GetLightColor(); // (R=127,G=127,B=0,A=129)

	if (RedColor.ToRGBE().ToString() == "(R=127,G=0,B=0,A=129)")
	{
		RedMatched = true;
	}
	else
	{
		RedMatched = false;
	}

	if (GreenColor.ToRGBE().ToString() == "(R=0,G=127,B=0,A=129)")
	{
		GreenMatched = true;
	}
	else
	{
		GreenMatched = false;
	}

	if (YellowColor.ToRGBE().ToString() == "(R=127,G=127,B=0,A=129)")
	{
		YellowMatched = true;
	}
	else
	{
		YellowMatched = false;
	}

	if (RedMatched && GreenMatched && YellowMatched)
	{
		OpenPuzzleDoor.Broadcast();
	}
	else
	{
		ClosePuzzleDoor.Broadcast();
	}

	//UE_LOG(LogTemp, Error, TEXT("BBB %s"), *RedColor.ToRGBE().ToString())
	//UE_LOG(LogTemp, Error, TEXT("BBB %s"), *GreenColor.ToRGBE().ToString())
	//UE_LOG(LogTemp, Error, TEXT("BBB %s"), *YellowColor.ToRGBE().ToString())
}

