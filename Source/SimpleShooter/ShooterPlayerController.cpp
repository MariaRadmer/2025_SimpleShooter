// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"



void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if(HUD !=nullptr)
	{
		HUD->RemoveFromViewport();
	}

	if(bIsWinner)
	{
		UUserWidget* winScreen =CreateWidget(this, WinScreenClass);

		if(winScreen !=nullptr)
		{
			winScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen =CreateWidget(this, LoseScreenClass);

		if(LoseScreen !=nullptr)
		{
			LoseScreen->AddToViewport();
		}
	}



	GetWorldTimerManager().SetTimer(TimerHandle,this,&APlayerController::RestartLevel,Delay);
}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUD = CreateWidget(this, CrossScreenClass);
	if(HUD !=nullptr)
	{
		HUD->AddToViewport();
	}
}
