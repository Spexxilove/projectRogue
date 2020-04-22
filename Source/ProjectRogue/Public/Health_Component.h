// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health_Component.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTROGUE_API UHealth_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealth_Component();

	/** Broadcasts whenthe Unit reaches zero health */
	FDeathEvent& OnChanged() { return DeathEvent; }

	void TakeDamage(float Amount);

	void Heal(float Amount);

	bool IsHealable();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	/* The max health value */
	UPROPERTY(Category = Gameplay, VisibleAnyWhere, BlueprintReadOnly)
	class UUnitModifiableStatComponent* MaxHealth;

private:
	float CurrentHealth = 1;

	/** Broadcasts whenthe Unit reaches zero health */
	UPROPERTY(BlueprintAssignable)
	FDeathEvent DeathEvent;

	void HandleOnMaxHealthChanged(float OldValue, float NewValue);
		
};
