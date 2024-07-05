// Fill out your copyright notice in the Description page of Project Settings.


#include "ZenithGameState.h"


void AZenithGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	StateMachine->UpdateTimeOfDay(DeltaTime);
	//is ticking?
}

void AZenithGameState::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
	StateMachine = NewObject<UZenithStateMachine>(this);
	StateMachine->Initialization(this);
	//enable tick
}
