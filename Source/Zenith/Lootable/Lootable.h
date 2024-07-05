// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "LootableProperty/LootEffect.h"

#include "Zenith/ZenithPawn/Character/ZenithCharacter.h"
#include "Lootable.generated.h"

UCLASS(Abstract)
class ZENITH_API ALootable : public AActor
{
	GENERATED_BODY()
	//Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent * Mesh;

	//Loot Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lootable Property", meta = (AllowPrivateAccess = "true"))
	FName LootName = "Loot";
	
	//sphere collision
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComponent;

	//LootProperty
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lootable Property", meta = (AllowPrivateAccess = "true"))
	TArray<FLootEffect> LootEffects;

public:
	// Sets default values for this actor's properties
	ALootable();
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void ApplyEffect(IPlayerAttributeHandle * PlayerHandle);
	//begin overlap
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintCallable, Category = "Lootable Property")
	virtual void InitializeLoot(const FName Name, const TArray<FLootEffect>& Effects, UStaticMesh * NewMesh);
};
