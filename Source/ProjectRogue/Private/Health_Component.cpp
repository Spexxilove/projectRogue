// Fill out your copyright notice in the Description page of Project Settings.


#include "Health_Component.h"
#include "UnitModifiableStat.h"

// Sets default values for this component's properties
UHealth_Component::UHealth_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = CreateDefaultSubobject<UUnitModifiableStatComponent>(TEXT("MaxHealthComponent"));
	MaxHealth->OnChanged().AddUniqueDynamic(this, &UHealth_Component::HandleOnMaxHealthChanged);
	// ...
}


void UHealth_Component::TakeDamage(float Amount)
{
	bool Death = CurrentHealth - Amount <= 0;
	if (Death) {
		CurrentHealth = 0;
		DeathEvent.Broadcast();
	}
	else {
		CurrentHealth = CurrentHealth - Amount;
	}
}

void UHealth_Component::Heal(float Amount)
{
	if (IsHealable()) {
		float CurrentMaxHealth = MaxHealth->GetCurrentValue();
		CurrentHealth = CurrentHealth + Amount > CurrentMaxHealth ? CurrentMaxHealth : CurrentHealth + Amount;
	}
}

bool UHealth_Component::IsHealable()
{
	return  CurrentHealth < MaxHealth->GetCurrentValue();
}

// Called when the game starts
void UHealth_Component::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth->GetCurrentValue();
}


void UHealth_Component::HandleOnMaxHealthChanged(float OldValue, float NewValue)
{
	// keep difference between current health and max health value
	CurrentHealth = CurrentHealth > NewValue ? NewValue : NewValue - (OldValue - CurrentHealth);
}





