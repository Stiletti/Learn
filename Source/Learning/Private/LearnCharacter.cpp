// Fill out your copyright notice in the Description page of Project Settings.


#include "LearnCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ALearnCharacter::ALearnCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	// by default false but we need it to let the player turn into the ControlRotation based on the view controlled with mouse
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	// by default false but we need it to let the player turn into the pressed direction
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// by default true but we wont let the view be controlled by the ActorRotation
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ALearnCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALearnCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALearnCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Keyboard controls
	PlayerInputComponent->BindAxis("MoveForward", this, &ALearnCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALearnCharacter::MoveRight);

	// Mouse controls
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("ProjectileAttack", IE_Pressed, this, &ALearnCharacter::ProjectileAttack);
}

void ALearnCharacter::MoveForward(float Value)
{
	/*
	 * We use ControlRotation here to be independent from the ActorRotation so the player is always facing the direction we are
	 * looking with the camera
	 */
	
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	AddMovementInput(ControlRot.Vector(), Value);
}

void ALearnCharacter::MoveRight(float Value)
{
	// We need to create a rotator which gives us access to the ControlRotation
	FRotator ControlRot = GetControlRotation();
	// We make sure that only the yaw rotation is updated
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	/*
	 *	Unreal Coordinate System
	 *	========================
	 *	
	 *	X = Forward
	 *	Y = Right
	 *	Z = Up 
	 */
	
	// Here we need to create a vector which will align to the ControlRotation's Y
	// We uses the GetRightVector() codebase from KismetMathLibrary.cpp
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, Value);
}

void ALearnCharacter::ProjectileAttack()
{
	// We set the spawn location to a specific socket on the player SkeletalMesh
	FVector Handlocation = GetMesh()->GetSocketLocation("RightHandSocket");
	FTransform SpawnTM = FTransform(GetControlRotation(), Handlocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	// We spawn the Actor into the world so the world is handling it
	/* To spawn an Actor the world needs to know which ActorClass will be spawned (ProjectileClass in header),
	 * which rotation its using and which location it should be placed (SpawnTM)
	 * and how it should be spawned (SpawnParams)
	 */ 
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}
