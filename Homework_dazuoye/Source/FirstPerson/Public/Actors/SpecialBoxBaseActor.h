// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpecialBoxBaseActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UBoxTriggerActorComponent;
class UPrimitiveComponent;


UCLASS()
class FIRSTPERSON_API ASpecialBoxBaseActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASpecialBoxBaseActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> BoxCollisionComponent;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Components")
	TSubclassOf<UBoxTriggerActorComponent> TriggerActorClass;

	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category = "Components")
	TArray<UPrimitiveComponent*> OverlappingComponents;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable,Category = "Overrides")
	void OnOverlapStay_Float(float DeltaTime);
	
	UFUNCTION(BlueprintNativeEvent,Category = "Overrides")
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) ;
	virtual void OnComponentBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) ;

	UFUNCTION(BlueprintNativeEvent,Category = "Overrides")
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void OnComponentEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintNativeEvent,Category = "Overrides")
	void SetSphereSimulation(bool bIsSimu);
	virtual void SetSphereSimulation_Implementation(bool bIsSimu);
	UFUNCTION(BlueprintCallable,Category = "Overrides")
	void BeginOverlap_PassLevel(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) ;
	
	UFUNCTION(BlueprintCallable,Category = "Overrides")
	void BeginOverlap_Lava(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) ;

	UFUNCTION(BlueprintCallable,Category = "Overrides")
	void BeginOverlap_Float(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) ;

	UFUNCTION(BlueprintCallable,Category = "Overrides")
	void EndOverlap_Float(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Components")
	int MyLevelIndex;

	UFUNCTION(BlueprintNativeEvent,Category = "Overrides")
	void OnPassLevel(int LevelIndex) ;
	virtual void OnPassLevel_Implementation(int LevelIndex);

	UFUNCTION(BlueprintCallable,Category = "Door")
	void BindEvent() ;

	
	UPROPERTY(EditAnywhere,Category = "Blow/Data")
	FVector LocalPos;
	
	UFUNCTION(BlueprintCallable,Category = "Blow/Function")
	void BindBlowEvent() ;

	UFUNCTION(BlueprintCallable,Category = "Blow/Function")
	void EndBlow();
	
	UFUNCTION(BlueprintCallable,Category = "Blow/Function")
	void BlowBroadcast();
	
	UFUNCTION(BlueprintCallable,Category = "Blow/Function")
	void StartBlow(FVector Pos);

	FORCEINLINE void SetCanBlow(bool bcan){bCanBlow = bcan;}
private:
	UPROPERTY(EditAnywhere,Category="FanConfig")
	bool bReady = false;
	
	UPROPERTY(EditAnywhere,Category="FanConfig")
	bool bCanBlow = false;

	UPROPERTY(EditAnywhere,Category="FanConfig")
	float FloatArea = 0;
	
	bool bBroadcast = false;
	
	UPROPERTY(EditAnywhere,Category="Blow/Data")
	float BlowMaxTime = 3.0f;
	
	UPROPERTY(EditAnywhere,Category="Blow/Data")
	float BlowBroadcastTime = 2.5f;
	
	float BlowingTime = 0;
	
};


