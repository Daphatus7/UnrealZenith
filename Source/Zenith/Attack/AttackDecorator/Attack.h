// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Zenith/Attack/AttackGroup/AttackClusterHandle.h"
#include "Zenith/ZenithPawn/Pawn/ZenithPawn.h"
#include "NiagaraComponent.h"
#include "Attack.generated.h"

/** A Motionless Object that applies damage to target
 * 
 */
UCLASS()
class ZENITH_API AAttack : public AActor
{
	GENERATED_BODY()
	
	//scene component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;
	
	//The cluster the attack belongs to 
	IAttackClusterHandle * ParentCluster;
	bool bIsActiveActive = true;


protected:

	//----------------------------------------Modifiable Properties --------------------------------------
	//Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent * CollisionMesh;
	
	//damage - flat damage
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
	float Damage = 1.0f;
	//Speed can be either spin or linear
	
	//Piercing - if Piercing, then it will go through the target
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
	bool bPiercing = false;
	//Damage Radius
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
	float DamageArea = 1.f;
	//FX
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent * FX;	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ApplyDamage(AZenithPawn* Target, float DamageAmount);
	//on hit
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	//Administration

public:
	// Sets default values for this actor's properties
	AAttack();
	
	//Administration ------------------------------
	//Activate
	virtual void Activate();
	//Deactivate
	virtual void Deactivate();
	//Check if active
	virtual bool IsAttackActive() 
	{
		return bIsActiveActive;
	}

	UFUNCTION(BlueprintNativeEvent, Category = "Attack")
	void OnHitEffect();


	
	void InitializeParent(IAttackClusterHandle* NewParentCluster)
	{
		ParentCluster = NewParentCluster;
	}
	
	//Attack property
	virtual void InitializeProperty(const float InitDamage, const bool bPierce, const float InitDamageArea, TSoftObjectPtr<UNiagaraSystem> NewFX);
	virtual void UpdateAttack(const float InitDamage, const bool bPierce, const float InitDamageArea);
	void DebugAttackMessage() const;
};
