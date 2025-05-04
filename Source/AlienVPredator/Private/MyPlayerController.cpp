// Copyright Rohit VFS 2023-2024

#include "MyPlayerController.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	EnableInput(this);

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Get the Enhanced Input Component
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Bind Input Actions
		if (MoveForwardAction)
		{
			EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AMyPlayerController::MoveForward);
		}

		if (MoveRightAction)
		{
			EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AMyPlayerController::MoveRight);
		}
	}
}

void AMyPlayerController::MoveForward(const FInputActionValue& Value)
{
	if (APawn* ControlledPawn = GetPawn())
	{
		const float AxisValue = Value.Get<float>();
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		ControlledPawn->AddMovementInput(Direction, AxisValue * MovementSpeed * GetWorld()->GetDeltaSeconds());
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Yellow, TEXT("Moving"));
	}
}

void AMyPlayerController::MoveRight(const FInputActionValue& Value)
{
	if (APawn* ControlledPawn = GetPawn())
	{
		const float AxisValue = Value.Get<float>();
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		ControlledPawn->AddMovementInput(Direction, AxisValue * MovementSpeed * GetWorld()->GetDeltaSeconds());
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Yellow, TEXT("Moving"));
	}
}

