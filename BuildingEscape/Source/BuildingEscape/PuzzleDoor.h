// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Classes/Engine/PointLight.h"
#include "PuzzleDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPuzzleDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UPuzzleDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzleDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FPuzzleDoorEvent OpenPuzzleDoor;

	UPROPERTY(BlueprintAssignable)
		FPuzzleDoorEvent ClosePuzzleDoor;

private:
	UPROPERTY(EditAnywhere)
		APointLight* PointLightRed = nullptr;

	UPROPERTY(EditAnywhere)
		APointLight* PointLightGreen = nullptr;

	UPROPERTY(EditAnywhere)
		APointLight* PointLightYellow = nullptr;

	bool RedMatched = false;
	bool GreenMatched = false;
	bool YellowMatched = false;

};
