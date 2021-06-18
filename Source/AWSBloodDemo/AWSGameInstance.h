// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "AWSBloodDemo/MenuSystem/MenuInterface.h"
#include "AWSGameInstance.generated.h"

class UUserWidget;
class UMenuInterface;
class UMainMenu;
class UInGameMenu;

/**
 * 
 */
UCLASS(config = Game)
class AWSBLOODDEMO_API UAWSGameInstance : public UGameInstance//, public UMenuInterface
{
	GENERATED_BODY()

public:
	UAWSGameInstance(const FObjectInitializer & ObjectInitializer);


	virtual void Init() override;

	//UFUNCTION(Exec)
	/** Allows other classes to safely Load Menu*/
	UFUNCTION(BlueprintCallable, Category = "UIMenu")
		void LoadMenuWidget();

	UFUNCTION(BlueprintCallable, Category = "UIMenu")
		void LoadPause();



	/*
	UFUNCTION(BlueprintCallable, Category = "UIMenu")
	virtual void Host() override;
	UFUNCTION(BlueprintCallable)
	virtual void Join(const FString& Address) override;
*/

//Main Menu
	UFUNCTION(Exec)
		void Host(); //override;

	UFUNCTION(Exec)
		void Join(const FString& Address);// override;

	UFUNCTION(Exec)
		void QuitGame();// override;



	UFUNCTION(Exec)
	virtual void LoadMainMenu();// override;

	//protected:
	// Called when the game starts or when spawned
	UFUNCTION(BlueprintCallable, Category = "UIMenu")
		void GoToLevel(const FString& Address);



private:

	TSubclassOf<UUserWidget> MenuClass;

	TSubclassOf<UUserWidget> InGameMenuClass;


	UMainMenu* Menu;

	UInGameMenu* InGameMenu;

	IOnlineSessionPtr SessionInterfacePtr;

	//TSharedRef< class FOnlineSessionSearch > SessionSearchREF;//(new FOnlineSessionSearch());
	TSharedPtr< FOnlineSessionSearch>  SessionSearch;

	void OnCreateSessionComplete(FName SessionName, bool Succes);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	
	void OnFindSessionComplete(bool Success);

	void CreateSession();

	void FoundedSession();
	
};
