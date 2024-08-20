// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackProperty.h"
#include "AttackPropertyHandle.h"
#include "Zenith/Attack/AttackComposite/AttackModifier.h"
#include "Zenith/Attack/AttackAttribute/AttackAttribute.h"
#include "Zenith/Attack/AttackGroup/AttackGroup.h"
#include "AttackComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Attack), meta=(BlueprintSpawnableComponent))
class ZENITH_API UAttackComponent : public UActorComponent, public IAttackPropertyHandle
{


private:
	GENERATED_BODY()

	/*---------------------------------Attack Base Property-------------------------------------*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	int TotalLevels = 30;
	//Attack Property
	UPROPERTY()
	FAttackProperty AttackProperty;
	UPROPERTY()
	FAttackProperty AttackPropertyDefault;
	
	//Attack Clusters
	UPROPERTY()
	AAttackGroup * AttackCluster = nullptr;
	
	/*---------------------------------Attack Modification--------------------------------------*/
	//Attack Modifiers
	TArray<FModifier *> AttackModifiers;
	//Damage
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
protected:
	/*------------------------------------Attack Level Table-----------------------------------------*/
#pragma region Attack Level Table
	//Attack Level Table
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	UCurveTable * AttackLevelTable;

	//Curve table data
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack")
	TArray<float> AttackLevelData;
	
	//Attack Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	int32 AttackLevel = 1;
	//Get Attack Level Data
	UFUNCTION(BlueprintCallable, Category = "Attack")
	float GetAttackLevelExperience(int32 Level);
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void LoadAttackLevelData();
#pragma endregion
	/*------------------------------------Attack Speed Table-----------------------------------------*/
	//Attack Speed Table
#pragma region Attack Speed Table
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	UCurveTable * AttackSpeedTable;
	//Curve table data
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack")
	TArray<float> AttackSpeedData; 
	UFUNCTION(BlueprintCallable, Category = "Attack")
	float GetAttackSpeedCurveValue(int32 Level);
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void LoadAttackSpeedTable();
#pragma endregion
public:
	/*------------------------------------Cluster Handle-----------------------------------------*/
	//Cluster
	virtual void UpdateCluster();
	//Initialize Cluster
	virtual void InitializeCluster();
	/*------------------------------------Attack Modifiers------------------------------------*/
	//Attack Modifiers
	virtual void AddAttackModifier(FModifier * Modifier);
	//Remove Attack Modifier
	virtual void RemoveAttackModifier(FModifier * Modifier);

	//Apply Changes to the attack property
	virtual void ApplyModifer();
	virtual void ReinitializeAttackProperty();



public:
	/*------------------------------Attack Component Handle------------------------------------*/
private:
	UPROPERTY()
	TMap<EAttackModifierType, UAttackAttribute *> AttackAttributes;
public:
	/**
	 * Add new Attack Attribute
	 */
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AddAttackAttribute(UAttackAttribute * AttackAttribute);
	/**
	 * 
	 * @param Amount Current Amount + New Amount
	 */
#pragma region Attack Property Handle
	virtual void ApplyFlatDamage(float Amount) override;
	/**
	 * 
	 * @param Amount Default Amount * (1 + Amount)
	 */
	virtual void ApplyDamageIncreasePercentage(float Amount) override;
	/**
	 * 
	 * @param Amount 
	 */
	virtual void ApplyNumberOfProjectiles(const int32 Amount) override;
	/**
	 * 
	 * @param Amount 
	 */
	virtual void ApplyDamageArea(const float Amount) override;
	/**
	 * 
	 * @param Amount 
	 */
	virtual void ApplyMovementSpeed(const float Amount) override;
	/**
	 * 
	 * @param Amount 
	 */
	virtual void ApplyNumberOfClusters(const int32 Amount) override;
	/**
	 * 
	 * @param Amount 
	 */
	virtual void ApplyAttackSpeed(const float Amount) override;
	/**
	 * 
	 * @param Amount 
	 */
	virtual void ApplyPierceCount(const int32 Amount) override;
	/**
	 * 
	 * @param Amount 
	 */
	virtual void ApplyOffCenterDistance(const float Amount) override;
	/**
	 * 
	 * @param Amount 
	 */
	virtual void ApplyClusterSize(const int32 Amount) override;
	/**
	 * 
	 * @param Amount 
	 */
	virtual void ApplyEffectEnhanced(const float Amount) override;
	/**
	 * 
	 * @param Amount 
	 */
	virtual void ApplyCriticalStrikeChance(const float Amount) override;
#pragma endregion 
};


