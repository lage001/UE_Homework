// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsGrabComponent.generated.h"

class UPhysicsHandleComponent;
class UPrimitiveComponent;
class AFirstPersonCharacter;
class USkeletalMeshComponent;
class AFirstPersonHUD;

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

    //������ʱ����
    UFUNCTION(BlueprintCallable)
    void ToggleGrab();
	
	UFUNCTION(BlueprintCallable)
	void StartCharging();
	
	UFUNCTION(BlueprintCallable)
	void OnCharging();

	UFUNCTION(BlueprintCallable)
	void StopCharging();
	
	UFUNCTION(BlueprintCallable)
	void CheckRealse(int32 LevelIndex);
	UPROPERTY(EditAnywhere, Category = "Grab Settings")
	float GrabDistance = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Grab Settings")
	FName GrabSocketName = "Muzzle";

	UPROPERTY(EditAnywhere, Category = "Charge Settings")
	float MaxChargingForce = 3000.0f;

	UPROPERTY(EditAnywhere, Category = "Charge Settings")
	float DeltaForce = 10;
	
	UPROPERTY(VisibleAnywhere, Category = "Charge Settings")
	float ChargingForce = 0;
private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UPhysicsHandleComponent> PhysicsHandle;
	
	UPROPERTY(VisibleAnywhere)
    TObjectPtr<UPrimitiveComponent> HeldComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AFirstPersonCharacter> Player;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<APlayerCameraManager> PlayerCameraManager;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AFirstPersonHUD> FirstPersonHUD;
	
    bool FindGrabbableObject(FHitResult& OutHitResult) const;
    void GrabObject(UPrimitiveComponent* Component);

	
	UFUNCTION(BlueprintCallable,Category="UpdateUI")
	void UpdateChargeProgressBar(float Alpha);

	bool bStartCharging = false;
};

