// Fill out your copyright notice in the Description page of Project Settings.


#include "LearnAnimInstance.h"

#include "GameFramework/PawnMovementComponent.h"

void ULearnAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
}

void ULearnAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.0f);
		MovementSpeed = LateralSpeed.Size();

		bInAir = Pawn->GetMovementComponent()->IsFalling();
	}
}




