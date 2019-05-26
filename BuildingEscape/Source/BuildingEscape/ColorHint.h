// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "ColorHint.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHintEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UColorHint : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UColorHint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FHintEvent FirstHint;

	UPROPERTY(BlueprintAssignable)
		FHintEvent SecondHint;

	UPROPERTY(BlueprintAssignable)
		FHintEvent ThirdHint;

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	float SecondHintMass = 20.f;

	float ThirdHintMass = 50.f;

	float GetTotalMassOfActorsOnPlate();
};
