// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

//day Length
#define REAL_WORLD_DAY_LENGTH 24
#define DAY_LENGTH 24
#define DAY_QUANTUM DAY_LENGTH/REAL_WORLD_DAY_LENGTH
enum ETimeState
{
	Ts_Dawn = 6 * DAY_QUANTUM,
	Ts_Morning = 9 * DAY_QUANTUM,
	Ts_Noon = 12 * DAY_QUANTUM,
	Ts_Dusk = 15 * DAY_QUANTUM,
	Ts_Night = 21 * DAY_QUANTUM,
	Ts_Midnight = 0 * DAY_QUANTUM
};

UENUM(BlueprintType)
enum class ETimeStateType : uint8
{
	Dawn UMETA(DisplayName = "Dawn"),
	Morning UMETA(DisplayName = "Morning"),
	Noon UMETA(DisplayName = "Noon"),
	Dusk UMETA(DisplayName = "Dusk"),
	Night UMETA(DisplayName = "Night"),
	Midnight UMETA(DisplayName = "Midnight"),
};
