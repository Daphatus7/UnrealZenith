#pragma once

#include "CoreMinimal.h"
#include "PlayerLevel.generated.h"

USTRUCT(BlueprintType)
struct ZENITH_API FPlayerLevel : public FTableRowBase
{
	GENERATED_BODY()
	//Level
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level")
	int32 Level = 1;
	//Experience
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level")
	int32 Experience = 100;
};
