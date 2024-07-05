// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStateHandle.h"
#include "UObject/Object.h"
#include "Zenith/GameMode/TimeState.h"
#include "ZenithStateMachine.generated.h"

/**
 * 
 */
UCLASS()
class ZENITH_API UZenithStateMachine : public UObject
{
	GENERATED_BODY()
	UPROPERTY()
	float TimeOfDay;
	UPROPERTY()
	float DayLengthInSeconds;
	UPROPERTY()
	ETimeStateType CurrentState;

	UPROPERTY()
	TArray<IGameStateHandle *> GameStateHandle;
	
	//days
	UPROPERTY()
	int Days;

public:
	UFUNCTION(BlueprintCallable, Category = "Time")
	float GetTimeOfDay() const;

	UFUNCTION(BlueprintCallable, Category = "Time")
	void UpdateTimeOfDay(float DeltaSeconds);
	
	//get current time state
	UFUNCTION(BlueprintCallable, Category = "Time")
	ETimeStateType GetCurrentState() const;

	UFUNCTION(Blueprintable, Category = "Time")
	void Initialization(const TScriptInterface<IGameStateHandle>& Handle);
};
