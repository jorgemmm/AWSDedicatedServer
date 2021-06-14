// Fill out your copyright notice in the Description page of Project Settings.


#include "AWSBloodDemo/AWSGameInstance.h"

#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#include "Misc/Guid.h"


#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

//#include "MenuSystem/MenuInterface.h"
//
#include "AWSBloodDemo/MenuSystem/MainMenu.h"
#include "AWSBloodDemo/MenuSystem/InGameMenu.h"
#include "AWSBloodDemo/MenuSystem/MenuInterface.h"




UAWSGameInstance::UAWSGameInstance(const FObjectInitializer & ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Gameinstance Constructor"));
	

	//WidgetBlueprint'/Game/UI/WBP_MainMenu.WBP_MainMenu'
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/UI/WBP_MainMenu"));


	if (MenuBPClass.Class != NULL)
	{
		MenuClass = MenuBPClass.Class;

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Gameinstance Constructor:  Menuclass not founded it"));
	}
	
	static ConstructorHelpers::FClassFinder<UUserWidget> PauseBPClass(TEXT("/Game/UI/WBP_InGameMenu"));

	if (PauseBPClass.Class != NULL)
	{
		InGameMenuClass = PauseBPClass.Class;

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Gameinstance Constructor:  PauseClass not founded it"));
	}
	//To find Platformtrigger class for debug
	/*
	static ConstructorHelpers::FClassFinder<APlatformTrigger> PlatformTriggerBPClass(TEXT("/Game/Blueprints/BP_PlatformTrigger"));
	if (PlatformTriggerBPClass.Class != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *PlatformTriggerBPClass.Class->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlatformTriggerBPClass Not Founded"));
	}
	*/
}


void UAWSGameInstance::Init()
{
	Super::Init();



	UE_LOG(LogTemp, Warning, TEXT("Gameinstance Init"));

	if (MenuClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MenuClass class is none or null"));
	}

	if (InGameMenuClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *InGameMenuClass->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InGameMenuClass class is none or null"));
	}

}



void UAWSGameInstance::LoadMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("Gameinstance LoadMenu"));

		if (!MenuClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("MenuClass class is none or null"));
			return;
		}
			/*UUserWidget* MenuWidget = CreateWidget<UUserWidget>(this, MenuClass);
			if (!MenuWidget)
			{
				UE_LOG(LogTemp, Error, TEXT("LobbyMenu (Main Menu) NOT Created!!!"));
			
				return;
			}*/


		Menu = CreateWidget<UMainMenu>(this, MenuClass);
		
		if (!Menu)
		{
			UE_LOG(LogTemp, Error, TEXT("LobbyMenu (Main Menu) NOT Created!!!"));
			return;
		}
		
		
		Menu->Setup();


		Menu->AddToViewport();

	
	   //Menu->SetMenuInterface(this);
		
		

	
	

}

void UAWSGameInstance::LoadPause()
{
	UE_LOG(LogTemp, Warning, TEXT("Gameinstance Load Pause"));

	if (!InGameMenuClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("InGameMenu Class is none or null"));
		UE_LOG(LogTemp, Error, TEXT("InGameMenu  NOT Created!!!"));
		return;
	}
		//UUserWidget* Menu =	CreateWidget<UUserWidget>(this, MenuClass);
	    InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);
		
		
		if (!InGameMenu)
		{
			UE_LOG(LogTemp, Error, TEXT("InGameMenu  NOT Created!!!"));
			return;
		}
			//InGameMenu->SetGameInstanceREF();
	     InGameMenu->Setup();

		 InGameMenu->AddToViewport();

			//Pause->SetMenuInterface(this);
		
	

}


