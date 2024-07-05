// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum class EEffectType : uint8
{
	IncreaseAttack UMETA(DisplayName = "IncreaseAttack"),
	IncreaseSpeed UMETA(DisplayName = "IncreaseSpeed"),
	IncreaseHealth UMETA(DisplayName = "IncreaseHealth"),
	IncreaseAttackMovementSpeed UMETA(DisplayName = "IncreaseAttackMovementSpeed"),
};
