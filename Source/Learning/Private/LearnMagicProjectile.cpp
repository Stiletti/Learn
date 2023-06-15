// Fill out your copyright notice in the Description page of Project Settings.


#include "LearnMagicProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ALearnMagicProjectile::ALearnMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	RootComponent = SphereCollision;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
	

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSysTemComponent");
	ParticleSystemComponent->SetupAttachment(SphereCollision);
}

// Called when the game starts or when spawned
void ALearnMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALearnMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

