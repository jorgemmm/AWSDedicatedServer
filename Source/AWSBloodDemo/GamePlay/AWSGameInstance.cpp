// Fill out your copyright notice in the Description page of Project Settings.


#include "AWSBloodDemo/GamePlay/AWSGameInstance.h"

#include "Engine/Engine.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

#include "UObject/ConstructorHelpers.h"

UAWSGameInstance::UAWSGameInstance(const FObjectInitializer & ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
	
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/UI/WBP_MainMenu"));
	if (MenuBPClass.Class!=NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuBPClass.Class->GetName());

		MenuClass = MenuBPClass.Class;
	}
	


}

void UAWSGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}


void UAWSGameInstance::LoadMenu()
{
	if (!MenuClass) return;

	UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);
	if (!Menu) return;

	Menu->AddToViewport();


	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!PlayerController) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(Menu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;
}

void UAWSGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	//World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");


}

void UAWSGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}



