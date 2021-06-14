// Fill out your copyright notice in the Description page of Project Settings.


#include "AWSBloodDemo/MenuSystem/UMenuWidget.h"

#include "AWSBloodDemo/AWSGameInstance.h"
#include "AWSBloodDemo/MenuSystem/MenuInterface.h"

//Engine
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


//Tools
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"






void UUMenuWidget::SetMenuInterface(IMenuInterface* menuInterface)
{
	this->MenuInterface = menuInterface;
}


bool UUMenuWidget::SetGameInstanceREF()
{
	UAWSGameInstanceRef = Cast<UAWSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!UAWSGameInstanceRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Host Ref to UAWSGameInstance Failed!!! at Initiliazed "));
		return false;
	}
	return true;
}

void UUMenuWidget::Setup()
{
	UWorld* world = GetWorld();
	if (!world)
	{
		UE_LOG(LogTemp, Error, TEXT("No hay referencia del Nivel Uworld es nulptrl UMainMenu Setup  "));
		return;
	}
	
	//APlayerController* PC = world->GetFirstPlayerController();
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController Ref Nullptr in Mainmenu Setup "));
		return;
	}

	FInputModeUIOnly InputModeUIData;

	InputModeUIData.SetWidgetToFocus(this->TakeWidget());
	InputModeUIData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PC->SetInputMode(InputModeUIData);
	PC->bShowMouseCursor = true;
}

void UUMenuWidget::TearDown()
{
	this->RemoveFromParent();


	FInputModeGameOnly InputModeGameData;


	UWorld* world = GetWorld();
	if (!world)
	{
		UE_LOG(LogTemp, Error, TEXT("No hay referencia del Nivel Uworld es nulptrl UMainMenu TearDown  "));
		return;
	}
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController Ref Nullptr in Mainmenu TearDown "));
		return;
	}

	PC->SetInputMode(InputModeGameData);
	PC->bShowMouseCursor = false;
}


UAWSGameInstance* UUMenuWidget::GetAWSGameInstance() const
{
	return UAWSGameInstanceRef;
}
