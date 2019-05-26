// Fill out your copyright notice in the Description page of Project Settings.

#include "ColorHint.h"
#include "Classes/Components/PrimitiveComponent.h"


// Sets default values for this component's properties
UColorHint::UColorHint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UColorHint::BeginPlay()
{
	Super::BeginPlay();
	
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName())
	}
}


// Called every frame
void UColorHint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorsOnPlate() > SecondHintMass && GetTotalMassOfActorsOnPlate() < ThirdHintMass)
	{
		SecondHint.Broadcast();
	}
	else if (GetTotalMassOfActorsOnPlate() >= ThirdHintMass)
	{
		ThirdHint.Broadcast();
	}
	else
	{
		FirstHint.Broadcast();
	}
}

float UColorHint::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return 0.f; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

