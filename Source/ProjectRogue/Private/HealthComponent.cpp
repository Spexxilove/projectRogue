// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "UnitModifiableStat.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
	
	// ...
}


void UHealthComponent::TakeDamage(float Amount)
{
	
	bool Death = CurrentHealth - Amount <= 0;
	if (Death) {
		CurrentHealth = 0;
		DamageTakenEvent.Broadcast(Amount, true);
		DeathEvent.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("DEATH: %f"), CurrentHealth)
	}
	else {
		CurrentHealth = CurrentHealth - Amount;
		DamageTakenEvent.Broadcast(Amount, false);
		UE_LOG(LogTemp, Warning, TEXT("new health: %f"), CurrentHealth)
	}
}

void UHealthComponent::Heal(float Amount)
{
	if (IsHealable()) {
		float CurrentMaxHealth = MaxHealth->GetCurrentValue();
		CurrentHealth = CurrentHealth + Amount > CurrentMaxHealth ? CurrentMaxHealth : CurrentHealth + Amount;
	}
}

bool UHealthComponent::IsHealable() const
{
	return  CurrentHealth < MaxHealth->GetCurrentValue();
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	MaxHealth->Update();
	MaxHealth->OnChanged().AddUniqueDynamic(this, &UHealthComponent::HandleOnMaxHealthChanged);
	CurrentHealth = MaxHealth->GetCurrentValue();
}


void UHealthComponent::HandleOnMaxHealthChanged(float OldValue, float NewValue)
{
	// keep difference between current health and max health value
	CurrentHealth = CurrentHealth > NewValue ? NewValue : NewValue - (OldValue - CurrentHealth);
}





