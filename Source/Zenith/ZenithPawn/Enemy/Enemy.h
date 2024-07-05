// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterAttribute.h"
#include "Zenith/ZenithPawn/Pawn/ZenithPawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy.generated.h"

UCLASS()
class ZENITH_API AEnemy : public AZenithPawn
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;\

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
	FName MonsterName = "No Name";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
	float Damage = 1.0f;
		
	//health
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = "true"))
	float Health = 5.f;

	//health Max
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = "true"))
	float HealthMax = 5.f;

	//Experience Points
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Experience, meta = (AllowPrivateAccess = "true"))
	int32 Experience = 1;
public:
	// Sets default values for this character's properties
	AEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//notification on begin overlap
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void OnTakingDamage(const float DamageAmount, AActor* DamageCauser) override;

	//Apply Damage
	virtual void ApplyDamage(AZenithPawn* Target, float DamageAmount);
	virtual void Notify() override;
	virtual void OnDeath_Implementation() override;
	//die

	virtual void InitializeEnemy(const FMonsterAttribute MonsterAttribute)
	{
		MonsterName = MonsterAttribute.Name;
		Damage = MonsterAttribute.Damage;
		Health = MonsterAttribute.Health;
		HealthMax = MonsterAttribute.Health;
		Experience = MonsterAttribute.Experience;
		//movement speed
		GetCharacterMovement()->MaxWalkSpeed = MonsterAttribute.MovementSpeed;
	}
};
