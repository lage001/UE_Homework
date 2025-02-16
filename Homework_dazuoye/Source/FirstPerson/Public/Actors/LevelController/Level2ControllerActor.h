// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/LevelControllerBaseActor.h"
#include "Level2ControllerActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBlowEnd, FVector, Pos);

class ASpecialBoxBaseActor;
/**
 * 
 */
UCLASS()
class FIRSTPERSON_API ALevel2ControllerActor : public ALevelControllerBaseActor
{
	GENERATED_BODY()
public:
	//BeforePlay
	UPROPERTY(EditAnywhere, Category = "Scene")
	TSubclassOf<AActor> FanClass;
	
	UPROPERTY(EditAnywhere,Category="Scene")
	TArray<FVector> PosList;
	
	//BeginPlay
	UPROPERTY(VisibleAnywhere,Category="Scene")
	TArray<AActor*> FanActors;

	UPROPERTY(VisibleAnywhere,category = "Blow")
	FOnBlowEnd OnBlowEnd;

	UFUNCTION(BlueprintCallable,category = "Blow")
	void EndBlow();
private:

	int32 BlowIndex = 0;
	
	UFUNCTION()
	void GetFans();
	
	UFUNCTION()
	void StartBlow();
public:
	virtual void BeginPlay() override;

	virtual void OnStartLevel(int32 Index) override;

	virtual void Initialization() override;
};
