// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TimeCountDownActor.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ATimeCountDownActor::ATimeCountDownActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ATimeCountDownActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATimeCountDownActor::StartCountDown(int32 time)
{
	RemainingTime = time;
 
	GetWorldTimerManager().SetTimer(
		CountdownTimerHandle,
		FTimerDelegate::CreateUObject(this, &ATimeCountDownActor::UpdateCountDown),
		1.0f, // 每秒更新一次
		true  // 循环执行
	);
}

void ATimeCountDownActor::UpdateCountDown()
{
	if (RemainingTime > 0)
	{
		RemainingTime --;
		UE_LOG(LogTemp, Warning, TEXT("Time: %d"), RemainingTime);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit,true);
	}
}

// Called every frame
void ATimeCountDownActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

