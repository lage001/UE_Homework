// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstPersonGameMode.h"
#include "FirstPersonCharacter.h"
#include "MyPlayerController.h"
#include "Actors/LevelController/Level0ControllerActor.h"
#include "Actors/LevelController/Level1ControllerActor.h"
#include "Actors/LevelController/Level2ControllerActor.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFirstPersonGameMode::AFirstPersonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void AFirstPersonGameMode::BeginPlay()
{
	Super::BeginPlay();
	InitializeLevelControllers();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&AFirstPersonGameMode::EnterGame,0.5f,false);
}

void AFirstPersonGameMode::InitializeLevelControllers()
{
	AActor* Level0ControllerActor = UGameplayStatics::GetActorOfClass(GetWorld(),Level0ControllerClass);
	Level0Controller = Cast<ALevel0ControllerActor>(Level0ControllerActor);
	
	AActor* Level1ControllerActor = UGameplayStatics::GetActorOfClass(GetWorld(),Level1ControllerClass);
	Level1Controller = Cast<ALevel1ControllerActor>(Level1ControllerActor);
	
	AActor* Level2ControllerActor = UGameplayStatics::GetActorOfClass(GetWorld(),Level2ControllerClass);
	
	Level2Controller = Cast<ALevel2ControllerActor>(Level2ControllerActor);

	UE_LOG(LogTemp,Warning,TEXT("InitializeLevelControllers"))
	
	Level0Controller->Initialization();
	Level1Controller->Initialization();
	Level2Controller->Initialization();
}

ALevel2ControllerActor* AFirstPersonGameMode::GetLevelController_2()
{
	if (Level2Controller)
	{
		return Level2Controller;
	}
	return nullptr;
}



void AFirstPersonGameMode::EnterGame()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	PlayerController->SetInputMode(FInputModeGameOnly());
	StartLevel();
}

void AFirstPersonGameMode::WinGame()
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	PlayerController->WinGame();
}

void AFirstPersonGameMode::StartLevel()
{
	OnLevelStart.Broadcast(CurrentLevel);
}

void AFirstPersonGameMode::RetryLevel()
{
	StartLevel();
	OnRetryLevel.Broadcast(CurrentLevel);
}

void AFirstPersonGameMode::PassLevel()
{
	OnLevelPassed.Broadcast(CurrentLevel);
	CurrentLevel++;
	if (CurrentLevel==3)
	{
		const FLatentActionInfo LatentInfo(0, FMath::Rand(), TEXT("WinGame"), this);
		UKismetSystemLibrary::Delay(this, 1.2f, LatentInfo);
	}
}

void AFirstPersonGameMode::DestroyKeyBox()
{
	OnKeyBoxDestroyed.Broadcast(CurrentLevel);
}


