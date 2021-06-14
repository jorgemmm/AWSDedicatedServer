// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "UMenuWidget.generated.h"

/**
 * 
 */
class IMenuInterface;
class UAWSGameInstance;

UCLASS(config = Game)
class AWSBLOODDEMO_API UUMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetMenuInterface(IMenuInterface* menuInterface); //To avoid coupling
    
	bool SetGameInstanceREF(); 


	void Setup();

	void TearDown();


protected:

	IMenuInterface* MenuInterface;

	UAWSGameInstance* UAWSGameInstanceRef;

public:

	UAWSGameInstance* GetAWSGameInstance() const;

	
};
