// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FinishLevelActor.h"

#include "Components/BoxComponent.h"

// Sets default values
AFinishLevelActor::AFinishLevelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;
	
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollisionComponent->SetCollisionProfileName(TEXT("OverlapAll")); 
	BoxCollisionComponent->SetupAttachment(RootComponent);
	
	//BoxCollisionComponent->OnComponentHit.AddDynamic(this, &AFinishLevelActor::OnHit);
	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFinishLevelActor::OnComponentBeginOverlap);
	
}

// Called when the game starts or when spawned
void AFinishLevelActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinishLevelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AFinishLevelActor::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Congratulations! You have finished the level."));	
	}
}
