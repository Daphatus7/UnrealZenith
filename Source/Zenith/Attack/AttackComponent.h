// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackHandle.h"
#include "Components/ActorComponent.h"
#include "AttackProperty.h"
#include "Zenith/Attack/AttackComposite/AttackModifier.h"
#include "Zenith/Attack/AttackGroup/AttackGroup.h"
#include "AttackComponent.generated.h"


UCLASS()
class ZENITH_API UAttackComponent : public UActorComponent, public IAttackHandle
{
	GENERATED_BODY()

	/*---------------------------------Attack Base Property-------------------------------------*/
	//Attack Property
	UPROPERTY()
	FAttackProperty AttackProperty;
	UPROPERTY()
	FAttackProperty AttackPropertyDefault;
	
	//Attack Clusters
	UPROPERTY(EditAnywhere, Category = "Attack")
	AAttackGroup * AttackCluster = nullptr;

	/*---------------------------------Attack Modification--------------------------------------*/
	//Attack Modifiers
	TArray<FAttackModifier*> AttackModifiers;
	
	
	//determine numerical value
	UPROPERTY(EditAnywhere, Category = "Attack")
	float Damage = 1.0f;

public:
	//Constructor
	UAttackComponent();
	//Tick
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/*------------------------------------Player input------------------------------------------*/
	//Attack
	UFUNCTION(BlueprintCallable, Category = "Attack")
	bool Attack(const FVector& Direction);

	//Assign Attack Type
	void AssignAttackType(FAttackProperty AttackType);
	/*------------------------------------Attack Base--------------------------------------------*/
	
	/*------------------------------------Cluster Handle-----------------------------------------*/
	//Cluster
	virtual void UpdateCluster();
	//Initialize Cluster
	virtual void InitializeCluster();
	
	/*------------------------------------Attack Modification Handle--------------------------*/
	//Attack Handle
	virtual void IncreaseDamage(float FlatDamage) override;
	//increase damage percentage
	// base damage * (1 + Percentage/100)
	virtual void IncreaseDamagePercentage(float Percentage) override;
	//increase attack speed
	virtual void IncreaseAttackSpeed(float Percentage) override;
	//Add Number of Projectiles per attack
	virtual void IncreaseNumberOfProjectiles(int32 NumberOfProjectiles) override;
	//Increase Damage Area
	virtual void IncreaseDamageArea(float DamageArea) override;
	//Increase Movement Speed
	virtual void IncreaseMovementSpeed(float MovementSpeed) override;
	//IncreaseClusterSize
	virtual void IncreaseClusterSize(int32 ClusterSize) override;

	/*------------------------------------Attack Modifiers------------------------------------*/
	//Attack Modifiers
	virtual void AddAttackModifier(FAttackModifier * Modifier);
	//Remove Attack Modifier
	virtual void RemoveAttackModifier(FAttackModifier * Modifier);

	virtual void ApplyModifer();
	virtual void RemoveModifier(FAttackModifier * ModifierToAdd);
	virtual void RemoveModifierEffect(FAttackModifier * ModifierToRemove);
	virtual void ReinitializeAttackProperty();
};


