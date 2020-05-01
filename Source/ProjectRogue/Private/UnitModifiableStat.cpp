// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitModifiableStat.h"
#include "Math/UnrealMathUtility.h"


UUnitModifiableStatComponent::UUnitModifiableStatComponent()
{
	this->BaseStat = 1;
	this->CurrentValue = (BaseStat + AddedValue) * Multiplier;
}

UUnitModifiableStatComponent::~UUnitModifiableStatComponent()
{
}

void UUnitModifiableStatComponent::Initialize(float BaseValue)
{
	this->BaseStat = BaseValue;
}

void UUnitModifiableStatComponent::ChangeAddedValue(float amount)
{
	AddedValue = FMath::Clamp(AddedValue + amount, MinAddedValue, MaxAddedValue);
	Update();
}

void UUnitModifiableStatComponent::ChangeMultiplier(float amount)
{
	Multiplier = FMath::Clamp(Multiplier * amount, MinMultiplierValue, MaxMultiplierValue);
	Update();
}

float UUnitModifiableStatComponent::GetCurrentValue() const
{
	return CurrentValue;
}

void UUnitModifiableStatComponent::Reset()
{
	AddedValue = 0;
	Multiplier = 1;
	Update();
}

float UUnitModifiableStatComponent::Update()
{
	float OldValue = CurrentValue;
	CurrentValue = (BaseStat + AddedValue) * Multiplier;
	UE_LOG(LogTemp, Warning, TEXT("ValueUpdate Old: %f New %f"), OldValue, CurrentValue);
	if (OldValue != CurrentValue) {
		ChangedEvent.Broadcast(OldValue, CurrentValue);
	}
	
	return CurrentValue;
}

// Called when the game starts
void UUnitModifiableStatComponent::BeginPlay()
{
	Super::BeginPlay();

	Update();

}
