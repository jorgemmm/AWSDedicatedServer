// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

//Requires for this actor
#include "Animation/AnimInstance.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

//Enegine
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

//online
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

//Utils
#include  "DrawDebugHelpers.h"
// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Initialize the player's Health
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;

}




FString GetEnumText(ENetRole Role)
{
	switch (Role)
	{
	case ROLE_None:
		return "None";
	case ROLE_SimulatedProxy:
		return "SimulatedProxy";
	case ROLE_AutonomousProxy:
		return "AutonomousProxy";
	case ROLE_Authority:
		return "Authority";
	default:
		return "ERROR";
	}
}

//Setup Replication
void ABaseCharacter::GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate current health.
	DOREPLIFETIME(ABaseCharacter, CurrentHealth);
}


// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor* MyOwner = GetOwner();
	if (MyOwner != nullptr) {

		//Para el jugador
		DrawDebugString(GetWorld(),
			MyOwner->GetActorLocation(), //FVector(0, 0, 100), 
			GetEnumText(MyOwner->GetLocalRole()), this, FColor::White, DeltaTime);



	}
	else
	{
		//Para enemigos
		DrawDebugString(GetWorld(),
			GetActorLocation(), //FVector(0, 0, 100), 
			GetEnumText(GetLocalRole()), this, FColor::White, DeltaTime);
	}

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



void ABaseCharacter::OnRep_CurrentHealth()
{

	OnHealthUpdate();


}


void ABaseCharacter::OnHealthUpdate()
{
	//Client-specific functionality
	if (IsLocallyControlled())
	{
		FString healthMessage = FString::Printf(TEXT("You now have %f health remaining."), CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);

		if (CurrentHealth <= 0)
		{
			FString deathMessage = FString::Printf(TEXT("You have been killed."));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);

			// ragdoll the character
			//ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
			//if (MyCharacter)
			//{
			   // MyCharacter->GetMesh()->SetSimulatePhysics(true);
			   // //MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
			//}
		}
	}

	//Server-specific functionality
	if (GetLocalRole() == ROLE_Authority)
	{
		FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetFName().ToString(), CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
	}

	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		//Suelen ser los propietarios o los que controlan al Pawn
		//Es decir el Jugador o Hero

	}
	if (GetLocalRole() == ROLE_SimulatedProxy)
	{
		//Suelen ser los enemigos o jugadores o online
		FString healthMessage = FString::Printf(TEXT("You now have %f health remaining."), CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);

		if (CurrentHealth <= 0)
		{
			FString deathMessage = FString::Printf(TEXT("You have been killed."));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);

			// ragdoll the character
			ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
			if (MyCharacter)
			{
				MyCharacter->GetMesh()->SetSimulatePhysics(true);
				// //MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
			}
		}

	}


	//Functions that occur on all machines. 
   /*



	   Any special functionality that should occur as a result of damage or death should be placed here.
   */
}

void ABaseCharacter::SetCurrentHealth(float healthValue)
{
	//En servidor el valor de health se propagará / replicará

   // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(" Set Current Health")));
	if (GetLocalRole() == ROLE_Authority)
		//if(HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT(" Take Damage")));
		CurrentHealth = FMath::Clamp(healthValue, 0.f, MaxHealth);
		OnHealthUpdate();
	}
}

float ABaseCharacter::TakeDamage(float DamageTaken, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float damageApplied = CurrentHealth - DamageTaken;
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT(" Take Damage")));

	SetCurrentHealth(damageApplied);

	return damageApplied;
}


