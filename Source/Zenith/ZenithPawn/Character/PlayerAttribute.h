#pragma once

#include "CoreMinimal.h"
#include "PlayerAttribute.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct ZENITH_API FPlayerAttribute 
{
	GENERATED_BODY()
	
	float Health = 10.f;
	float HealthMax = 10.f;
	int32 Experience = 0;
	int32 Level = 1;
	
	float MagicPowerPoint = 0.f;
	float ManaPowerPoint = 0.f;
	float SpeedPowerPoint = 0.f;
	float PhysiquePowerPoint = 0.f;
};
