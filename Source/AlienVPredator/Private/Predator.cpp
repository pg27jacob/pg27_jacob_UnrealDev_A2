// Copyright Rohit VFS 2023-2024

#include "Predator.h"
#include "Engine/World.h"
#include "LivingOrganism.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APredator::APredator()
{
    PrimaryActorTick.bCanEverTick = true;

    // Set the root component
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // Spring Arm setup
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 400.f;
    SpringArm->bUsePawnControlRotation = false;
    SpringArm->SetRelativeRotation(FRotator(-10.f, 0.f, 0.f));

    // Camera setup
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
    Camera->bUsePawnControlRotation = false;

    // Enable player possession
    AutoPossessPlayer = EAutoReceiveInput::Player0;
    bUseControllerRotationYaw = false;
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

    // Optional: you can add movement code here if you want to move the Predator automatically
}

void APredator::SenseForEnemy()
{
    FHitResult HitResult;
    FVector StartLocation = GetActorLocation() + GetActorForwardVector() * 50.0f;
    FVector EndLocation = StartLocation + GetActorForwardVector() * DetectionRange;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Pawn, QueryParams))
    {
        AActor* HitActor = HitResult.GetActor();
        if (HitActor && HitActor->ActorHasTag(FName("Alien")))
        {
            GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Green, TEXT("Alien Detected!"));
            ShootAtTarget(HitActor);
            DrawDebugLine(GetWorld(), StartLocation, HitResult.ImpactPoint, FColor::Red, false, 0.1f);
        }
        else
        {
            DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 0.1f);
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
