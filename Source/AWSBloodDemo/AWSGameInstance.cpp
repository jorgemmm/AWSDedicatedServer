// Fill out your copyright notice in the Description page of Project Settings.


#include "AWSBloodDemo/AWSGameInstance.h"

#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


#include "Misc/Guid.h"


#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

//Tools
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Templates/SharedPointer.h"

//#include "MenuSystem/MenuInterface.h"
//
#include "AWSBloodDemo/MenuSystem/MainMenu.h"
#include "AWSBloodDemo/MenuSystem/InGameMenu.h"
#include "AWSBloodDemo/MenuSystem/MenuInterface.h"

//Online
//#include "OnlineSubsystem.h"
//#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"


const static FName SESSION_NAME = TEXT("My Session Game");

const static bool SESSION_IS_LAN = true;

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
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Subsystem %s"), *Subsystem->GetSubsystemName().ToString());
		SessionInterfacePtr = Subsystem->GetSessionInterface();
		if (SessionInterfacePtr.IsValid()) 
		{
			/*UE_LOG(LogTemp, Warning, TEXT("Found Session"));*/
			
			SessionInterfacePtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UAWSGameInstance::OnCreateSessionComplete);
			SessionInterfacePtr->OnDestroySessionCompleteDelegates.AddUObject(this,  &UAWSGameInstance::OnDestroySessionComplete);
			
			SessionInterfacePtr->OnFindSessionsCompleteDelegates.AddUObject(this, &UAWSGameInstance::OnFindSessionComplete);
				
			
			//SessionSearch(new FOnlineSessionSearch());
			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			
			
			
			
			if(SessionSearch.IsValid())
			{
				//SessionSearchPointer->bIsLanQuery = true;
				UE_LOG(LogTemp, Warning, TEXT(" Starting Find Sessions"));				
				SessionInterfacePtr->FindSessions(0, SessionSearch.ToSharedRef());
				
				return;
			}

			//Otra forma de Hacerlo
			TSharedRef< class FOnlineSessionSearch > SessionSearchREF = MakeShared<class FOnlineSessionSearch>();
			TSharedPtr< class FOnlineSessionSearch> SessionSearchPointer = SessionSearchREF;
			if (SessionSearchPointer.IsValid())
			{
				SessionSearchPointer->bIsLanQuery = true;
				UE_LOG(LogTemp, Warning, TEXT(" Starting Find Sessions"));
				SessionInterfacePtr->FindSessions(0, SessionSearchREF);
				return;
			}

			{
				UE_LOG(LogTemp, Error, TEXT("Session Search Pointer No valid"));
			}
			
			
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Found Subsystem"));
	}




	/** ya comprobado en LoadMenuWidget y Load Pause
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
	*/
}



void UAWSGameInstance::LoadMenuWidget()
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


/*Para listen server; pues si dedicated server las sesiones se crean desde el servidor
y se listan desde findsesion
Básicamnete sólo hay join
Se crea una lista de servidores IP:Port
y clicas para unirte
*/
void UAWSGameInstance::Host()
{

	UE_LOG(LogTemp, Warning, TEXT("AWSGameInstance:: Host.."));
	//IOnlineSessionPtr	SessionInterfacePtr = Subsystem->GetSessionInterface();
	if (SessionInterfacePtr.IsValid())
	{
		auto ExistingSession = SessionInterfacePtr->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			SessionInterfacePtr->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}

		


}

/*Para listen server*/
void UAWSGameInstance::OnCreateSessionComplete(FName SessionName, bool Succes)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete"));

	if(!Succes)
	{
		UE_LOG(LogTemp, Warning, TEXT("It couldn't create session"));
		return;
	}
	if (Menu != nullptr)
	{
		Menu->TearDown();
	}

	UEngine* Engine = GetEngine();
	if (!Engine)
	{
		UE_LOG(LogTemp, Error, TEXT("Engine not Loaded at OnCreateSessionComplete ¿?¿?¿?¿?"));		
		return;
	}
	Engine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, TEXT("OnCreateSessionComplete"));
	
	Engine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("I´m Going to AWS server Map!"));
	
	UWorld* world = GetWorld();
	if (!world)
	{
		UE_LOG(LogTemp, Error, TEXT("Map content (World) not Loaded ¿?¿?¿"));
		return;
	}
	
	//world->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	//world->ServerTravel("127.0.0.1");
	world->ServerTravel("/Game/Maps/FirstPBloodDemoServerMap?listen");

	//Deicated Server
	//UGameplayStatics::OpenLevel(GetWorld(), “LevelName”, true, “listen”)//¿?"server");
	//UGameplayStatics::OpenLevel(GetWorld(), "/Game/Maps/FirstPBloodDemoServerMap?listen");
	//UGameplayStatics::OpenLevel(GetWorld(), "/Game/Maps/ThirdPBloodDemoServerMap?listen");	
	

	

}



void UAWSGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		CreateSession();
	}
}


void UAWSGameInstance::CreateSession()
{
	if (SessionInterfacePtr.IsValid()) {
		FOnlineSessionSettings SessionSettings;

		SessionSettings.bIsLANMatch = SESSION_IS_LAN;
		SessionSettings.NumPublicConnections = 4;
		SessionSettings.bShouldAdvertise = true;

		SessionInterfacePtr->CreateSession(0, SESSION_NAME, SessionSettings);
	}
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


void UAWSGameInstance::OnFindSessionComplete(bool Success)
{
 
	if (!Success)
	{
		UE_LOG(LogTemp, Error, TEXT("Finishing Not Findind Sessions"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Finishing Find Sessions"));
	

	//	if(SessionSearchPointer.IsValid())

	if(SessionSearch.IsValid())
	{
		//SessionSearchPointer->bIsLanQuery = true;
		//for (const FOnlineSessionSearchResult& SearchResult : SessionSearchPointer->SearchResults)
		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found session names: %s"), *SearchResult.GetSessionIdStr());
		}

		return;
	}
	//Otra forma de hacerlo
	{
		TSharedRef< class FOnlineSessionSearch > SessionSearchREF = MakeShared<class FOnlineSessionSearch>();
		TSharedPtr< class FOnlineSessionSearch>  SessionSearchPointer = SessionSearchREF;;
		if (SessionSearchPointer.IsValid()) 
		{
			for (const FOnlineSessionSearchResult& SearchResult : SessionSearchPointer->SearchResults)
			{
				UE_LOG(LogTemp, Warning, TEXT("Found session names: %s"), *SearchResult.GetSessionIdStr());
			}
			return;

		}
			
	}

	{
		UE_LOG(LogTemp, Error, TEXT("Session Search Pointer No valid"));
	}
}

void UAWSGameInstance::FoundedSession()
{
 
}

void UAWSGameInstance::QuitGame()
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