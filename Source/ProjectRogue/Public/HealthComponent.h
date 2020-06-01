// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitModifiableStat.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDamageTakenEvent, float, DamageAmount, bool, IsDead);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTROGUE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	/** Broadcasts when the Unit reaches zero health after taking Damage event*/
	FDeathEvent& OnDeath() { return DeathEvent; }

	void TakeDamage(float Amount);

	/** Broadcasts when the Unit takes damage */
	FDamageTakenEvent& OnDamageTaken() { return DamageTakenEvent; }

	void Heal(float Amount);

	bool IsHealable() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//virtual void TickComponent(float deltaTime) override;


public:
	/* The max health value */
	UPROPERTY(Category = Gameplay, EditAnyWhere, BlueprintReadWrite)
	FUnitModifiableStat MaxHealth;

private:
	float CurrentHealth = 1;

	/** Broadcasts whenthe Unit reaches zero health */
	UPROPERTY(BlueprintAssignable)
	FDeathEvent DeathEvent;

	/** Broadcasts when the Unit takes damage */
	UPROPERTY(BlueprintAssignable)
	FDamageTakenEvent DamageTakenEvent;

	UFUNCTION()
	void HandleOnMaxHealthChanged(float OldValue, float NewValue);
		
};
