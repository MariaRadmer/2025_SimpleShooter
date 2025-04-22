// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "SimpleShooter/Shooter.h"


void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if(AIBehaviorTree != nullptr){
		RunBehaviorTree(AIBehaviorTree);
		APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),playerPawn->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaTime){

	Super::Tick(DeltaTime);

}

bool AShooterAIController::IsDead() const
{
	AShooter* controlledCharachter = Cast<AShooter>(GetPawn());

	if(controlledCharachter != nullptr)
	{
		return controlledCharachter->IsDead();
	}

	return true; 
}
