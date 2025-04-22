// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter.h"

#include "Components/CapsuleComponent.h"

#include "SimpleShooter/Gun.h"
#include "SimpleShooter/SimpleShooterGameModeBase.h"

// Sets default values
AShooter::AShooter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AShooter::Shoot()
{
	Gun->PullTrigger();
}

// Called when the game starts or when spawned
void AShooter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);

	GetMesh()->HideBoneByName(TEXT("weapon_R"),PBO_None);
	Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
	
	Gun->SetOwner(this); 
}

// Called every frame
void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AShooter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float damageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	damageApplied = FMath::Min(Health,damageApplied);
	Health-=damageApplied;

	UE_LOG(LogTemp, Warning, TEXT("Health is %f"),Health);

	if(IsDead())
	{
		ASimpleShooterGameModeBase* gameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if(gameMode)
		{
			gameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}

	return damageApplied;
}

