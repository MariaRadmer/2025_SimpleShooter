// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"

#include "AIController.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = "Update player location if seen";
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& InOwnerComp, uint8* InNodeMemory, float DeltaSeconds)
{
	Super::TickNode(InOwnerComp, InNodeMemory, DeltaSeconds);

	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

	AAIController* controller = InOwnerComp.GetAIOwner();
	if(controller == nullptr)
	{
		return;
	}

	if(controller->LineOfSightTo(playerPawn)){

		InOwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(),playerPawn);

	}else {
		InOwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}

