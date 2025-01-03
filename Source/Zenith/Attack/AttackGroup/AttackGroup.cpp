// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackGroup.h"

#include "Zenith/Library/ZenithFunctionLibrary.h"

void AAttackGroup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMotion(DeltaTime);
}

AAttackGroup::AAttackGroup()
{
	//enable tick
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	// Initialize Mesh component and set collision and mesh properties
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cube.Cube")).Object);
	Mesh->SetupAttachment(RootComponent); // Attach Mesh to SceneComponent
	Mesh->SetVisibility(false);
}

void AAttackGroup::BeginPlay()
{
	Super::BeginPlay();
}

void AAttackGroup::InitializeCluster(const float InitMovementSpeed,
									   const float InitOffCenterDistance, const int32 InitClusterSize)
{
	MovementSpeed = InitMovementSpeed;
	OffCenterDistance = InitOffCenterDistance;
	ClusterSize = InitClusterSize;
}

void AAttackGroup::UpdateMotion_Implementation(float DeltaTime)
{
	
}

void AAttackGroup::InitializeAttack_Implementation(AActor* Attack)
{
}

void AAttackGroup::DebugClusterMessage()
{
	if(GEngine)
	{
		//printout Cluster information, name, offcenter distance etc.
		UZenithFunctionLibrary::DxPrint("--------------------------------------", true);
		GEngine->AddOnScreenDebugMessage(-1, GetWorld()->DeltaTimeSeconds,
			FColor::Purple, "Cluster Name: " + GetName() + " Movement Speed = " +
			FString::SanitizeFloat(MovementSpeed) + " Off Center Distance = " +
			FString::SanitizeFloat(OffCenterDistance) + " Cluster Size = " +
			FString::FromInt(ClusterSize));
	}
	
	for(const AAttack * Attack: Attacks)
	{
		Attack->DebugAttackMessage();
	}
}