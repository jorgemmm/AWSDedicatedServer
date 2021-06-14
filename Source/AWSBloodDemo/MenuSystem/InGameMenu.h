// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AWSBloodDemo/MenuSystem/UMenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class AWSBLOODDEMO_API UInGameMenu : public UUMenuWidget//public UUserWidget
{
	GENERATED_BODY()



protected:

	virtual bool  Initialize() override;

private:



	//BackBtn
	UPROPERTY(meta = (BindWidget))
		class UButton* CancelInGameMenuBtn;

	UPROPERTY(meta = (BindWidget))
		class UButton* QuitBtn;




	UFUNCTION()
		void CancelPressed();

	UFUNCTION()
		void QuitPressed(); //Aquí regresamos a main menu es decir regresamos al Lobby
	
};
