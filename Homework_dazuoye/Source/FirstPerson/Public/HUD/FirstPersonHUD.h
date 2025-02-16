// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FirstPersonHUD.generated.h"

class UMyUserWidget;
class UEndGameWidget;
/**
 * 
 */
UCLASS()
class FIRSTPERSON_API AFirstPersonHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMyUserWidget> MyUserWidgetClass;
	TObjectPtr<UMyUserWidget> MyUserWidgetInstance;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UEndGameWidget> EndGameWidgetClass;
	TObjectPtr<UEndGameWidget> EndGameWidgetInstance;
public:
	void CreateMyUserWidget();
	void DestroyMyUserWidget();
	TObjectPtr<UMyUserWidget> GetMyUserWidget();

	void CreateEndGameWidget();
	void DestroyEndGameWidget();
	TObjectPtr<UEndGameWidget> GetEndGameWidget();
};
