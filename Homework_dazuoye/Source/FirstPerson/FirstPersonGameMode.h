// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FirstPersonGameMode.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPassLevel,int32,LevelIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelStart,int32,LevelIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKeyBoxDestroyed,int32,LevelIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRetryLevel,int32,LevelIndex);

class ALevel0ControllerActor;
class ALevel1ControllerActor;
class ALevel2ControllerActor;

UCLASS(minimalapi)
class AFirstPersonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFirstPersonGameMode();

	UPROPERTY(BlueprintCallable)
	FOnPassLevel OnLevelPassed;
	
	UFUNCTION(BlueprintCallable)
	void PassLevel();
	
	UPROPERTY(BlueprintCallable)
	FOnLevelStart OnLevelStart;

	UFUNCTION(BlueprintCallable)
	void EnterGame();
	
	UFUNCTION(BlueprintCallable)
	void WinGame();
	
	UFUNCTION(BlueprintCallable)
	void StartLevel();
	
	UPROPERTY(BlueprintCallable)
	FOnRetryLevel OnRetryLevel;
	
	UFUNCTION(BlueprintCallable)
	void RetryLevel();
	
	UPROPERTY(BlueprintCallable)
	FOnPassLevel OnKeyBoxDestroyed;
	
	UFUNCTION(BlueprintCallable)
	void DestroyKeyBox();
	
	UFUNCTION(BlueprintCallable)
	int32 GetLevelIndex() const { return CurrentLevel; }
	
	UFUNCTION(BlueprintCallable)
	int32 GetTotalLevelNum() const { return TotalLevelNum; }
protected:
	virtual void BeginPlay() override;
private:
	int32 CurrentLevel = 0;
	
	int32 TotalLevelNum = 3;
	//Before Play
	UPROPERTY(EditAnywhere,Category="LevelControllers")
	TSubclassOf<ALevel0ControllerActor>  Level0ControllerClass;
	
	UPROPERTY(EditAnywhere,Category="LevelControllers")
	TSubclassOf<ALevel1ControllerActor>  Level1ControllerClass;
	
	UPROPERTY(EditAnywhere,Category="LevelControllers")
	TSubclassOf<ALevel2ControllerActor>  Level2ControllerClass;

	//BeginPlay
	UPROPERTY(VisibleAnywhere,Category="LevelControllers")
	TObjectPtr<ALevel0ControllerActor>  Level0Controller;
	
	UPROPERTY(VisibleAnywhere,Category="LevelControllers")
	TObjectPtr<ALevel1ControllerActor>  Level1Controller;
	
	UPROPERTY(VisibleAnywhere,Category="LevelControllers")
	TObjectPtr<ALevel2ControllerActor>  Level2Controller;

	void InitializeLevelControllers();
	
	FTimerHandle TimerHandle;

public:
	UFUNCTION(BlueprintCallable,Category="LevelControllers")
	ALevel0ControllerActor* GetLevelController_0(){return Level0Controller;}
	
	UFUNCTION(BlueprintCallable,Category="LevelControllers")
	ALevel1ControllerActor* GetLevelController_1(){return Level1Controller;}

	UFUNCTION(BlueprintCallable,Category="LevelControllers")
	ALevel2ControllerActor* GetLevelController_2();
};



