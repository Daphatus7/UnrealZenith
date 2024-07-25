// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZenithCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Zenith/Attack/AttackComponent.h"
#include "Zenith/GameMode/GameModeUIHandle/PlayerUIHandle.h"


class AAttack;
DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////	
// ZenithCharacter


AZenithCharacter::AZenithCharacter()
{
#pragma region CharacterComponents
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	//set tag
	Tags.Add("ZenithPlayer");
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
#pragma endregion

#pragma region player health
	//health
#pragma endregion
}

void AZenithCharacter::Mouse(const FInputActionValue& Value)
{
}

void AZenithCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	// AttackComponent = NewObject<UAttackComponent>(this);
	// if (AttackComponent)
	// {
	// 	AttackComponent->RegisterComponent();
	// }
	if(GetWorld())
	{
		if (IPlayerUIHandle* Interface = Cast<IPlayerUIHandle>(GetWorld()->GetAuthGameMode()))
		{
			PlayerUIHandle.SetInterface(Interface);
			PlayerUIHandle.SetObject(GetWorld()->GetAuthGameMode());
			if(PlayerUIHandle)
				PlayerUIHandle->UpdateHealth();
		}
	}
}

void AZenithCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AZenithCharacter::Attack(FVector CursorLocation)
{
	FVector Direction = CursorLocation - GetActorLocation();
	if(AttackComponent)
	{
		//printout Attack Component
		return AttackComponent->Attack(Direction);
	}
	return false;
}

void AZenithCharacter::IncreaseHealth(float HealthAmount)
{
	PlayerAttribute.Health += HealthAmount;
	if(PlayerUIHandle)
	PlayerUIHandle->UpdateHealth();
}

void AZenithCharacter::IncreaseDamage(float DamageAmount)
{
	AttackComponent->IncreaseDamage(DamageAmount);
}

void AZenithCharacter::IncreaseSpeed(float SpeedAmount)
{
	AttackComponent->IncreaseMovementSpeed(SpeedAmount);
}

void AZenithCharacter::OnTakeDamageEffect(float DamageAmount)
{
	Super::OnTakeDamageEffect(DamageAmount);
	if(PlayerUIHandle)
	PlayerUIHandle->UpdateHealth();
}

UAttackComponent * AZenithCharacter::LoadSkill(FAttackProperty* AttackProperty)
{
	if (AttackProperty && AttackComponent)
	{
		AttackComponent->AssignAttackType(*AttackProperty);
		OnStartAttack();
		return AttackComponent;
	}
	UE_LOG(LogTemplateCharacter, Error, TEXT("Attack Property or AttackComponent is null"));
	return nullptr;
}


void AZenithCharacter::OnTakingDamage(const float DamageAmount, AActor* DamageCauser)
{
	Super::OnTakingDamage(DamageAmount, DamageCauser);
	PlayerAttribute.Health -= DamageAmount;
	if(PlayerAttribute.Health <= 0)
	{
		OnDeath();
	}
}

void AZenithCharacter::Notify()
{
	//notify listeners
	for (IListener* Listener : Listeners)
	{
		if(Listener)
			Listener->NotifyListener(&PlayerAttribute.Health);
	}
}

void AZenithCharacter::AddMagicPowerPoint(float Amount)
{
	PlayerAttribute.MagicPowerPoint += Amount;
	if(AttackComponent)
		AttackComponent->IncreaseMagicPower(PlayerAttribute.MagicPowerPoint);
}

void AZenithCharacter::AddSpeedPowerPoint(float Amount)
{
	PlayerAttribute.SpeedPowerPoint += Amount;
	if(AttackComponent)
		AttackComponent->IncreaseSpeedPower(PlayerAttribute.SpeedPowerPoint);
}

void AZenithCharacter::AddPhysiquePowerPoint(float Amount)
{
	PlayerAttribute.PhysiquePowerPoint += Amount;
	PlayerAttribute.Health += Amount;
	PlayerAttribute.HealthMax += Amount;
	if(PlayerUIHandle)
		PlayerUIHandle->UpdateHealth();
}

void AZenithCharacter::AddManaPowerPoint(float Amount)
{
	PlayerAttribute.MagicPowerPoint += Amount;
	if(AttackComponent)
		AttackComponent->IncreaseManaPower(PlayerAttribute.MagicPowerPoint);
}
