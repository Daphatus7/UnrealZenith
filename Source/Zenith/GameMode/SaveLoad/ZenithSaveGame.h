// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/AsyncActionHandleSaveGame.h"
#include "GameFramework/SaveGame.h"
#include "Zenith/Interactable/Interactable.h"
#include "Zenith/Inventory/Resource.h"
#include "ZenithSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ZENITH_API UZenithSaveGame : public USaveGame
{
	GENERATED_BODY()
	//Seed
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame", meta = (AllowPrivateAccess = "true"))
	FRandomStream Seed;
	//Resources
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame", meta = (AllowPrivateAccess = "true"))
	TMap<E_ResourceType, int32> Resources;
	//Play Time
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame", meta = (AllowPrivateAccess = "true"))
	float PlayTime;

	//Player experience
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame", meta = (AllowPrivateAccess = "true"))
	int32 PlayerExperience;

	//Player Level
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame", meta = (AllowPrivateAccess = "true"))
	int32 PlayerLevel;
};
