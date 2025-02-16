// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PhysicsGrabComponent.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "FirstPerson/FirstPersonCharacter.h"
#include "FirstPerson/FirstPersonGameMode.h"
#include "HUD/FirstPersonHUD.h"
#include "HUD/MyUserWidget.h"
#include "Kismet/GameplayStatics.h"

class AFirstPersonGameMode;
// Sets default values for this component's properties
UPhysicsGrabComponent::UPhysicsGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogTemp,Warning,TEXT("PhysicsGrabComponent Constructor"));
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	PhysicsHandle->SetInterpolationSpeed(100.f);
	
}


// Called when the game starts
void UPhysicsGrabComponent::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AFirstPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
	{
		PlayerCameraManager = PlayerController->PlayerCameraManager;
		FirstPersonHUD = Cast<AFirstPersonHUD>(PlayerController->GetHUD());
	}
	AFirstPersonGameMode* FirstPersonGameMode = Cast<AFirstPersonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	FirstPersonGameMode->OnRetryLevel.AddDynamic(this,&UPhysicsGrabComponent::CheckRealse);
	//...
	
}


// Called every frame
void UPhysicsGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PhysicsHandle && HeldComponent)
	{
		FVector GrabLocation = GetOwner()->GetActorLocation()+PlayerCameraManager->GetCameraRotation().RotateVector(FVector(150.0f, 30.0f, 10.0f));
		PhysicsHandle->SetTargetLocationAndRotation(GrabLocation,HeldComponent->GetComponentRotation());
	}	
	// ...
}

void UPhysicsGrabComponent::ToggleGrab()
{
	if (!HeldComponent)
	{
		FHitResult  HitResult;
		if (FindGrabbableObject(HitResult)) {
			UE_LOG(LogTemp,Warning, TEXT("PhysicsGrabComponent: %s"),*HitResult.GetActor()->GetName());
			GrabObject(HitResult.GetComponent());
		}
	}
}

void UPhysicsGrabComponent::StartCharging()
{
	if (!bStartCharging)
	{
		bStartCharging = true;
		if (FirstPersonHUD)
		{
			UMyUserWidget* Widget = FirstPersonHUD->GetMyUserWidget();
			Widget->FadeIn(Widget->GetChargeProgressBar());
		}
	}
}

void UPhysicsGrabComponent::OnCharging()
{
	if (HeldComponent)
	{
		
		if (ChargingForce < MaxChargingForce)
		{
			ChargingForce += DeltaForce;
			if (ChargingForce/MaxChargingForce>0.1f)
			{
				StartCharging();
			}
			UpdateChargeProgressBar(DeltaForce/MaxChargingForce);
		}
	}
}

void UPhysicsGrabComponent::StopCharging()
{
	UE_LOG(LogTemp,Warning,TEXT("StopCharging"))
	if (HeldComponent && PhysicsHandle)
	{
		UE_LOG(LogTemp,Warning,TEXT("HeldComponent StopCharging"));
		PhysicsHandle->ReleaseComponent();
		AActor* HeldActor = HeldComponent->GetOwner();
		HeldActor->SetActorScale3D(HeldActor->GetActorScale3D() * 2.0f);
		FVector Location = GetOwner()->GetActorLocation()+PlayerCameraManager->GetCameraRotation().RotateVector(FVector(100.0f, 0.0f, 10.0f));
		HeldActor->SetActorLocation(Location);
		HeldComponent->AddImpulse(PlayerCameraManager->GetCameraRotation().Vector() * ChargingForce, NAME_None, true);
		//HeldComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		HeldComponent = nullptr;
	}
	ChargingForce = 0.0f;
	
	bStartCharging = false;
	if (FirstPersonHUD)
	{
		UMyUserWidget* Widget = FirstPersonHUD->GetMyUserWidget();
		Widget->StartProgressBarDecline();
		Widget->FadeOut(Widget->GetChargeProgressBar());
	}
}

void UPhysicsGrabComponent::CheckRealse(int32 LevelIndex)
{
	if (HeldComponent && PhysicsHandle)
	{
		UE_LOG(LogTemp,Warning,TEXT("StopCharging"));
		PhysicsHandle->ReleaseComponent();
		AActor* HeldActor = HeldComponent->GetOwner();
		HeldActor->SetActorScale3D(HeldActor->GetActorScale3D() * 2.0f);
		FVector Location = GetOwner()->GetActorLocation()+PlayerCameraManager->GetCameraRotation().RotateVector(FVector(100.0f, 0.0f, 10.0f));
		HeldActor->SetActorLocation(Location);
		HeldComponent->AddImpulse(PlayerCameraManager->GetCameraRotation().Vector() * ChargingForce, NAME_None, true);
		//HeldComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		HeldComponent = nullptr;
	}
	ChargingForce = 0.0f;
	
	bStartCharging = false;
	if (FirstPersonHUD)
	{
		UMyUserWidget* Widget = FirstPersonHUD->GetMyUserWidget();
		Widget->StartProgressBarDecline();
		Widget->FadeOut(Widget->GetChargeProgressBar());
	}
}



bool UPhysicsGrabComponent::FindGrabbableObject(FHitResult& OutHitResult) const
{
	const FRotator Rotation = PlayerCameraManager->GetCameraRotation();
	UE_LOG(LogTemp,Warning,TEXT("FindGrabbableObject"));
	const FVector Start = PlayerCameraManager->GetCameraLocation();
	const FVector End = Start + Rotation.Vector() * GrabDistance;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	Params.AddIgnoredActor(Player);
	FHitResult Hit;
	
	GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_PhysicsBody,
		Params
	);
	// 绘制检测线
	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 10.0f);
	
	
	if (Hit.GetComponent() && Hit.GetComponent()->IsSimulatingPhysics()) {

		//UE_LOG(LogTemp,Warning,TEXT("PhysicsGrabComponent: %s"),*Hit.GetActor()->GetName());
		OutHitResult = Hit;
		return true;
	}
	return false;
}
void UPhysicsGrabComponent::GrabObject(UPrimitiveComponent* Component)
{

	if (!PhysicsHandle || !Component)
	{
		return;
	}
	PhysicsHandle->GrabComponentAtLocationWithRotation(
		Component,
		NAME_None,
		Component->GetComponentLocation(),
		Component->GetComponentRotation()
	);
	AActor* Owner = Component->GetOwner();
	Owner->SetActorScale3D(Owner->GetActorScale3D() * 0.5f);
	//Component->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	HeldComponent = Component;
}

void UPhysicsGrabComponent::UpdateChargeProgressBar(float Alpha)
{
	if (FirstPersonHUD)
	{
		UMyUserWidget* Widget = FirstPersonHUD->GetMyUserWidget();
		Widget->UpdateProgressBar_OnIncrease(Alpha);
	}
}

