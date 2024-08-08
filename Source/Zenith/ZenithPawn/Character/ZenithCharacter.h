// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerAttribute.h"
#include "PlayerAttributeHandle.h"
#include "Zenith/Attack/AttackComponent.h"
#include "Logging/LogMacros.h"
#include "Zenith/GameMode/GameModeUIHandle/PlayerUIHandle.h"
#include "Zenith/ZenithPawn/Pawn/ZenithPawn.h"
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

private:
	GENERATED_BODY()

	//Attack component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
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
	/**
	 * Blueprint only event, finished initializing attack, attack automatically	
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
	void OnStartAttack();

	/**
	 * stop attack
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
	void OnStopAttack();
	
	//IEnhance
	virtual void IncreaseHealth(float HealthAmount) override;
	virtual void IncreaseDamage(float DamageAmount) override;
	virtual void IncreaseSpeed(float SpeedAmount) override;
	
	//on take damage effect
	virtual void OnTakeDamageEffect(float DamageAmount) override;


	/*-----------------Taking Damage-----------------*/
	//On taking damage
	virtual void OnTakingDamage(const float DamageAmount, AActor* DamageCauser) override;
	virtual void Notify() override;

	/*----------------------------------Attributes----------------------------------*/
#pragma region Attributes
public:
	UFUNCTION(BlueprintPure, Category = "Attribute")
	float GetHealth() const { return PlayerAttribute.Health; }
	UFUNCTION(BlueprintPure, Category = "Attribute")
	float GetHealthMax() const { return PlayerAttribute.HealthMax; }

	/*----------------------------------Plant magic---------------------------------*/
	UFUNCTION(BlueprintCallable, Category = "Plant")
	void AddMagicPowerPoint(float Amount);
	UFUNCTION(BlueprintCallable, Category = "Plant")
	void AddSpeedPowerPoint(float Amount);
	UFUNCTION(BlueprintCallable, Category = "Plant")
	void AddPhysiquePowerPoint(float Amount);
	UFUNCTION(BlueprintCallable, Category = "Plant")
	void AddManaPowerPoint(float Amount);
	// getters
	UFUNCTION(BlueprintPure, Category = "Plant")
	float GetMagicPowerPoint() const { return PlayerAttribute.MagicPowerPoint; }
	UFUNCTION(BlueprintPure, Category = "Plant")
	float GetSpeedPowerPoint() const { return PlayerAttribute.SpeedPowerPoint; }
	UFUNCTION(BlueprintPure, Category = "Plant")
	float GetPhysiquePowerPoint() const { return PlayerAttribute.PhysiquePowerPoint; }
	UFUNCTION(BlueprintPure, Category = "Plant")
	float GetManaPowerPoint() const { return PlayerAttribute.ManaPowerPoint; }
#pragma endregion
	
};


