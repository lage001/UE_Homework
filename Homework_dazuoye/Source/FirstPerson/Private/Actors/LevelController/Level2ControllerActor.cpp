// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelController/Level2ControllerActor.h"

#include "Actors/SpecialBoxBaseActor.h"
#include "Kismet/GameplayStatics.h"



void ALevel2ControllerActor::BeginPlay()
{
	Super::BeginPlay();
	GetFans();
}

void ALevel2ControllerActor::GetFans()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), FanClass,FanActors);
}



void ALevel2ControllerActor::OnStartLevel(int32 Index)
{
	Super::OnStartLevel(Index);
	if (Index == LevelIndex)
	{
		const FLatentActionInfo LatentInfo(0, FMath::Rand(), TEXT("StartBlow"), this);
		UKismetSystemLibrary::Delay(this, 2.0f, LatentInfo);
	}
	
}

void ALevel2ControllerActor::Initialization()
{
	Super::Initialization();

	UE_LOG(LogTemp,Warning,TEXT("Initialization_2"))
	for (int i=0;i<FanActors.Num();i++)
	{
		ASpecialBoxBaseActor* Fan = Cast<ASpecialBoxBaseActor>(FanActors[i]);
		if (Fan)
		{
			Fan->SetCanBlow(true);
			Fan->BindBlowEvent();
			Fan->SetSphereSimulation(false);
		}
	}
}
void ALevel2ControllerActor::StartBlow()
{
	for (int i=0;i<FanActors.Num();i++)
	{
		ASpecialBoxBaseActor* Fan = Cast<ASpecialBoxBaseActor>(FanActors[i]);
		if (Fan)
		{
			Fan->SetSphereSimulation(true);
		}
	}
	OnBlowEnd.Broadcast(PosList[BlowIndex]);
}
void ALevel2ControllerActor::EndBlow()
{
	BlowIndex++;
	BlowIndex = BlowIndex%PosList.Num();
	OnBlowEnd.Broadcast(PosList[BlowIndex]);
}
