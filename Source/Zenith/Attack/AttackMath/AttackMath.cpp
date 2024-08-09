#include "AttackMath.h"

float FAttackMath::ApplyFlatDamage(float Damage, float Amount)
{
    return Damage + Amount;
}

float FAttackMath::ApplyDamageIncreasePercentage(float Damage, float Amount)
{
    return Damage * Amount;
}

int32 FAttackMath::ApplyNumberOfProjectiles(int32 NumberOfProjectiles, float Amount)
{
    return NumberOfProjectiles + Amount;
}

float FAttackMath::ApplyDamageArea(float DamageArea, float Amount)
{
    return DamageArea + Amount;
}

float FAttackMath::ApplyMovementSpeed(float MovementSpeed, float Amount)
{
    return MovementSpeed + Amount;
}

int32 FAttackMath::ApplyNumberOfClusters(int32 NumberOfClusters, float Amount)
{
    return NumberOfClusters + Amount;
}

float FAttackMath::ApplyAttackSpeed(float AttackSpeed, float Amount)
{
    return AttackSpeed + Amount;
}

int32 FAttackMath::ApplyPierceCount(int32 PierceCount, float Amount)
{
    return PierceCount + Amount;
}

float FAttackMath::ApplyOffCenterDistance(float OffCenterDistance, float Amount)
{
    return OffCenterDistance + Amount;
}

int32 FAttackMath::ApplyClusterSize(int32 ClusterSize, float Amount)
{
    return ClusterSize + Amount;
}

float FAttackMath::ApplyEffectEnhanced(float EffectEnhanced, float Amount)
{
    return EffectEnhanced + Amount;
}

float FAttackMath::ApplyCriticalStrikeChance(float CriticalStrikeChance, float Amount)
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
