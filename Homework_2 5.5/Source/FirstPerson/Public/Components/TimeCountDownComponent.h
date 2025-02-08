// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TimeCountDownComponent.generated.h"


class AMyPlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPERSON_API UTimeCountDownComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimeCountDownComponent();
	
	void StartCountDown(int32 time);

	int32 GetRemainingTime();
protected:
	int32 RemainingTime;
	FTimerHandle CountdownTimerHandle;
	TObjectPtr<AMyPlayerController> MyPlayerController;

	
	void UpdateCountDown();

	void OnFinished();
public:	
	
};
