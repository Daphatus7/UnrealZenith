#pragma once

#include "Zenith/Attack/AttackData.h"
#include "Zenith/Attack/AttackComposite/Modifier.h"

class FAttackMath
{
private:
	static float ApplyFlatDamage(float Damage, float Amount);
	static float ApplyDamageIncreasePercentage(float Damage, float Amount);
	static int32 ApplyNumberOfProjectiles(int32 NumberOfProjectiles, float Amount);
	static float ApplyDamageArea(float DamageArea, float Amount);
	static float ApplyMovementSpeed(float MovementSpeed, float Amount);
	static int32 ApplyNumberOfClusters(int32 NumberOfClusters, float Amount);
	static float ApplyAttackSpeed(float AttackSpeed, float Amount);
	static int32 ApplyPierceCount(int32 PierceCount, float Amount);
	static float ApplyOffCenterDistance(float OffCenterDistance, float Amount);
	static int32 ApplyClusterSize(int32 ClusterSize, float Amount);
	static float ApplyEffectEnhanced(float EffectEnhanced, float Amount);
	static float ApplyCriticalStrikeChance(float CriticalStrikeChance, float Amount);
public:
	static FAttackData GetNewAttackData(const FAttackData& AttackData, TArray<FModifier*> AttackModifiers);
};
