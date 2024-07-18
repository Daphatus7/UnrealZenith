// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerAttribute.h"
#include "PlayerAttributeHandle.h"
#include "GameFramework/Character.h"
#include "Zenith/Attack/AttackComponent.h"
#include "PlayerAttribute.h"
#include "Logging/LogMacros.h"
#include "Zenith/GameMode/GameModeUIHandle/PlayerUIHandle.h"
#include "ZenithCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AZenithCharacter : public AZenithPawn, public IPlayerAttributeHandle
{
public:
	virtual void AddAttackModifier(FAttackModifier * Modifier) override
	{
		AttackComponent->AddAttackModifier(Modifier);
	}
	virtual void RemoveAttackModifier(FAttackModifier * Modifier) override
	{
		AttackComponent->RemoveAttackModifier(Modifier);
	}

private:
	GENERATED_BODY()

	//Attack component
	UPROPERTY()
	UAttackComponent * AttackComponent;
	
	/*-----------------Character Attributes-----------------*/
	//health - in parent class
public:
	AZenithCharacter();
protected:
	/** mouse input **/
	virtual void Mouse(const FInputActionValue& Value);
	
	// To add mapping context
	virtual void BeginPlay() override;

	//Player Ui Handle reference
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameMode")
	TScriptInterface<IPlayerUIHandle> PlayerUIHandle;
	//attack speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	float AttackSpeed = 1.0f;

	//Character Attribute
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attribute, meta = (AllowPrivateAccess = "true"))
	FPlayerAttribute PlayerAttribute;
	
	//tick
	virtual void Tick(float DeltaTime) override;

	
public:
	/*-----------------Character Attributes-----------------*/
	//Take Damage
	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual bool Attack(FVector CursorLocation);
	//IEnhance
	virtual void IncreaseHealth(float HealthAmount) override;
	virtual void IncreaseDamage(float DamageAmount) override;
	virtual void IncreaseSpeed(float SpeedAmount) override;
	
	//on take damage effect
	virtual void OnTakeDamageEffect(float DamageAmount) override;

	//Load Skill
	virtual void LoadSkill(FAttackProperty * AttackProperty);

	/*-----------------Taking Damage-----------------*/
	//On taking damage
	virtual void OnTakingDamage(const float DamageAmount, AActor* DamageCauser) override;
	virtual void Notify() override;

	//Pure
	UFUNCTION(BlueprintPure, Category = "Attribute")
	float GetHealth() const { return PlayerAttribute.Health; }
	UFUNCTION(BlueprintPure, Category = "Attribute")
	float GetHealthMax() const { return PlayerAttribute.HealthMax; }


private:
	/*-----------------Character Attributes-----------------*/
	//player Magic Power Stats
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	float MagicPowerPoint = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	float ManaPowerPoints = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	float SpeedPowerPoints = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	float PhysiquePowerPoints = 0;

public:
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void AddMagicPowerPoint(float Amount);
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void AddManaPowerPoints(float Amount);
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void AddSpeedPowerPoints(float Amount);
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void AddPhysiquePowerPoints(float Amount);
	
};

