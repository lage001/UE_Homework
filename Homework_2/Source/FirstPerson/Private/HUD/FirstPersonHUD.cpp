// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/FirstPersonHUD.h"
#include "HUD/MyUserWidget.h"
#include "HUD/EndGameWidget.h"

void AFirstPersonHUD::CreateMyUserWidget()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (MyUserWidgetClass != nullptr)
	{
		MyUserWidgetInstance = CreateWidget<UMyUserWidget>(PlayerController, MyUserWidgetClass);
		MyUserWidgetInstance->AddToViewport();
	}
	
}

void AFirstPersonHUD::DestroyMyUserWidget()
{

	MyUserWidgetInstance->RemoveFromParent();
	MyUserWidgetInstance->Destruct();
}

TObjectPtr<UMyUserWidget> AFirstPersonHUD::GetMyUserWidget()
{
	return MyUserWidgetInstance;
}

void AFirstPersonHUD::CreateEndGameWidget()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (EndGameWidgetClass != nullptr)
	{
		EndGameWidgetInstance = CreateWidget<UEndGameWidget>(PlayerController, EndGameWidgetClass);
		EndGameWidgetInstance->AddToViewport();
	}
}

void AFirstPersonHUD::DestroyEndGameWidget()
{
	
	EndGameWidgetInstance->RemoveFromParent();
	EndGameWidgetInstance->Destruct();
}

TObjectPtr<UEndGameWidget> AFirstPersonHUD::GetEndGameWidget()
{
	return EndGameWidgetInstance;
}






