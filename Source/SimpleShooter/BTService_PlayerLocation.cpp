// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName= "Update player location";
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& InOwnerComp, uint8* InNodeMemory, float DeltaSeconds)
{
	Super::TickNode(InOwnerComp, InNodeMemory, DeltaSeconds);

	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

	if(playerPawn == nullptr)
	{
		return;
	}

	InOwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),playerPawn->GetActorLocation());
}
