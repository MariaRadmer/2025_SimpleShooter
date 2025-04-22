// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	SetRootComponent(Root);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh component"));
	MeshComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}



// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, MeshComponent,TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, MeshComponent,TEXT("MuzzleFlashSound"));

	FHitResult hitResult;
	FVector shotDirection;
	bool status = GunTrace(hitResult, shotDirection);

	if (status)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletHit, hitResult.Location, shotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),BulletHitSound,hitResult.Location);
		FPointDamageEvent DamageEvent(Damage, hitResult, shotDirection, nullptr);
		AActor* hitActor = hitResult.GetActor();

		if (!IsValid(hitActor))
		{
			return;
		}

		AController* ownerController = GetOwnerController();

		if (!IsValid(ownerController))
		{
			return;
		}

		hitActor->TakeDamage(Damage, DamageEvent, ownerController, this);
	}
}


bool AGun::GunTrace(FHitResult& HitResult, FVector& ShotDirection)
{
	AController* ownerController = GetOwnerController();

	if (!IsValid(ownerController))
	{
		return false;
	}

	FVector cameraLocation;
	FRotator cameraRotation;
	ownerController->GetPlayerViewPoint(cameraLocation, cameraRotation);
	ShotDirection = -cameraRotation.Vector();

	FVector end = cameraLocation + cameraRotation.Vector() * maxGunRange;

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(HitResult, cameraLocation, end, ECollisionChannel::ECC_GameTraceChannel1,params);

}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if (!IsValid(OwnerPawn))
	{
		return nullptr;
	}

	return  OwnerPawn->GetController();

}
