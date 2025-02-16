// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class FIRSTPERSON_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock>  EndScoreText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock>  EndGameText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> EndGameBtn;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> RestartBtn;


	void SetScoreText(int32 Score);

	UFUNCTION(BlueprintCallable)
	void SetEndGameText(FString Text);
private:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnClickReStartBtn();
	
};
