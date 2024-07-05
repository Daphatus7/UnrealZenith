// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Zenith/GameMode/ZenithGameMode.h"
#include "Zenith/GameMode/EnemyHandle/GameMonsterHandle.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add("Enemy");

	
	//set character movement speed max
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//if the target has the tag to be damage-> apply damage
	if(OtherActor->Tags.Contains("ZenithPlayer"))
	{
		AZenithPawn* ZenithPawn = Cast<AZenithPawn>(OtherActor);
		if (ZenithPawn == nullptr) return;
		
		ApplyDamage(ZenithPawn, Damage);
	}
}

void AEnemy::OnTakingDamage(const float DamageAmount, AActor* DamageCauser)
{
	OnTakeDamageEffect(DamageAmount);
	Notify();
	Health -= DamageAmount;
	if(Health <= 0)
	{
		//Add tag dead
		Tags.Add("Killed");
		//Notify GameMode
		if (IGameMonsterHandle* GameMode = Cast<IGameMonsterHandle>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->OnMonsterKilled(MonsterName);
		}
		//Disable collision
		OnDeath();
	}
}

void AEnemy::ApplyDamage(AZenithPawn* Target, float DamageAmount)
{
	Target->OnTakingDamage(DamageAmount, this);
}

void AEnemy::Notify()
{
	//notify listeners
	for (IListener* Listener : Listeners)
	{
		if(Listener)
			Listener->NotifyListener(&Health);
	}
}

void AEnemy::OnDeath_Implementation()
{
	Destroy();
}