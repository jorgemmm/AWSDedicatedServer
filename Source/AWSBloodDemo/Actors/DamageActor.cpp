// Fill out your copyright notice in the Description page of Project Settings.


#include "AWSBloodDemo/Actors/DamageActor.h"

//Components

#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Components/StaticMeshComponent.h"
//#include "Components/SphereComponent.h"
//#include "Components/StaticMeshComponent.h"

//Engine componentes 
//#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"

//Utiles
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"






// Sets default values
ADamageActor::ADamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	
	
	//Definition for the SphereComponent that will serve as the Root component for the projectile and its collision.
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	CollisionComp->InitBoxExtent(FVector(10.f,10.f,10.f));
	CollisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = CollisionComp;


	

	HazzardEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Hazzard Effect"));
	HazzardEffect->SetupAttachment(CollisionComp);
	HazzardEffect->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
	HazzardEffect->Activate();

	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultExplosionEffect(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (DefaultExplosionEffect.Succeeded())
	{
		ExplosionEffect=DefaultExplosionEffect.Object;
	}

	DamageType = UDamageType::StaticClass();
	Damage = 10.0f;

	bReplicates = true;
	SetReplicateMovement(true);

}

// Called when the game starts or when spawned
void ADamageActor::BeginPlay()
{
	Super::BeginPlay();

	

	/*if (GetLocalRole() == ROLE_Authority)
	{

		

	}*/
}




//Solo una notificación de actor sin físicas
void ADamageActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(GetLocalRole() == ROLE_Authority)
	{
		
		if (OtherActor) UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, DamageType);
		UE_LOG(LogTemp, Warning, TEXT("Server : OnHit and Damage: %f"), Damage);
	}
	

		if (OtherActor)
		{
			
		  	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnHit and Damage")));
			
			//UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigator()->Controller, this, DamageType);
			//UGameplayStatics::ApplyPointDamage(OtherActor, Damage, NormalImpulse, Hit, GetInstigator()->Controller, this, DamageType);
			UE_LOG(LogTemp, Warning, TEXT("Client: OnHit and Damage: %f"), Damage);

		}

		Destroy();

		

	
}


void ADamageActor::Destroyed()
{
	FVector spawnLocation = GetActorLocation();
	
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, spawnLocation, FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
}



