// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelControllerBaseActor.generated.h"

UCLASS()
class FIRSTPERSON_API ALevelControllerBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelControllerBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="KeyBox")
	TSubclassOf<AActor> KeyBoxClass;
	
	UPROPERTY(EditAnywhere,Category="KeyBox")
	FVector3d KeyBoxLocation;
	
	UPROPERTY(EditAnywhere,Category="KeyBox")
	FVector3d CharacterRebornLocation;

	UPROPERTY(EditAnywhere,Category="KeyBox")
	FRotator CharacterRebornRotator;
	
	UPROPERTY(EditAnywhere)
	int32 LevelIndex;

	
	UFUNCTION(BlueprintCallable)
	virtual void OnStartLevel(int32 Index);

	UFUNCTION(BlueprintCallable)
	virtual void SpawnKeyBoxAtLocation(FVector Location);
	UFUNCTION(BlueprintCallable)
	virtual void RebornCharacterAtLocationAndRotation();
	UFUNCTION()
	void OnKeyBoxDestroyed(int Index);
	
	UFUNCTION()
	void OnRetryLevel(int Index);

	UFUNCTION()
	void OnLevelPassed(int Index);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Initialization();
};
