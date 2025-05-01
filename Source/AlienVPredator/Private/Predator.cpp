// Copyright Rohit VFS 2023-2024

#include "Predator.h"
#include "Engine/World.h"
#include "LivingOrganism.h"
#include "DrawDebugHelpers.h" // For visualizing the raycast (optional)
#include "Engine/Engine.h"    // For GEngine

// Sets default values
APredator::APredator()
{
    // Set this actor to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;
    DetectionRange = 1000.0f; // Initialize DetectionRange here or in the editor
}

void APredator::BeginPlay()
{
    Super::BeginPlay();
    // Start the periodic sensing for enemies
    GetWorldTimerManager().SetTimer(SenseTimerHandle, this, &APredator::SenseForEnemy, 0.1f, true);
}

void APredator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APredator::SenseForEnemy()
{
    FHitResult HitResult;
    FVector StartLocation = GetActorLocation() + GetActorForwardVector() * 50.0f;
    FVector EndLocation = StartLocation + GetActorForwardVector() * DetectionRange;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    // Perform the line trace
    if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Pawn, QueryParams))
    {
        AActor* HitActor = HitResult.GetActor();
        if (HitActor && HitActor->ActorHasTag(FName("Alien"))) // Check for the "Alien" tag
        {
            GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Green, TEXT("Alien Detected!"));
            ShootAtTarget(HitActor);
            DrawDebugLine(GetWorld(), StartLocation, HitResult.ImpactPoint, FColor::Red, false, 0.1f);
        }
        else
        {
            DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 0.1f); // Different color for non-Alien hits
        }
    }
    else
    {
        DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 0.1f);
    }
}

void APredator::ShootAtTarget(AActor* Target)
{
    if (Target && Target->ActorHasTag(FName("Alien")))
    {
        GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Red, TEXT("Alien Destroyed!"));
        Target->Destroy();
    }
    else if (Target)
    {
        GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Yellow, TEXT("Target is not an Alien."));
    }
}