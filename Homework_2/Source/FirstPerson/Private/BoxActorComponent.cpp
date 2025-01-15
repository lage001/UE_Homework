// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPerson/Public/BoxActorComponent.h"




// Sets default values for this component's properties
UBoxActorComponent::UBoxActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBoxActorComponent::BeginPlay()
{
	Super::BeginPlay();
	SetBoxType();
	
}


// Called every frame
void UBoxActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UBoxActorComponent::SetBoxType()
{
	bBoxType = FMath::RandBool();
	if (!bBoxType)
	{
		Score *= 2; 
	}
	
}

void UBoxActorComponent::LoseHealth()
{
	Health --;
	if (Health == 1)
	{
		GetOwner()->SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
	}
	else if (Health == 0)
	{
		GetOwner()->Destroy();
	}
}
