#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "AttackData.generated.h"

USTRUCT(BlueprintType)
struct FAttackData
{
	GENERATED_BODY()

	// Cluster Property Name
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	FName ClusterPropertyName = "SpinningCluster";

	// Damage value
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float Damage = 5.f;

	// Number of projectiles
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	int32 NumberOfProjectiles = 1;

	// Damage Radius
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float DamageArea = 1.f;

	// Movement Speed
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float MovementSpeed = 300.f;

	// Number of Clusters
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	int32 NumberOfCluster = 1;

	// Attack Speed per second
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float AttackSpeed = 3.0f;

	// Pierce Count
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	int32 PierceCount = 0;

	// Off-center Distance
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float OffCenterDistance = 300.f;

	// Cluster Size
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	int32 ClusterSize = 3;

	// Effect Enhanced percentage
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float EffectEnhanced = 1.f;

	// Critical Strike Chance
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float CriticalStrikeChance = 0.f;
};
