// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AWSBloodDemo/MenuSystem/UMenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;
//class IMenuInterface;
class UAWSGameInstance;
class UWidgetSwitcher;
class UWidget;
class UEditableTextBox;


//class APlayerController;
/**
 * 
 */
UCLASS()
class AWSBLOODDEMO_API UMainMenu : public UUMenuWidget//public UUserWidget
{
	GENERATED_BODY()


public:

	UMainMenu(const FObjectInitializer & ObjectInitializer);

	/*UFUNCTION()
		void Setup();

	    void TearDown();*/
	
	
protected:

	virtual bool  Initialize() override;

private:

		//Buttons
	//Buttons Host-Join Main menu
	

	//UPROPERTY(meta = (BindWidget))
	//	 UButton* OpenJoinMenuBtn;

	//UPROPERTY(meta = (BindWidget))
	//	UButton* OpenQuitMenuBtn;

	



	//Butttons Join Back to main menu
	UPROPERTY(meta = (BindWidget))
		 UButton* CancelJoinMenuButton;
	/*Confirm join to server ip, to game*/
	UPROPERTY(meta = (BindWidget))
		UButton* ConfirmJoinMenuButton;

	/*Open Join menu*/
	UPROPERTY(meta = (BindWidget))
		 UButton* JoinBtn;

	/*Host a server*/
	UPROPERTY(meta = (BindWidget))
		UButton* HostBtn;

	UPROPERTY(meta = (BindWidget))
		class UButton* QuitBtn;

	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* MenuSwitcher;

	/*Size box o elemento widget padre seleccionado del UWidgetSwitcher*/
	UPROPERTY(meta = (BindWidget))
		UWidget* MainMenu;
	
	/*Size box o elemento widget padre seleccionado del UWidgetSwitcher*/
	UPROPERTY(meta = (BindWidget))
		UWidget* JoinMenu;

	//Enter manual IP server and port
	UPROPERTY(meta = (BindWidget))
		UEditableTextBox* IPAddressField;

	UPROPERTY(meta = (BindWidget))
		UPanelWidget* ServerList;

	TSubclassOf<class UUserWidget> ServerRowClass;


	UFUNCTION()
		void HostServer();

	UFUNCTION()
		void JoinServer();

	UFUNCTION()
		void OpenJoinMenu();

	

	UFUNCTION()
		void OpenMainMenu();

	UFUNCTION()
		void QuitPressed();

	//UAWSGameInstance* UAWSGameInstanceRef;

	//No voy a poner interfases
    //no aporta valor añadido
	//IMenuInterface* MenuInterface;

	//APlayerController* PC;

public:
	

};
