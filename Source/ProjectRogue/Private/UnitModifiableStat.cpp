// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitModifiableStat.h"
#include "Math/UnrealMathUtility.h"


FUnitModifiableStat::FUnitModifiableStat()
	
{
	//UE_LOG(LogTemp, Warning, TEXT("created stat"));
	CurrentValue = (BaseStat + AddedValue) * Multiplier;
}


void FUnitModifiableStat::Initialize(float BaseValue)
{
	this->BaseStat = BaseValue;
}

void FUnitModifiableStat::ChangeAddedValue(float amount)
{
	AddedValue = FMath::Clamp(AddedValue + amount, MinAddedValue, MaxAddedValue);
	Update();
}

void FUnitModifiableStat::ChangeMultiplier(float amount)
{
	Multiplier = FMath::Clamp(Multiplier * amount, MinMultiplierValue, MaxMultiplierValue);
	Update();
}

float FUnitModifiableStat::GetCurrentValue() const
{
	return CurrentValue;
}

void FUnitModifiableStat::Reset()
{
	AddedValue = 0;
	Multiplier = 1;
	Update();
}

float FUnitModifiableStat::Update()
{
	float OldValue = CurrentValue;
	CurrentValue = (BaseStat + AddedValue) * Multiplier;
	UE_LOG(LogTemp, Warning, TEXT("ValueUpdate Old: %f New %f"),  OldValue, CurrentValue);
	if (OldValue != CurrentValue) {
		ChangedEvent.Broadcast(OldValue, CurrentValue);
	}
	
	return CurrentValue;
}



