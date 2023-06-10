// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LearnAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API ULearnAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AnimationProperty)
	float MovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=AnimationProperty)
	bool bInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=AnimationProperty)
	APawn* Pawn;
	
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties();
};
