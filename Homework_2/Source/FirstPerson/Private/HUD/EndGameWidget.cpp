// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/EndGameWidget.h"
#include "MyPlayerController.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UEndGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (EndScoreText!=nullptr)
	{
		EndScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"),0)));
	}
	if (EndGameBtn!=nullptr)
	{
		EndGameBtn->OnClicked.AddDynamic(this, &UEndGameWidget::OnClickEndGameBtn);
	}
	if (RestartBtn!=nullptr)
	{
		RestartBtn->OnClicked.AddDynamic(this, &UEndGameWidget::OnClickReStartBtn);
	}
	
}
void UEndGameWidget::SetScoreText(int32 Score)
{
	EndScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"),Score)));
}
void UEndGameWidget::OnClickEndGameBtn()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit,true);
}

void UEndGameWidget::OnClickReStartBtn()
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetOwningPlayer());
	if (PlayerController!=nullptr)
	{
		PlayerController->RestartGame();
	}
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}
