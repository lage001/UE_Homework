// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PhysicsGrabComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UPhysicsGrabComponent::UPhysicsGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}


// Called when the game starts
void UPhysicsGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPhysicsGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPhysicsGrabComponent::ToggleGrab()
{
	if (HeldComponent!=nullptr) {
		ReleaseObject();
	}
	else {
		FHitResult  HitResult;
		if (FindGrabbableObject(HitResult)) {
			GrabObject(HitResult.GetComponent());
		}
	}
}
bool UPhysicsGrabComponent::FindGrabbableObject(FHitResult& OutHitResult) const
{
	USkeletalMeshComponent* ParentMesh = Cast<USkeletalMeshComponent>(GetAttachParent());
	FVector Start = ParentMesh->GetSocketLocation(GripSocketName);
	FVector End = Start + ParentMesh->GetForwardVector() * GrabDistance;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	FHitResult Hit;
	// ·¢ÉäÉäÏß
	GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_PhysicsBody,
		Params
	);

	// ¼ì²â³É¹¦
	if (Hit.GetComponent() && Hit.GetComponent()->IsSimulatingPhysics()) {
		OutHitResult = Hit;
		return true;
	}
	// ¼ì²âÊ§°Ü
	return false;
}
void UPhysicsGrabComponent::GrabObject(UPrimitiveComponent* Component)
{

	if (!PhysicsHandle || !Component) return;

	PhysicsHandle->GrabComponentAtLocationWithRotation(
		Component,
		NAME_None,
		Component->GetComponentLocation(),
		Component->GetComponentRotation()
	);
	HeldComponent = Component;
}

void UPhysicsGrabComponent::ReleaseObject()
{
	if (PhysicsHandle && HeldComponent) {
		PhysicsHandle->ReleaseComponent();
		HeldComponent = nullptr;
	}
}
