// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class AFirstPersonHUD;
class UTimeCountDownComponent;
class AFirstPersonCharacter;
/**
 * 
 */
UCLASS()
class FIRSTPERSON_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	AMyPlayerController();
	void AddScore(int32 const Score) const;
	void LogScore() const;

	void UpdateTime(int32 Time);

	void OnTimeCountDownFinished();

	void RestartGame();
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<AFirstPersonHUD> FirstPersonHUD;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTimeCountDownComponent> TimeCountDownComponent;

	TObjectPtr<AFirstPersonCharacter> MyPawn;
	int32 InitTime = 10;
};
