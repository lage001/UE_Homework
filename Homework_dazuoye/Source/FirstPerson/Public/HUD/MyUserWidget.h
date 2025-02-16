// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"


class UTextBlock;
class UProgressBar;
class AMyPlayerController;
typedef std::function<void()> FEndGameCallBack;
// class UProgressBar;
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
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ShowLevelTextBlock;

	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ChargeProgressBar;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ChanceBar_0;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ChanceBar_1;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ChanceBar_2;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="ChanceBars")
	TArray<TObjectPtr<UProgressBar>> ChanceBars;
	
	UPROPERTY(BlueprintReadOnly,Transient,meta=(BindWidgetAnim))
	UWidgetAnimation* ChanceBarFadeIn;
	
	UPROPERTY(BlueprintReadOnly,Transient,meta=(BindWidgetAnimOptional))
	UWidgetAnimation* ChanceBarFadeOut;

	UFUNCTION(BlueprintCallable,Category="ChanceBars")
	void InitializeChanceBars();
	UFUNCTION(BlueprintCallable,Category="Animation")
	void FadeIn(UWidget* ui);
	
	UFUNCTION(BlueprintCallable,Category="Animation")
	void FadeOut(UWidget* ui);

	UFUNCTION(BlueprintCallable,Category="Animation")
	void UpdateProgressBar_OnIncrease(float Alpha);
	
	UFUNCTION(BlueprintCallable,Category="Animation")
	void StartProgressBarDecline();

	UFUNCTION(BlueprintCallable,Category="Animation")
	void RefreshProgressBar();

	UFUNCTION(BlueprintCallable,Category="Animation")
	void OnUsedChance(int32 Num);

	UFUNCTION(BlueprintNativeEvent)
	void ShowCurrentLevel(int32 Index);
	void ShowCurrentLevel_Implementation(int32 Index);

	UFUNCTION(BlueprintCallable)
	void ShowChanceBars(int32 Index);
	
	UFUNCTION(BlueprintCallable)
	void HideChanceBars(int32 Index);
	
	UFUNCTION(BlueprintCallable)
	UWidget* GetChargeProgressBar();
	
	UFUNCTION(BlueprintCallable)
	UWidget* GetShowLevelTextBlock();
	
	UFUNCTION(BlueprintCallable)
	void UpdateScoreText(int32 Score);

	void UpdateTimeText(int32 Time);

	void SetFuncPtr(const FEndGameCallBack &Function);

private:
	virtual void NativeOnInitialized() override;

	FTimerHandle FadeTimerHandle;

	FTimerHandle ChargeProgressBarTimerHandle;
	
	FTimerHandle ChanceBarTimerHandle;
	
	UWidget* UIOnAnimation;

	UProgressBar* ChanceProgressBar;
	
	UPROPERTY(EditAnywhere,Category="Animation")
	float DeltaOpacity=0.02f;

	void UpdateFadeIn();
	
	void UpdateFadeOut();

	void UpdateProgressBar_OnDecline();
	
	void UpdateChanceBar_OnDecline();
	
	void BindEvent();

	

	FEndGameCallBack Callfunc;
	
	int32 ChanceNum = 3;
};




