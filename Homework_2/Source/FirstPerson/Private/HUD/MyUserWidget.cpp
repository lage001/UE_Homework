// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MyUserWidget.h"

#include "Components/TextBlock.h"


void UMyUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	TimeTextBlock->SetText(FText::GetEmpty());
	ScoreTextBlock->SetText(FText::AsNumber(0));
}

void UMyUserWidget::UpdateScoreText(int32 Score) 
{
	ScoreTextBlock->SetText(FText::AsNumber(Score));
}

void UMyUserWidget::UpdateTimeText(int32 Time)
{
	TimeTextBlock->SetText(FText::AsNumber(Time));
}


