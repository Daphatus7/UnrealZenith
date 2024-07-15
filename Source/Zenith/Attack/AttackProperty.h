#pragma once

#include "CoreMinimal.h"
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
	//Cluster Property Name
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	FName ClusterPropertyName = "SpinningCluster";
	//Class To Spawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Base")
	TSubclassOf<AAttack> ClassToSpawn = nullptr;

	//Class To Spawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Base")
	TSubclassOf<AAttackGroup> ClusterToSpawn = nullptr;
	//FX
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	TSoftObjectPtr<UNiagaraSystem> FX = nullptr;
	
	//float value of damage
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float Damage = 5.f;

	//number of projectiles
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	int32 NumberOfProjectiles = 1;

	//Damage Radius
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float DamageArea = 1.f;

	//Movement Speed
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float MovementSpeed = 300.f;
	
	//Number of Cluster
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	int32 NumberOfCluster = 1;
	
	//Attack Speed per second
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float AttackSpeed = 3.0f;
	
	//does attack pierce
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	bool bPiercing = false; //does attack pierce

	
	//Off-center Distance
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float OffCenterDistance = 300.f;

	//ClusterSize
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	int32 ClusterSize = 3;
};
