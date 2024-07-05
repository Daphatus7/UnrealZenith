// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZenithGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "StateMachine/GameStateHandle.h"
#include "Zenith/GameMode/StateMachine/ZenithStateMachine.h"
#include "ZenithGameState.generated.h"

/**
 * 
 */
UCLASS()
class ZENITH_API AZenithGameState : public AGameStateBase, public IGameStateHandle
{
	GENERATED_BODY()

	UPROPERTY()
	UZenithStateMachine* StateMachine;
	//tick
    virtual void Tick(float DeltaTime) override;
public:
	//on begin play
	virtual void BeginPlay() override;

#pragma region IGameStateHandle
	//IGameState Handle
	virtual void DawnEvent() override {
		if (AZenithGameMode* GameMode = Cast<AZenithGameMode>(GetWorld()->GetAuthGameMode())) {
			GameMode->OnDawnEvent();
		}
	}
	virtual void MorningEvent() override
	{
		if (AZenithGameMode* GameMode = Cast<AZenithGameMode>(GetWorld()->GetAuthGameMode())) {
			GameMode->OnMorningEvent();
		}
	}
	virtual void NoonEvent() override
	{
		if(AZenithGameMode* GameMode = Cast<AZenithGameMode>(GetWorld()->GetAuthGameMode())) {
			GameMode->OnNoonEvent();
		}
	}
	virtual void DuskEvent() override
	{
		if(AZenithGameMode* GameMode = Cast<AZenithGameMode>(GetWorld()->GetAuthGameMode())) {
			GameMode->OnDuskEvent();
		}
	}
	virtual void NightEvent() override
	{
		if(AZenithGameMode* GameMode = Cast<AZenithGameMode>(GetWorld()->GetAuthGameMode())) {
			GameMode->OnNightEvent();
		}
	}
	virtual void MidnightEvent() override
	{
		if(AZenithGameMode* GameMode = Cast<AZenithGameMode>(GetWorld()->GetAuthGameMode())) {
			GameMode->OnMidnightEvent();
		}
	}
#pragma endregion
};
