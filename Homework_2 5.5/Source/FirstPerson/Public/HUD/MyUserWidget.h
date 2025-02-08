// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"


class UTextBlock;
/**
 * 
 */

UCLASS()
class FIRSTPERSON_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TimeTextBlock;
	
	
	void UpdateScoreText(int32 Score);

	void UpdateTimeText(int32 Time);

private:
	virtual void NativeOnInitialized() override;
};
