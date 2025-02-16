// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelControllerBaseActor.h"

#include "Components/CapsuleComponent.h"
#include "FirstPerson/FirstPersonCharacter.h"
#include "FirstPerson/FirstPersonGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelControllerBaseActor::ALevelControllerBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelControllerBaseActor::BeginPlay()
{
	Super::BeginPlay();
}



void ALevelControllerBaseActor::SpawnKeyBoxAtLocation(FVector Location)
{
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters ActorSpawnParams;
		AActor* KeyBox = World->SpawnActor<AActor>(KeyBoxClass, KeyBoxLocation, FRotator::ZeroRotator, ActorSpawnParams);
		KeyBox->Tags.Add("KeyBox");
	}
}

void ALevelControllerBaseActor::RebornCharacterAtLocationAndRotation()
{
	AFirstPersonCharacter* FirstPersonCharacter = Cast<AFirstPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	FirstPersonCharacter->SetActorLocation(CharacterRebornLocation);
	FirstPersonCharacter->SetActorRotation(CharacterRebornRotator);
	FirstPersonCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ALevelControllerBaseActor::OnKeyBoxDestroyed(int Index)
{
	if (Index == LevelIndex)
	{
		SpawnKeyBoxAtLocation(KeyBoxLocation);
	}
}
inline void ALevelControllerBaseActor::OnRetryLevel(int Index)
{
	if (Index == LevelIndex)
	{
		const FLatentActionInfo LatentInfo(0, FMath::Rand(), TEXT("RebornCharacterAtLocationAndRotation"), this);
		UKismetSystemLibrary::Delay(this, 1.0f, LatentInfo);
	}
}
void ALevelControllerBaseActor::OnStartLevel(int32 Index)
{
	if (Index == LevelIndex)
	{
		UE_LOG(LogTemp,Warning,TEXT("Start Level %d"),LevelIndex);
	}
}

void ALevelControllerBaseActor::OnLevelPassed(int Index)
{
	if (Index == LevelIndex)
	{
		UE_LOG(LogTemp,Warning,TEXT("Level Passed %d"),LevelIndex);
	}
}

// Called every frame
void ALevelControllerBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelControllerBaseActor::Initialization()
{
	AFirstPersonGameMode* GameMode = Cast<AFirstPersonGameMode>(UGameplayStatics::GetGameMode(this));
	GameMode->OnRetryLevel.AddDynamic(this, &ALevelControllerBaseActor::OnRetryLevel);
	GameMode->OnLevelStart.AddDynamic(this, &ALevelControllerBaseActor::OnStartLevel);
	GameMode->OnLevelPassed.AddDynamic(this, &ALevelControllerBaseActor::OnLevelPassed);
	GameMode->OnKeyBoxDestroyed.AddDynamic(this, &ALevelControllerBaseActor::OnKeyBoxDestroyed);
}

