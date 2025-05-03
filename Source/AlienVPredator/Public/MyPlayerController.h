// Copyright Rohit VFS 2023-2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"


class UInputMappingContext;

UCLASS()
class ALIENVPREDATOR_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	// Input Actions (Exposed to Editor)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveForwardAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveRightAction;
	
protected:
	// InputComponent setup
	virtual void SetupInputComponent() override;

	// Input Action Functions
	UFUNCTION()
	void MoveForward(const struct FInputActionValue& Value);

	UFUNCTION()
	void MoveRight(const struct FInputActionValue& Value);


private:

	
	// Movement Speed (Exposed to Editor)
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MovementSpeed = 500.0f;
};