// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitModifiableStat.generated.h"
/**
 * 
 */
UCLASS()
class UUnitModifiableStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Broadcasts whenever the layer changes */
	DECLARE_EVENT_TwoParams(FLayerViewModel, FChangedEvent, float, float)
	FChangedEvent& OnChanged(float OldValue, float NewValue) { return ChangedEvent; }

	void ChangeAddedValue(float amount);

	void ChangeMultiplier(float amount);

	float GetCurrentValue();

	void Reset();

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
	float MaxAddedValue = 0;

	UPROPERTY(EditDefaultsOnly)
	float MinAddedValue = 100;

	UPROPERTY(EditDefaultsOnly)
	float MaxMultiplierValue = 10;

	UPROPERTY(EditDefaultsOnly)
	float MinMultiplierValue = 1;

	UPROPERTY(VisibleAnywhere)
	float CurrentValue;

	/** Broadcasts whenever the current value changes */
	FChangedEvent ChangedEvent;

	float Update();

public:
	UUnitModifiableStatComponent();
	~UUnitModifiableStatComponent();
};
