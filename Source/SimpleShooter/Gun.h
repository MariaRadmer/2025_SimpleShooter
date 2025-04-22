// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"



UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void PullTrigger();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	UParticleSystem* BulletHit;

	UPROPERTY(EditAnywhere)
	USoundBase* BulletHitSound;


	UPROPERTY(EditAnywhere)
	float maxGunRange = 1000;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	private:
	bool GunTrace(FHitResult& HitResult, FVector& ShotDirection);

	AController* GetOwnerController() const;
};
