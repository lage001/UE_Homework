// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MyUserWidget.h"

#include "MyPlayerController.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "FirstPerson/FirstPersonCharacter.h"
#include "FirstPerson/FirstPersonGameMode.h"
#include "Kismet/GameplayStatics.h"


void UMyUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	// TimeTextBlock->SetText(FText::GetEmpty());
	// ScoreTextBlock->SetText(FText::AsNumber(0));
	InitializeChanceBars();
	BindEvent();
}


void UMyUserWidget::UpdateScoreText(int32 Score) 
{
	ScoreTextBlock->SetText(FText::AsNumber(Score));
}

void UMyUserWidget::UpdateTimeText(int32 Time)
{
	TimeTextBlock->SetText(FText::AsNumber(Time));
}

void UMyUserWidget::SetFuncPtr(const FEndGameCallBack &Function)
{
	Callfunc = Function;
}

void UMyUserWidget::InitializeChanceBars()
{
	ChanceBars.Add(ChanceBar_0);
	ChanceBars.Add(ChanceBar_1);
	ChanceBars.Add(ChanceBar_2);
	for (auto &Bar:ChanceBars)
	{
		Bar->SetRenderOpacity(0);
		Bar->SetPercent(1);
	}
}

void UMyUserWidget::FadeIn(UWidget* ui)
{
	if (UIOnAnimation==nullptr)
	{
		UIOnAnimation = ui;
	}
	UIOnAnimation->SetRenderOpacity(0.0f);
	GetWorld()->GetTimerManager().SetTimer(FadeTimerHandle,this,&UMyUserWidget::UpdateFadeIn,0.02f,true);
	
}

void UMyUserWidget::UpdateFadeIn()
{
	if (UIOnAnimation!=nullptr)
	{
		float CurrentOpacity = UIOnAnimation->GetRenderOpacity();
		if (CurrentOpacity<1.0f)
		{
			UIOnAnimation->SetRenderOpacity(CurrentOpacity+DeltaOpacity);
		}else
		{
			GetWorld()->GetTimerManager().ClearTimer(FadeTimerHandle);
			UIOnAnimation = nullptr;
		}
	}
}

void UMyUserWidget::FadeOut(UWidget* ui)
{
	if (UIOnAnimation==nullptr)
	{
		UIOnAnimation = ui;
	}
	if (UIOnAnimation->GetRenderOpacity()>0)
	{
		GetWorld()->GetTimerManager().SetTimer(FadeTimerHandle,this,&UMyUserWidget::UpdateFadeOut,0.02f,true);
	}
}

void UMyUserWidget::UpdateFadeOut()
{
	if (UIOnAnimation!=nullptr)
	{
		float CurrentOpacity = UIOnAnimation->GetRenderOpacity();
		if (CurrentOpacity>0.0f)
		{
			UIOnAnimation->SetRenderOpacity(CurrentOpacity-DeltaOpacity);
		}else
		{
			GetWorld()->GetTimerManager().ClearTimer(FadeTimerHandle);
			UIOnAnimation = nullptr;
		}
	}
}

void UMyUserWidget::RefreshProgressBar()
{
	if (ChargeProgressBar)
	{
		ChargeProgressBar->SetPercent(0);
	}
}

void UMyUserWidget::OnUsedChance(int32 Num)
{
	ChanceProgressBar = ChanceBars[Num-1];
	ChanceNum--;
	GetWorld()->GetTimerManager().SetTimer(ChanceBarTimerHandle,this,&UMyUserWidget::UpdateChanceBar_OnDecline,0.02f,true);
}

void UMyUserWidget::UpdateProgressBar_OnIncrease(float Alpha)
{
	if (ChargeProgressBar)
	{
		
		float CurPercent = ChargeProgressBar->GetPercent();
		ChargeProgressBar->SetPercent(CurPercent+Alpha);
	}
}

void UMyUserWidget::StartProgressBarDecline()
{
	if (ChargeProgressBar&&ChargeProgressBar->GetPercent()>0)
	{
		GetWorld()->GetTimerManager().SetTimer(ChargeProgressBarTimerHandle,this,&UMyUserWidget::UpdateProgressBar_OnDecline,0.02f,true);
	}
}

void UMyUserWidget::UpdateProgressBar_OnDecline()
{
	if (ChargeProgressBar)
	{
		float CurPercent = ChargeProgressBar->GetPercent();
		if (CurPercent>0)
		{
			ChargeProgressBar->SetPercent(CurPercent-0.02f);
		}else
		{
			GetWorld()->GetTimerManager().ClearTimer(ChargeProgressBarTimerHandle);
		}
	}
	
}

void UMyUserWidget::UpdateChanceBar_OnDecline()
{
	
	if (ChanceProgressBar)
	{
		float CurPercent = ChanceProgressBar->GetPercent();
		if (CurPercent>0)
		{
			
			ChanceProgressBar->SetPercent(CurPercent-0.02f);
			UE_LOG(LogTemp,Warning,TEXT("%s,%f"),*ChanceProgressBar->GetName(),ChanceProgressBar->GetPercent());
		}else
		{
			GetWorld()->GetTimerManager().ClearTimer(ChanceBarTimerHandle);
			
			if (ChanceNum==0)
			{
				Callfunc();
			}
		}
	}
}

void UMyUserWidget::BindEvent()
{
	AFirstPersonGameMode* FirstPersonGameMode = Cast<AFirstPersonGameMode>(UGameplayStatics::GetGameMode(this));
	FirstPersonGameMode->OnLevelStart.AddDynamic(this,&UMyUserWidget::ShowCurrentLevel);
	FirstPersonGameMode->OnLevelStart.AddDynamic(this,&UMyUserWidget::ShowChanceBars);
	AFirstPersonCharacter* FirstPersonCharacter = Cast<AFirstPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	FirstPersonCharacter->OnCharacterUseChance.AddDynamic(this,&UMyUserWidget::OnUsedChance);
	
}

void UMyUserWidget::ShowChanceBars(int32 Index)
{
	if (Index == 1||Index==2)
	{
		if (ChanceBars[0]->GetRenderOpacity()==0)
		{
			PlayAnimation(ChanceBarFadeIn);
		}
	}
}

void UMyUserWidget::HideChanceBars(int32 Index)
{
	if (Index == 3)
	{
		PlayAnimation(ChanceBarFadeOut);
	}
}

UWidget* UMyUserWidget::GetChargeProgressBar()
{
	return ChargeProgressBar;
}

UWidget* UMyUserWidget::GetShowLevelTextBlock()
{
	return ShowLevelTextBlock;
}

void UMyUserWidget::ShowCurrentLevel_Implementation(int32 Index)
{
}



