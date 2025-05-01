// Copyright Rohit VFS 2023-2024

#pragma once

#include "CoreMinimal.h"
#include "LivingOrganism.h"
#include "DamageInterface.h"
#include "Predator.generated.h"

/**
 * 
 */
UCLASS()
class ALIENVPREDATOR_API APredator : public ALivingOrganism
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APredator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Function to perform the line trace and check for enemies
	void SenseForEnemy();

	// Function to attempt to destroy the detected Alien
	void ShootAtTarget(AActor* Target);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// How far the Predator can "see" with its raycast
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float DetectionRange = 1000.0f;

	// Timer handle for the periodic sensing
	FTimerHandle SenseTimerHandle;
};