// Fill out your copyright notice in the Description page of Project Settings.


#include "KillThemAllGameModeBase.h"

#include "EngineUtils.h"

#include "SimpleShooter/ShooterAIController.h"

void AKillThemAllGameModeBase::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	UE_LOG(LogTemp, Warning, TEXT("called PawnKilled from kill all gamemode"));

	APlayerController* playerController = Cast<APlayerController>(PawnKilled->GetController());

	if(playerController !=nullptr)
	{
		EndGame(false);
	}
	for (AShooterAIController* shooterAIController: TActorRange<AShooterAIController>(GetWorld()))
	{
		if(!shooterAIController->IsDead())
		{
			return;
		}
	}
	EndGame(true);

}

void AKillThemAllGameModeBase::EndGame(bool bIsPlayerWinner)
{
	for (AController* controller: TActorRange<AController>(GetWorld()))
	{
		bool isWinner= controller->IsPlayerController() == bIsPlayerWinner;

		controller->GameHasEnded(controller->GetPawn(),isWinner);
	}
}
