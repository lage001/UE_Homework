// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SpecialBoxBaseActor.h"

#include "MyPlayerController.h"
#include "Actors/LevelController/Level2ControllerActor.h"
#include "Components/BoxComponent.h"
#include "FirstPerson/FirstPersonCharacter.h"
#include "FirstPerson/FirstPersonGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpecialBoxBaseActor::ASpecialBoxBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;
	
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollisionComponent->SetCollisionProfileName(TEXT("OverlapAll")); 
	BoxCollisionComponent->SetupAttachment(RootComponent);
	
	//BoxCollisionComponent->OnComponentHit.AddDynamic(this, &AFinishLevelActor::OnHit);
	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASpecialBoxBaseActor::OnComponentBeginOverlap);
	BoxCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASpecialBoxBaseActor::OnComponentEndOverlap);
	
}

// Called when the game starts or when spawned
void ASpecialBoxBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpecialBoxBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpecialBoxBaseActor::OnOverlapStay_Float(float DeltaTime)
{


	if (bCanBlow && bReady&&BlowingTime<BlowMaxTime)
	{
		BlowingTime += DeltaTime;
		for (auto& OverlappingComponent : OverlappingComponents)
		{
			if (OverlappingComponent && OverlappingComponent->IsSimulatingPhysics())
			{
				float OtherZ = OverlappingComponent->GetComponentLocation().Z;
				float ThisZ = GetActorLocation().Z;
				float LocationDif = OtherZ-ThisZ;
				FVector Resistance;
				if (900-LocationDif>50)
				{
					Resistance = OverlappingComponent->GetPhysicsLinearVelocity();
				}else
				{
					Resistance = FVector(0,0,0);
				}
				float ForceZ = (900-LocationDif)*15;
				FVector Force = FVector(0,0,ForceZ)-Resistance*0.1;
				OverlappingComponent->AddForce(FVector(0,0,2000), NAME_None, true);
			}
		}
		if (BlowingTime>BlowBroadcastTime && !bBroadcast)
		{
			BlowBroadcast();
		}
	}
	else
	{
		EndBlow();
	}
}

void ASpecialBoxBaseActor::OnComponentBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ASpecialBoxBaseActor::OnComponentEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ASpecialBoxBaseActor::SetSphereSimulation_Implementation(bool bIsSimu)
{
}

void ASpecialBoxBaseActor::BeginOverlap_PassLevel(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("KeyBox")))
	{
		AFirstPersonGameMode* GameMode = Cast<AFirstPersonGameMode>(UGameplayStatics::GetGameMode(this));;
		if (GameMode)
		{
			GameMode->PassLevel();
		}
		
		OtherActor->Destroy();
	}
}

void ASpecialBoxBaseActor::BeginOverlap_Lava(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("KeyBox"))
	{
		OtherComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		OtherActor->Destroy();
	}
	if (OtherActor->ActorHasTag("Player"))
	{
		AFirstPersonCharacter* FirstPersonCharacter = Cast<AFirstPersonCharacter>(OtherActor);
		OtherComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		FirstPersonCharacter->UseChance();
	}
}

void ASpecialBoxBaseActor::BeginOverlap_Float(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bCanBlow && OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OverlappingComponents.Add(OtherComp);
	}
}

void ASpecialBoxBaseActor::EndOverlap_Float(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bCanBlow && OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OverlappingComponents.Remove(OtherComp);
	}
	
}
//重载 执行门开启
void ASpecialBoxBaseActor::OnPassLevel_Implementation(int LevelIndex)
{
	
}

void ASpecialBoxBaseActor::BindEvent()
{
	AFirstPersonGameMode* GameMode = Cast<AFirstPersonGameMode>(UGameplayStatics::GetGameMode(this));;
	GameMode->OnLevelPassed.AddDynamic(this, &ASpecialBoxBaseActor::OnPassLevel);
}

void ASpecialBoxBaseActor::BindBlowEvent()
{
	AFirstPersonGameMode* GameMode = Cast<AFirstPersonGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode->GetLevelController_2())
	{
		UE_LOG(LogTemp,Warning,TEXT("bIND"))
		GameMode->GetLevelController_2()->OnBlowEnd.AddDynamic(this, &ASpecialBoxBaseActor::StartBlow);
	}
}

void ASpecialBoxBaseActor::EndBlow()
{
	bReady = false;
	BlowingTime = 0;
}

void ASpecialBoxBaseActor::BlowBroadcast()
{
	bBroadcast = true;
	AFirstPersonGameMode* GameMode = Cast<AFirstPersonGameMode>(UGameplayStatics::GetGameMode(this));
	GameMode->GetLevelController_2()->EndBlow();
}

void ASpecialBoxBaseActor::StartBlow(FVector pos)
{
	if (LocalPos == pos)
	{
		bReady = true;
		bBroadcast = false;
		BlowingTime = 0;
	}
}





