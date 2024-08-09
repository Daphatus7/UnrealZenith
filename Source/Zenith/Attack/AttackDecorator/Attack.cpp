// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Zenith/Attack/AttackData.h"
#include "Zenith/ZenithPawn/Enemy/Enemy.h"

#include "Zenith/ZenithPawn/Pawn/ZenithPawn.h"

AAttack::AAttack()
{
		
	// Initialize SceneComponent as the root component
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	// Initialize Mesh component and set collision and mesh properties
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	CollisionMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	//hide
	CollisionMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Sphere.Sphere")).Object);
	CollisionMesh->SetupAttachment(RootComponent); // Attach Mesh to SceneComponent
}

void AAttack::InitializeProperty(FAttackData AttackData)
{
	Damage = AttackData.Damage;
	DamageArea = AttackData.DamageArea;

	CollisionMesh->SetRelativeScale3D(FVector(AttackData.DamageArea));
	CollisionMesh->SetVisibility(false);
}

void AAttack::UpdateAttack(const float InitDamage, const bool bPierce, const float InitDamageArea)
{
	Damage = InitDamage;
	bPiercing = bPierce;
	DamageArea = InitDamageArea;
	CollisionMesh->SetRelativeScale3D(FVector(InitDamageArea));
}

void AAttack::DebugAttackMessage() const
{
	if(GEngine)
	{
		// GEngine->AddOnScreenDebugMessage(-1, GetWorld()->DeltaTimeSeconds,
		// 	FColor::Purple, "Attack Number " + GetName() + " Damage = " +
		// 	FString::SanitizeFloat(Damage) + " Piercing = " +
		// 	FString::FromInt(bPiercing) + " Damage Area = " +
		// 	FString::SanitizeFloat(DamageArea));
	}
}

void AAttack::BeginPlay()
{
	Super::BeginPlay();
}

void AAttack::ApplyDamage(AZenithPawn* Target, float DamageAmount)
{
	Target->OnTakingDamage(DamageAmount, this);
}

//overlap - apply damage
void AAttack::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//check valid target
	if(OtherActor->Tags.Contains("Killed")) return;
	if(OtherActor->Tags.Contains("Enemy") )
	{
		AEnemy* ZenithPawn = Cast<AEnemy>(OtherActor);
		if (ZenithPawn == nullptr) return;
		ApplyDamage(ZenithPawn, Damage);
		OnHitEffect();

		if(bPiercing) return;
		//If not piercing, destroy the attack
		// to avoid crashes
		Deactivate();
	}
}



void AAttack::Activate()
{
	if(!bIsActiveActive)
	{
		bIsActiveActive = true;
		// Hides visible components
		SetActorHiddenInGame(false);

		// Disables collision components
		SetActorEnableCollision(true);

		// Stops the Actor from ticking
		SetActorTickEnabled(true);
	}

}

void AAttack::Deactivate()
{
	if(bIsActiveActive)
	{
		bIsActiveActive = false;

		// Hides visible components
		SetActorHiddenInGame(true);

		// Disables collision components
		SetActorEnableCollision(false);

		// Stops the Actor from ticking
		SetActorTickEnabled(false);
	}

}

void AAttack::OnHitEffect_Implementation()
{
}
