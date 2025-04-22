// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"

#include "AIController.h"

#include "SimpleShooter/MyPawn.h"
#include "SimpleShooter/Shooter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& InOwnerComp, uint8* InNodeMemory)
{
	Super::ExecuteTask(InOwnerComp, InNodeMemory);

	AAIController* controller = InOwnerComp.GetAIOwner();

	if(controller == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AShooter* character = Cast<AShooter>(controller->GetPawn());

	if(character==nullptr)
	{
		return EBTNodeResult::Failed;
	}

	character->Shoot(); 

	return EBTNodeResult::Succeeded;
}
