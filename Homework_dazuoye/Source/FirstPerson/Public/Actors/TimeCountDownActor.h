// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeCountDownActor.generated.h"

UCLASS()
class FIRSTPERSON_API ATimeCountDownActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeCountDownActor();

	void StartCountDown(int32 time);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	int32 RemainingTime;
	FTimerHandle CountdownTimerHandle;
	
	

	void UpdateCountDown();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
