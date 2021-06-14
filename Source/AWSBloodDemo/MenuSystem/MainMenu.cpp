// Fill out your copyright notice in the Description page of Project Settings.



#include "AWSBloodDemo/MenuSystem/MainMenu.h"

//Project
#include "AWSBloodDemo/AWSGameInstance.h"
//#include "AWSBloodDemo/MenuSystem/MenuInterface.h"

//Engine
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


//Tools
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

//Components
#include "Components/WidgetSwitcher.h"
#include "Components/Widget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Internationalization/Text.h"

//#include "GameFramework/Actor.h"




bool  UMainMenu::Initialize()
{
	bool Succes = Super::Initialize();
	if (Succes != true) return false;

	
	//TODO: Setup

   //Buttons Host-Join Main menu
	if (!HostBtn)
	{
		UE_LOG(LogTemp, Error, TEXT("Host Button  Not Binding"));
		return false;
	}		
	{
		UE_LOG(LogTemp, Warning, TEXT("Host Button Binded"));
		HostBtn->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	}
	if (!JoinBtn) 
	{
		UE_LOG(LogTemp, Error, TEXT("Open Join Menu Button  Not Binding"));
		return false;
	}
	{
		UE_LOG(LogTemp, Warning, TEXT("Open Join Menu Button Binded"));
		JoinBtn->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	}
	if (!ConfirmJoinMenuButton)
	{
		UE_LOG(LogTemp, Error, TEXT("Confirm join Button  Not Binding"));
		return false;
	}
	{
		UE_LOG(LogTemp, Warning, TEXT("Confirm join Button Binded"));
		ConfirmJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	}
	

	if (!CancelJoinMenuButton)
	{
		UE_LOG(LogTemp, Error, TEXT("CancelJoinMenuButton Button  Not Binding"));
		return false;
	}
	{
		UE_LOG(LogTemp, Warning, TEXT("Host Button Binded"));
		CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	}

	//Siempre comprobar 
	/*UWorld* world = GetWorld();
	if (!world)
	{
		UE_LOG(LogTemp, Error, TEXT("No hay referencia del Nivel Uworld es nulptrl UMainMenu Initialize  "));
		return false;
	}
	APlayerController* PC = world->GetFirstPlayerController();
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController Ref Nullptr in Mainmenu Initialize "));
		return false;
	}*/

	/*UAWSGameInstanceRef = Cast<UAWSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!UAWSGameInstanceRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Host Ref to UAWSGameInstance Failed!!! at Initiliazed "));
		return false;
	}*/

	return true;


}


//void UMainMenu::Setup()
//{
//
//	//APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
//	
//	UWorld* world = GetWorld();
//	if (!world)
//	{
//		UE_LOG(LogTemp, Error, TEXT("No hay referencia del Nivel Uworld es nulptrl UMainMenu Setup  "));
//		return;
//	}
//	//APlayerController* PC = world->GetFirstPlayerController();
//	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
//	if (!PC)
//	{
//		UE_LOG(LogTemp, Error, TEXT("PlayerController Ref Nullptr in Mainmenu Setup "));
//		return;
//	}
//	
//	FInputModeUIOnly InputModeUIData;
//	
//	InputModeUIData.SetWidgetToFocus(this->TakeWidget());
//	InputModeUIData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
//
//	PC->SetInputMode(InputModeUIData);
//	PC->bShowMouseCursor = true;
//
//
//}
//
//void UMainMenu::TearDown()
//{
//	this->RemoveFromParent();
//
//	
//	FInputModeGameOnly InputModeGameData;
//	
//
//	UWorld* world = GetWorld();
//	if (!world)
//	{
//		UE_LOG(LogTemp, Error, TEXT("No hay referencia del Nivel Uworld es nulptrl UMainMenu TearDown  "));
//		return;
//	}
//	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
//	if (!PC)
//	{
//		UE_LOG(LogTemp, Error, TEXT("PlayerController Ref Nullptr in Mainmenu TearDown "));
//		return;
//	}
//
//	PC->SetInputMode(InputModeGameData);
//	PC->bShowMouseCursor = false;
//
//}
//


void UMainMenu::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("I´m gonna host a server!"));

	

	if (!UAWSGameInstanceRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Host Ref to UAWSGameInstance Failed!!! at HostServer  "));
		return;
	}

	GetAWSGameInstance()->Host();
	UE_LOG(LogTemp, Warning, TEXT("Host Ref to UAWSGameInstance Correct Done "));
	return;

	/*if (MenuInterface != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Host Interface Correct Done "));
		MenuInterface->Host();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Host Interface Failed!!! "));

	}*/
}

void UMainMenu::JoinServer()
{

	if (!UAWSGameInstanceRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Host Ref to UAWSGameInstance Failed!!! at JoinServer  "));
		return;
	}
	const FString& IPAddress = IPAddressField->GetText().ToString();
	GetAWSGameInstance()->Join(IPAddress);
	UE_LOG(LogTemp, Warning, TEXT("Join Ref to UAWSGameInstance Correct Done "));
	
}


void UMainMenu::OpenJoinMenu()
{
	if ((!MenuSwitcher) || (!JoinMenu)) {
		UE_LOG(LogTemp, Error, TEXT("MenuSwitcher or JoinMenu is nullptr at MainMenu OpenJoinMenu "));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Change menu to join "));
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	if ((!MenuSwitcher) || (!JoinMenu)) {
		UE_LOG(LogTemp, Error, TEXT("MenuSwitcher or JoinMenu is nullptr at MainMenu OpenMainMenu "));
		return;
	}
	MenuSwitcher->SetActiveWidget(MainMenu);
}