// Fill out your copyright notice in the Description page of Project Settings.


#include "Lootable.h"

// Sets default values
ALootable::ALootable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//overlaps all
	Mesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	//set mesh /Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'
	RootComponent = Mesh;
	
	//collision
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(Mesh);
	SphereComponent->SetSphereRadius(100.f);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

// Called when the game starts or when spawned
void ALootable::BeginPlay()
{
	Super::BeginPlay();
}

void ALootable::ApplyEffect(IPlayerAttributeHandle * PlayerHandle)
{
	if(PlayerHandle)
	{
		for(const auto [EffectType, Amount] : LootEffects)
		{
			switch (EffectType)
			{	case EEffectType::IncreaseHealth:
					PlayerHandle->IncreaseHealth(Amount);
					break;
				case EEffectType::IncreaseAttack:
					PlayerHandle->IncreaseDamage(Amount);
					break;
				case EEffectType::IncreaseAttackMovementSpeed:
					PlayerHandle->IncreaseSpeed(Amount);
					break;
				default: ;
			}
		}
	}
}

void ALootable::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	//cast enhance
	if(IPlayerAttributeHandle* Enhance = Cast<IPlayerAttributeHandle>(OtherActor))
	{
		ApplyEffect(Enhance);
		Destroy();
	}
}

void ALootable::InitializeLoot(const FName Name, const TArray<FLootEffect>& Effects, UStaticMesh * NewMesh)
{
	LootName = Name;
	LootEffects = Effects;
	Mesh->SetStaticMesh(NewMesh);
}
