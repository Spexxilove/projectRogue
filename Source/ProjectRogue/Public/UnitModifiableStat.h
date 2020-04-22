// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitModifiableStat.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChangedEvent, float, OldValue, float, NewValue);

/**
 * 
 */
UCLASS()
class UUnitModifiableStatComponent : public UActorComponent
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
	float GetCurrentValue();

	void Reset();

	void Initialize(float BaseValue);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

private:
	// raw base stat. should not change
	UPROPERTY(EditDefaultsOnly)
	float BaseStat;

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

	float Update();

public:
	UUnitModifiableStatComponent();
	~UUnitModifiableStatComponent();
};
