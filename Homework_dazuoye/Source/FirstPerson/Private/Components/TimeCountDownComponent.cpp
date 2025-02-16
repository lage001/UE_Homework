// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TimeCountDownComponent.h"

#include "MyPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UTimeCountDownComponent::UTimeCountDownComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MyPlayerController = Cast<AMyPlayerController>(GetOwner());
	// ...
}

void UTimeCountDownComponent::StartCountDown(int32 time)
{
	RemainingTime = time;
	GetOwner()->GetWorldTimerManager().SetTimer(CountdownTimerHandle,this, &UTimeCountDownComponent::UpdateCountDown, 1.0f, true);
}

int32 UTimeCountDownComponent::GetRemainingTime()
{
	return RemainingTime;
}

void UTimeCountDownComponent::UpdateCountDown()
{
	if (RemainingTime>=0)
	{
		MyPlayerController->UpdateTime(RemainingTime);
		RemainingTime --;
	}
	else
	{
		OnFinished();
	}
}

void UTimeCountDownComponent::OnFinished()
{
	GetOwner()->GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	MyPlayerController->OnTimeCountDownFinished();
	//UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit,true);
}

