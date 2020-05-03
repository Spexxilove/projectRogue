// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitModifiableStat.h"
#include "Math/UnrealMathUtility.h"


UUnitModifiableStatComponent::UUnitModifiableStatComponent()
	
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] created stat"), *GetName());
	CurrentValue = (BaseStat + AddedValue) * Multiplier;
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
	UE_LOG(LogTemp, Warning, TEXT("[%s] ValueUpdate Old: %f New %f"), *GetName(), OldValue, CurrentValue);
	if (OldValue != CurrentValue) {
		ChangedEvent.Broadcast(OldValue, CurrentValue);
	}
	
	return CurrentValue;
}

