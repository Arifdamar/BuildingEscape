// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "MatchPuzzle.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMatchPuzzleEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UMatchPuzzle : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMatchPuzzle();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FMatchPuzzleEvent RedMatch;

	UPROPERTY(BlueprintAssignable)
		FMatchPuzzleEvent GreenMatch;

	UPROPERTY(BlueprintAssignable)
		FMatchPuzzleEvent YellowMatch;

	UPROPERTY(BlueprintAssignable)
		FMatchPuzzleEvent UnMatch;

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;
	
	UPROPERTY(EditAnywhere)
		AActor* ActorThatMatches;

	AActor* Owner;

	bool RedMatched = false, GreenMatched = false, YellowMatched = false;
};
