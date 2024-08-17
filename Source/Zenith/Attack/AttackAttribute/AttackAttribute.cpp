// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAttribute.h"

void UAttackAttribute::LoadAttackLevelData()
{
	if(AttackLevelTable)
	{
		UZenithFunctionLibrary::LoadCurveTableData(AttackLevelTable,"Curve", AttackLevelData, TotalLevels);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Attack Level Table is not set"));	
	}
	
}

void UAttackAttribute::LevelUpDataModify()
{
	if(AttackDataHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Attack Data Handle is not set"));
		return;
	}
	switch (AttackAttributeType)
	{
		case EAttackModifierType::Flat_Damage:
			AttackDataHandle->ApplyFlatDamage(GetValue());
			break;
		case EAttackModifierType::Damage_Increase_Percentage:
			AttackDataHandle->ApplyDamageIncreasePercentage(GetValue());
			break;
		case EAttackModifierType::Number_Of_Projectiles:
			AttackDataHandle->ApplyNumberOfProjectiles(GetValue());
			break;
		case EAttackModifierType::Damage_Area:
			AttackDataHandle->ApplyDamageArea(GetValue());
			break;
		case EAttackModifierType::Movement_Speed:
			AttackDataHandle->ApplyMovementSpeed(GetValue());
			break;
		case EAttackModifierType::Number_Of_Clusters:
			AttackDataHandle->ApplyNumberOfClusters(GetValue());
			break;
		case EAttackModifierType::Attack_Speed:
			AttackDataHandle->ApplyAttackSpeed(GetValue());
			break;
		case EAttackModifierType::Pierce_Count:
			AttackDataHandle->ApplyPierceCount(GetValue());
			break;
		case EAttackModifierType::Off_Center_Distance:
			AttackDataHandle->ApplyOffCenterDistance(GetValue());
			break;
		case EAttackModifierType::Cluster_Size:
			AttackDataHandle->ApplyClusterSize(GetValue());
			break;
		case EAttackModifierType::Effect_Enhanced:
			AttackDataHandle->ApplyEffectEnhanced(GetValue());
			break;
		case EAttackModifierType::Critical_Strike_Chance:
			AttackDataHandle->ApplyCriticalStrikeChance(GetValue());
			break;
		case EAttackModifierType::None:
			UE_LOG(LogTemp, Warning, TEXT("This Attack Attribute has no effect"));
			break;
	}
}

bool UAttackAttribute::LevelUp()
{
	if(Level >= TotalLevels)
	{
		Level = TotalLevels;
		return false;
	} else
	{
		Level++;
		LevelUpDataModify();
		LevelUpVisualEffect();
		return true;
	}
}

float UAttackAttribute::GetValue()
{
	if(Level > TotalLevels)
	{
		Level = TotalLevels;
	}
	return AttackLevelData[Level];
}
