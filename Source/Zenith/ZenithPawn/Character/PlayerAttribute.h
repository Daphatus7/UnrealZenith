#pragma once

#include "CoreMinimal.h"
#include "PlayerAttribute.generated.h"

USTRUCT(BlueprintType)
struct ZENITH_API FPlayerAttribute 
{
	GENERATED_BODY()
	
	float Health = 100.f;
	float HealthMax = 100.f;
	int32 Experience = 0;
	int32 Level = 1;
};
