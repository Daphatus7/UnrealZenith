#pragma once

#include "CoreMinimal.h"
#include "AttackData.h"
#include "Zenith/Attack/AttackGroup/AttackGroup.h"
#include "GameFramework/Actor.h"
#include "Zenith/Attack/AttackDecorator/Attack.h"
#include "AttackProperty.generated.h"

USTRUCT(BlueprintType)
struct ZENITH_API FAttackProperty : public FTableRowBase
{
	GENERATED_BODY()
	//Attack Name
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	FName AttackName = "Attack";

	//Class To Spawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Base")
	TSubclassOf<AAttack> ClassToSpawn = nullptr;

	//Class To Spawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Base")
	TSubclassOf<AAttackGroup> ClusterToSpawn = nullptr;

	//FAttackData
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	FAttackData AttackData;
};
