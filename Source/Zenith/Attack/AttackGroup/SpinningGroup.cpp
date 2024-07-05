// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinningGroup.h"


// Sets default values
ASpinningGroup::ASpinningGroup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpinningGroup::BeginPlay()
{
	Super::BeginPlay();
}


void ASpinningGroup::UpdateMotion(float DeltaTime)
{
	
	const float RotationSpeed = 10.f;
	const float MovementInterpSpeed = 10.f;
	const float AttackMovementSpeed = 1.f;
	
	// Rotate around the center smoothly
	FRotator CurrentRotation = RootComponent->GetRelativeRotation();
	FRotator TargetRotation = FRotator(0.f, MovementSpeed * DeltaTime, 0.f);
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, CurrentRotation + TargetRotation, DeltaTime, RotationSpeed);
	RootComponent->SetRelativeRotation(NewRotation, false, nullptr, ETeleportType::None);

	// Ensure the root component is smoothly interpolated to the actor's location
	FVector CurrentLocation = RootComponent->GetComponentLocation();
	if(!GetOwner()) return;
	FVector TargetLocation = GetOwner()->GetActorLocation();
	FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, MovementInterpSpeed);
	RootComponent->SetWorldLocation(NewLocation, false, nullptr, ETeleportType::None);

	// Move and rotate the attacks in a circular motion smoothly
	int i = 0;
	for(AActor * Attack : Attacks)
	{
		//cast to attack handle
		// IAttackInstanceHandle* AttackHandle = Cast<IAttackInstanceHandle>(Attack);
		// if(!AttackHandle->IsAttackActive()) continue;
		// Calculate the angle and position for each attack
		const float Angle = 2 * PI * i / Attacks.Num() + NewRotation.Yaw * PI / 180.f;
		const float Distance = OffCenterDistance;
		//relative position
		FVector Position = FVector(Distance * FMath::Cos(Angle), Distance * FMath::Sin(Angle), 0.f);
		
		//Global position
		FVector SelfLocation = GetOwner()->GetActorLocation() + Position;

		// Interpolate the attack's position to move smoothly
		FVector CurrentAttackLocation = Attacks[i]->GetActorLocation();
		FVector InterpolatedLocation = FMath::VInterpTo(CurrentAttackLocation, SelfLocation, DeltaTime, AttackMovementSpeed);
		Attack->SetActorLocation(InterpolatedLocation, false, nullptr, ETeleportType::None);

		// Calculate and set the attack's rotation to face the movement direction
		FVector Direction = (InterpolatedLocation - CurrentAttackLocation).GetSafeNormal();
		FRotator FaceDirection = Direction.Rotation();
		Attack->SetActorRotation(FaceDirection);
		//relative rotation
		i++;
	}
}

