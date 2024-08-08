// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackProperty.h"
#include "Zenith/Attack/AttackComposite/AttackModifier.h"
#include "Zenith/Attack/AttackGroup/AttackGroup.h"
#include "AttackComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Attack), meta=(BlueprintSpawnableComponent))
class ZENITH_API UAttackComponent : public UActorComponent
{
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
	TArray<FAttackModifier *> AttackModifiers;
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
	virtual void AddAttackModifier(FAttackModifier * Modifier);
	//Remove Attack Modifier
	virtual void RemoveAttackModifier(FAttackModifier * Modifier);

	virtual void ApplyModifer();
	virtual void ReinitializeAttackProperty();
	
};


