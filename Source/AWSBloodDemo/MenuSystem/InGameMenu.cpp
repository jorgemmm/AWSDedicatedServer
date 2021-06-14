// Fill out your copyright notice in the Description page of Project Settings.


#include "AWSBloodDemo/MenuSystem/InGameMenu.h"

#include "AWSBloodDemo/AWSGameInstance.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Widget.h"
#include "Components/EditableTextBox.h"
#include "Internationalization/Text.h"


//Engine
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


//Tools
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

bool UInGameMenu::Initialize()
{

	bool Succes = Super::Initialize();
	if (Succes != true) return false;

	//TODO
	if (CancelInGameMenuBtn != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Back To Game Button Clickled"));
		CancelInGameMenuBtn->OnClicked.AddDynamic(this, &UInGameMenu::CancelPressed);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Back To Game Button  Not Binding"));
	}


	if (QuitBtn != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Quit Button Clickled"));
		QuitBtn->OnClicked.AddDynamic(this, &UInGameMenu::QuitPressed);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Quit Button  Not Binding"));
	}


	return true;
}



//TearDown Th menu
void UInGameMenu::CancelPressed()
{
	UWorld* world = GetWorld();


	if (world != nullptr)
	{


		APlayerController* PC = world->GetFirstPlayerController();
		if (PC)
		{
			TearDown();
			UE_LOG(LogTemp, Warning, TEXT("I´m gonna Back The Game!"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Back the game Not Posible PlayerController nullptr Ingame menu"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Back the game Not Posible GetWorld() nullptr Ingame menu"));
	}

	
	
	//if (MenuInterface != nullptr)
	{
		/*UE_LOG(LogTemp, Warning, TEXT("Back The Game Correctly"));*/
		//Con interfaz es un poco tonto
		//utilizar la interfaz para dirigirte a GI
		// y luego el GI se dirige de nuevo al Pause menu
		//MenuInterface->Cancel();


		//Sin interfaz utilizando directamente el binding
		//TearDown();

	}
	//else
	{
		
		//UE_LOG(LogTemp, Error, TEXT("IMenuInterface* MenuInterface is none or nullptr"));
	}



}



void UInGameMenu::QuitPressed()
{

	UWorld* world = GetWorld();


	if (world != nullptr)
	{


		APlayerController* PC = world->GetFirstPlayerController(); //Uworld method
		//GetFirstLocalPlayerController(); GI method
		if (PC != nullptr)
		{
			TearDown(); //call from WB

			//MenuInterface->ReturnLobby();
			UAWSGameInstanceRef->LoadMainMenu();
			//TEnumAsByte 
			//UKismetSystemLibrary::QuitGame(world, PC, EQuitPreference::Quit, false);
			UE_LOG(LogTemp, Warning, TEXT("QuitGame Done!"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed When Quiting Game"));
			UE_LOG(LogTemp, Error, TEXT("Because Playercontroller is null or none"));
		}


	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed When Quiting Game"));
		UE_LOG(LogTemp, Error, TEXT("Because world is nullptr or not created"));
	}
}


