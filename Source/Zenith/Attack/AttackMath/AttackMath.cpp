#include "AttackMath.h"

int32 FAttackMath::ApplyAttackLevel(const int32 AttackLevel, const int32 Amount)
{
    return AttackLevel + Amount;
}

float FAttackMath::ApplyFlatDamage(const float Damage, const float Amount)
{
    return Damage + Amount;
}

float FAttackMath::ApplyDamageIncreasePercentage(const float Damage, const float Amount)
{
    return Damage * Amount;
}

int32 FAttackMath::ApplyNumberOfProjectiles(const int32 NumberOfProjectiles, const int32 Amount)
{
    return NumberOfProjectiles + Amount;
}

float FAttackMath::ApplyDamageArea(const float DamageArea, const float Amount)
{
    return DamageArea + Amount;
}

float FAttackMath::ApplyMovementSpeed(const float MovementSpeed, const float Amount)
{
    return MovementSpeed + Amount;
}

int32 FAttackMath::ApplyNumberOfClusters(const int32 NumberOfClusters, const int32 Amount)
{
    return NumberOfClusters + Amount;
}

float FAttackMath::ApplyAttackSpeed(const float AttackSpeed, const float Amount)
{
    return AttackSpeed + Amount;
}

int32 FAttackMath::ApplyPierceCount(const int32 PierceCount, const int32 Amount)
{
    return PierceCount + Amount;
}

float FAttackMath::ApplyOffCenterDistance(const float OffCenterDistance, const float Amount)
{
    return OffCenterDistance + Amount;
}

int32 FAttackMath::ApplyClusterSize(const int32 ClusterSize, const int32 Amount)
{
    return ClusterSize + Amount;
}

float FAttackMath::ApplyEffectEnhanced(const float EffectEnhanced, const float Amount)
{
    return EffectEnhanced + Amount;
}

float FAttackMath::ApplyCriticalStrikeChance(const float CriticalStrikeChance, const float Amount)
{
    return CriticalStrikeChance + Amount;
}

FAttackData FAttackMath::GetNewAttackData(const FAttackData& AttackData, TArray<FModifier*> AttackModifiers)
{
    FAttackData NewAttackData = AttackData;
    for (FModifier* Modifier : AttackModifiers)
    {
        switch (Modifier->ModifierName)
        {
        case EAttackModifier::Flat_Damage:
            NewAttackData.Damage = ApplyFlatDamage(AttackData.Damage, Modifier->Amount);
            break;

        case EAttackModifier::Damage_Increase_Percentage:
            NewAttackData.Damage = ApplyDamageIncreasePercentage(NewAttackData.Damage, Modifier->Amount);
            break;

        case EAttackModifier::Number_Of_Projectiles:
            NewAttackData.NumberOfProjectiles = ApplyNumberOfProjectiles(NewAttackData.NumberOfProjectiles, Modifier->Amount);
            break;

        case EAttackModifier::Damage_Area:
            NewAttackData.DamageArea = ApplyDamageArea(NewAttackData.DamageArea, Modifier->Amount);
            break;

        case EAttackModifier::Movement_Speed:
            NewAttackData.MovementSpeed = ApplyMovementSpeed(NewAttackData.MovementSpeed, Modifier->Amount);
            break;

        case EAttackModifier::Number_Of_Clusters:
            NewAttackData.NumberOfCluster = ApplyNumberOfClusters(NewAttackData.NumberOfCluster, Modifier->Amount);
            break;

        case EAttackModifier::Attack_Speed:
            NewAttackData.AttackSpeed = ApplyAttackSpeed(NewAttackData.AttackSpeed, Modifier->Amount);
            break;

        case EAttackModifier::Pierce_Count:
            NewAttackData.PierceCount = ApplyPierceCount(NewAttackData.PierceCount, Modifier->Amount);
            break;

        case EAttackModifier::Off_Center_Distance:
            NewAttackData.OffCenterDistance = ApplyOffCenterDistance(NewAttackData.OffCenterDistance, Modifier->Amount);
            break;

        case EAttackModifier::Cluster_Size:
            NewAttackData.ClusterSize = ApplyClusterSize(NewAttackData.ClusterSize, Modifier->Amount);
            break;

        case EAttackModifier::Effect_Enhanced:
            NewAttackData.EffectEnhanced = ApplyEffectEnhanced(NewAttackData.EffectEnhanced, Modifier->Amount);
            break;

        case EAttackModifier::Critical_Strike_Chance:
            NewAttackData.CriticalStrikeChance = ApplyCriticalStrikeChance(NewAttackData.CriticalStrikeChance, Modifier->Amount);
            break;

        default:
            // Handle unknown modifiers
                break;
        }
    }
    return NewAttackData;
    
}
