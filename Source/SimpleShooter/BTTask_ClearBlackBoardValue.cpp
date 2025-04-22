// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackBoardValue.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Kismet/GameplayStatics.h"

UBTTask_ClearBlackBoardValue::UBTTask_ClearBlackBoardValue()
{
	NodeName = TEXT("Clear Black bord value"); 
}

EBTNodeResult::Type UBTTask_ClearBlackBoardValue::ExecuteTask(UBehaviorTreeComponent& InOwnerComp, uint8* InNodeMemory)
{
	Super::ExecuteTask(InOwnerComp, InNodeMemory);

	InOwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	
	return EBTNodeResult::Succeeded;
}
