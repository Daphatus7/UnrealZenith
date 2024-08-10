#pragma once

#include "Zenith/Attack/AttackData.h"
#include "Zenith/Attack/AttackComposite/Modifier.h"

class FAttackMath
{
private:
	static int32 ApplyAttackLevel(const int32 AttackLevel, const int32 Amount);
	static float ApplyFlatDamage(const float Damage, const float Amount);
	static float ApplyDamageIncreasePercentage(const float Damage, const float Amount);
	static int32 ApplyNumberOfProjectiles(const int32 NumberOfProjectiles, const int32 Amount);
	static float ApplyDamageArea(const float DamageArea, const float Amount);
	static float ApplyMovementSpeed(const float MovementSpeed, const float Amount);
	static int32 ApplyNumberOfClusters(const int32 NumberOfClusters, const int32 Amount);
	static float ApplyAttackSpeed(const float AttackSpeed, const float Amount);
	static int32 ApplyPierceCount(const int32 PierceCount, const int32 Amount);
	static float ApplyOffCenterDistance(const float OffCenterDistance, const float Amount);
	static int32 ApplyClusterSize(const int32 ClusterSize, const int32 Amount);
	static float ApplyEffectEnhanced(const float EffectEnhanced, const float Amount);
	static float ApplyCriticalStrikeChance(const float CriticalStrikeChance, const float Amount);

public:
	static FAttackData GetNewAttackData(const FAttackData& AttackData, TArray<FModifier*> AttackModifiers);
};
