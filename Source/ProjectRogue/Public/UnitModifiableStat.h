// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnitModifiableStat.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChangedEvent, float, OldValue, float, NewValue);

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTROGUE_API FUnitModifiableStat
{
	GENERATED_USTRUCT_BODY()

public:
	/** Broadcasts whenever the value changes */
	FChangedEvent& OnChanged() { return ChangedEvent; }

	
	void ChangeAddedValue(const float amount);

	
	void ChangeMultiplier(const float amount);

	
	float GetCurrentValue() const;

	void Reset();

	void Initialize(float BaseValue);

	float Update();

private:
	// raw base stat. should not change
	UPROPERTY(EditDefaultsOnly)
	float BaseStat = 1;

	// overall added value
	UPROPERTY(VisibleAnywhere)
	float AddedValue = 0;

	// multiplayer value
	UPROPERTY(VisibleAnywhere)
	float Multiplier =1;

	UPROPERTY(EditDefaultsOnly)
	float MaxAddedValue = 100;

	UPROPERTY(EditDefaultsOnly)
	float MinAddedValue = 0;

	UPROPERTY(EditDefaultsOnly)
	float MaxMultiplierValue = 10;

	UPROPERTY(EditDefaultsOnly)
	float MinMultiplierValue = 0;

	UPROPERTY(VisibleAnywhere)
	float CurrentValue =1;

	/** Broadcasts whenever the current value changes */
	UPROPERTY(BlueprintAssignable)
	FChangedEvent ChangedEvent;

	

public:
	FUnitModifiableStat();

};


UCLASS()
class UUnitModifiableStatBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "UnitModifiableStat|Methods")
	static void ChangeAddedValue(UPARAM(ref) FUnitModifiableStat& UnitStat, const float amount)
	{
		return UnitStat.ChangeAddedValue(amount);
	};

	UFUNCTION(BlueprintCallable, Category = "UnitModifiableStat|Methods")
	static void ChangeMultiplier(UPARAM(ref) FUnitModifiableStat& UnitStat, const float amount)
	{
		return UnitStat.ChangeMultiplier(amount);
	};


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UnitModifiableStat|Methods")
	static float GetCurrentValue(UPARAM(ref) FUnitModifiableStat& UnitStat)
	{
		return UnitStat.GetCurrentValue();
	};

};