void UAWSGameInstance::Host()
{

	UE_LOG(LogTemp, Warning, TEXT("AWSGameInstance:: Host.."));
	


		if (Menu != nullptr)
		{
			//Menu->RemoveFromParent();
			Menu->TearDown();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("MainMenu not loaded at Gameinstance::Host"));
			UE_LOG(LogTemp, Error, TEXT("MainMenu not remove at Gameinstance::Host"));
		}

	

		UEngine* Engine = GetEngine();
		if (!Engine)
		{
			UE_LOG(LogTemp, Error, TEXT("Engine not Loaded ¿?¿?¿?¿?"));
			UE_LOG(LogTemp, Warning, TEXT("Hosting at log"));
			return;
		}
		Engine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, TEXT("Hosting"));
		

		UWorld* world = GetWorld();

		if(!world)
		{
			UE_LOG(LogTemp, Error, TEXT("Map content (World) not Loaded ¿?¿?¿"));
			return;		
		}


		UE_LOG(LogTemp, Warning, TEXT("I´m Going to AWS server Map"));
		//Faltan modulos ¿?
		//127.0.0.1
		//Openoworld
		
		//
		//world->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
		//world->ServerTravel("127.0.0.1");
	    //world->ServerTravel("/Game/Maps/FirstPBloodDemoServerMap?listen");
		
		
			//Dedicated server
		//UGameplayStatics::OpenLevel(GetWorld(), “LevelName”, true, “listen”)
		UGameplayStatics::OpenLevel(GetWorld(), "/Game/Maps/FirstPBloodDemoServerMap?listen");
		//UGameplayStatics::OpenLevel(GetWorld(), "/Game/Maps/FirstPBloodDemoServerMap");
			
	
	    // Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		Engine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("I´m Going to AWS server Map!"));
}



void UAWSGameInstance::Join(const FString& Address)
{

	UE_LOG(LogTemp, Warning, TEXT("puzle platfrom Game instance:: Join.."));
	if (Menu != nullptr)
	{
		Menu->TearDown();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MainMenu not loaded at Gameinstance::Join"));
		UE_LOG(LogTemp, Error, TEXT("MainMenu not remove at Gameinstance::Join"));
	}

	UEngine* Engine = GetEngine();

	if (Engine != nullptr)
	{
		Engine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, FString::Printf(TEXT("Joining  %s"), *Address));

	}
	UWorld* world = GetWorld();

	if (!world)
	{
		UE_LOG(LogTemp, Error, TEXT("Map content (World) not Loaded in GI Join ¿?¿?¿"));
		return;
	}
	//APlayerController* PC = GetFirstLocalPlayerController();
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("I´m Going to Join the game in a AWS server Map"));
		PC->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Playercontroller not Loaded at Joining"));

		Engine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, TEXT("Playercontroller not Loaded at Joining"));

	}


}

void UAWSGameInstance::Quit()
{
	UE_LOG(LogTemp, Warning, TEXT("Game instance:: Quit Game.."))


		APlayerController* PC = GetFirstLocalPlayerController();
	if (PC != nullptr)
	{
		//PC->ConsoleCommand("quit");
		UWorld* world = GetWorld();
		if (world)
		{
			UKismetSystemLibrary::QuitGame(world, PC, EQuitPreference::Quit, false);

		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT(" Quit Game not posible At GI"));
			UE_LOG(LogTemp, Error, TEXT("Because UWorld* is nullptr or none at Gameinstance"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" Quit Game not posible At GI"));
		UE_LOG(LogTemp, Error, TEXT("Because APlayerController is nullptr or none at Gameinstance"));
	}



}

void UAWSGameInstance::LoadMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("puzle platform Game instance:: Quit Pause.."));

	UEngine* Engine = GetEngine();
	UWorld* world = GetWorld();

	//if (world)
	//{
	//	
	//	ReturnToMainMenu();	//Retorna al mapa establecido como default en maps & Modes	
	//	LoadMenu();
	//}

	if (!world)
	{
		UE_LOG(LogTemp, Error, TEXT("Level not Loaded at Joining"));
		if(Engine)
		Engine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, TEXT("level not Loaded at Joining"));

		return;
	}
	APlayerController* PC = GetFirstLocalPlayerController();
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("Playercontroller not Loaded at Joining"));

		Engine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, TEXT("Playercontroller not Loaded at Joining"));

		return;
	}
	
	//PC->ClientTravel("/Game/Maps/BloodDemoEntryMap", ETravelType::TRAVEL_Relative,true)
	PC->ClientTravel("/Game/Maps/BloodDemoEntryMap", ETravelType::TRAVEL_Absolute);
	//PC->ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
	
	


}

void UAWSGameInstance::GoToLevel(const FString& Address)
{
	//Exmaple Address: "/Game/Maps/Lobby" or "/Game/Maps/Lobby?listen"
	UE_LOG(LogTemp, Warning, TEXT("Gameinstance BeginPlay"));

	UWorld* world = GetWorld();

	if (world != nullptr)
	{
		if (world->ServerTravel(*Address))
		{
			//Nor implemented yet
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ServerTravel Not Travelled to EmptyMap"));
		}

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Map content (World) not Loaded at BeginPlay"));
	}


}