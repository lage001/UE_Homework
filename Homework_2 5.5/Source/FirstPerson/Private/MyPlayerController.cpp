// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "FirstPerson/FirstPersonCharacter.h"
#include "HUD/FirstPersonHUD.h"
#include "Actors/TimeCountDownActor.h"
#include "Components/TimeCountDownComponent.h"
#include "HUD/MyUserWidget.h"
#include "HUD/EndGameWidget.h"
#include "Kismet/GameplayStatics.h"

class AFirstPersonCharacter;
AMyPlayerController::AMyPlayerController()
{
	TimeCountDownComponent = CreateDefaultSubobject<UTimeCountDownComponent>("TimeCountDownComponent");
}
void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FirstPersonHUD = Cast<AFirstPersonHUD>(GetHUD());
	MyPawn = Cast<AFirstPersonCharacter>(GetPawn());
	if (FirstPersonHUD!=nullptr)
	{
		FirstPersonHUD->CreateMyUserWidget();
	}
	if (TimeCountDownComponent!=nullptr)
	{
		TimeCountDownComponent->StartCountDown(InitTime);
	}
}


void AMyPlayerController::AddScore(int32 const Score) const
{
	MyPawn->AddScore(Score);
	UMyUserWidget* MyUserWidget = FirstPersonHUD->GetMyUserWidget();  
	MyUserWidget->UpdateScoreText(Score);
}

void AMyPlayerController::LogScore() const
{
	MyPawn->LogScore();
}

void AMyPlayerController::UpdateTime(int32 Time)
{
	UMyUserWidget* MyUserWidget = FirstPersonHUD->GetMyUserWidget();  
	MyUserWidget->UpdateTimeText(Time);
	
}

void AMyPlayerController::OnTimeCountDownFinished()
{
	FirstPersonHUD->DestroyMyUserWidget();
	SetPause(true);
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

	
	FirstPersonHUD->CreateEndGameWidget();
	UEndGameWidget* EndGameWidget = FirstPersonHUD->GetEndGameWidget();
	EndGameWidget->SetScoreText(MyPawn->GetScore());
}

void AMyPlayerController::RestartGame()
{
	
	FirstPersonHUD->DestroyEndGameWidget();
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}





