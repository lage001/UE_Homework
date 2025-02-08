// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsGrabComponent.generated.h"

class UPhysicsHandleComponent;
class UPrimitiveComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPERSON_API UPhysicsGrabComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPhysicsGrabComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    //点击左键时调用
    UFUNCTION(BlueprintCallable)
    void ToggleGrab();

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UPhysicsHandleComponent> PhysicsHandle;

    UPROPERTY(EditAnywhere, Category = "Grab Settings")
    float GrabDistance = 1000.0f;


    UPROPERTY(EditAnywhere, Category = "Grab Settings")
    FName GripSocketName = "Muzzle";

    UPrimitiveComponent* HeldComponent;

    bool FindGrabbableObject(FHitResult& OutHitResult) const;
    void GrabObject(UPrimitiveComponent* Component);
    void ReleaseObject();
	
};
