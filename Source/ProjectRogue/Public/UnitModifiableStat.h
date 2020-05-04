// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UnitModifiableStat.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChangedEvent, float, OldValue, float, NewValue);

/**
 * 
 */
UCLASS(ClassGroup = (Custom), DefaultToInstanced)
class PROJECTROGUE_API UUnitModifiableStatComponent : public UObject
{
	GENERATED_BODY()

public:
	/** Broadcasts whenever the value changes */
	FChangedEvent& OnChanged() { return ChangedEvent; }

	UFUNCTION(BlueprintCallable)
	void ChangeAddedValue(float amount);

	UFUNCTION(BlueprintCallable)
	void ChangeMultiplier(float amount);

	UFUNCTION(BlueprintCallable)
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
	UUnitModifiableStatComponent();
	~UUnitModifiableStatComponent();
};
