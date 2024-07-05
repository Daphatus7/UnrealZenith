// Fill out your copyright notice in the Description page of Project Settings.


#include "ZenithStateMachine.h"

void UZenithStateMachine::UpdateTimeOfDay(float DeltaSeconds)
{
	TimeOfDay += DeltaSeconds;
	
	if(TimeOfDay >= static_cast<float>(Ts_Night))
	{
		if(CurrentState != ETimeStateType::Night)
		{
			CurrentState = ETimeStateType::Night;
			GameStateHandle[0]->NightEvent();
		}
	}
	else if(TimeOfDay >= static_cast<float>(Ts_Dusk))
	{
		if(CurrentState != ETimeStateType::Dusk)
		{
			CurrentState = ETimeStateType::Dusk;
			GameStateHandle[0]->DuskEvent();
		}
	}
	else if(TimeOfDay >= static_cast<float>(Ts_Noon))
	{
		if(CurrentState != ETimeStateType::Noon)
		{
			CurrentState = ETimeStateType::Noon;
			GameStateHandle[0]->NoonEvent();
		}
	}
	else if(TimeOfDay >= static_cast<float>(Ts_Morning))
	{
		if(CurrentState != ETimeStateType::Morning)
		{
			CurrentState = ETimeStateType::Morning;
			GameStateHandle[0]->MorningEvent();
		}
	}
	else if(TimeOfDay >= static_cast<float>(Ts_Dawn))
	{
		if(CurrentState != ETimeStateType::Dawn)
		{
			CurrentState = ETimeStateType::Dawn;
			GameStateHandle[0]->DawnEvent();
		}
	}
	else
	{
		if(CurrentState != ETimeStateType::Midnight)
		{
			CurrentState = ETimeStateType::Midnight;
			GameStateHandle[0]->MidnightEvent();
		}
	}
	if(GEngine)
	{
		const FString CurrentStateString = StaticEnum<ETimeStateType>()->GetValueAsString(CurrentState);
		constexpr float Quantum = DAY_QUANTUM;
		GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Orange,
			FString::Printf(TEXT("Time of Day: %f, State: %s"),
				TimeOfDay/ Quantum, *CurrentStateString));
	}
	else
	{
		//debug pog
		UE_LOG(LogTemp, Warning, TEXT("Time of Day: %f"), TimeOfDay);
	}

	//check if the day is over
	if(TimeOfDay >= DAY_LENGTH)
	{
		TimeOfDay = 0;
		Days++;
	}
}

float UZenithStateMachine::GetTimeOfDay() const
{
	return TimeOfDay;
}

ETimeStateType UZenithStateMachine::GetCurrentState() const
{
	return CurrentState;
}

void UZenithStateMachine::Initialization(const TScriptInterface<IGameStateHandle>& Handle)
{
	if(Handle && Handle.GetInterface())
	{
		GameStateHandle.Add(Handle.GetInterface());
		Days = 0;
		TimeOfDay = Ts_Dawn;
		GameStateHandle[0]->DawnEvent();
		CurrentState = ETimeStateType::Dawn;
		DayLengthInSeconds = DAY_LENGTH;
	}
	//Game error
	else
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Game Error Game State does not exit"));
		}
		else
		{
			//debug pog
			UE_LOG(LogTemp, Error, TEXT("Game Error Game State does not exit"));
		}
	}
}

