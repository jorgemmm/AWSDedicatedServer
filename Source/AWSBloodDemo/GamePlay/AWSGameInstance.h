// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AWSGameInstance.generated.h"

/**
 * 
 */

class UUserWidget;

UCLASS(config = Game)
class AWSBLOODDEMO_API UAWSGameInstance : public UGameInstance
{
	GENERATED_BODY()


	UAWSGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init();

	UFUNCTION(BlueprintCallable)
		void LoadMenu();

	UFUNCTION(Exec)
		void Host();

	UFUNCTION(Exec)
		void Join(const FString& Address);

private:
	TSubclassOf<UUserWidget> MenuClass;
	
};
