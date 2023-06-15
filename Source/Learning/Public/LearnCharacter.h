// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LearnCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class LEARNING_API ALearnCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALearnCharacter();

	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	UCameraComponent* CameraComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SpawnClass)
	TSubclassOf<AActor> ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Character movement
	void MoveForward(float Value);
	void MoveRight(float Value);

	void ProjectileAttack();
};
