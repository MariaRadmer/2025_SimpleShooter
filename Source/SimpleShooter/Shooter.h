// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Shooter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooter();

	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	bool IsDead() const {return Health <=0; }

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const {return Health/MaxHealth; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY(BlueprintReadWrite)
	AGun* Gun;

	UPROPERTY(EditAnywhere)
	float MaxHealth =100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	
};
