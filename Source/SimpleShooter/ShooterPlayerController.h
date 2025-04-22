// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"


class UUserWidget;

UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CrossScreenClass;


	UPROPERTY(EditAnywhere)
	float Delay = 5;

	FTimerHandle TimerHandle;

	UPROPERTY()
	UUserWidget* HUD; 
};
