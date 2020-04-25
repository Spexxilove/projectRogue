// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FiringComponent.generated.h"

class AProjectRogueProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTROGUE_API UFiringComponent : public UActorComponent
{
	GENERATED_BODY()
private:

	/*Base reload time in seconds*/
	UPROPERTY(EditDefaultsOnly)
	float baseReloadTime = 1;

	float LastFireTime = 0;

	/*Reload time with modifiers in seconds*/
	float ModifiedReloadTime = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectRogueProjectile> ProjectileBlueprint;

public:	
	// Sets default values for this component's properties
	UFiringComponent();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool CanFire();

	float GetReloadProgressPercentage();

	float GetRemainingReloadTime();

	float GetReloadTime();

	void Fire();


private:

	void HandleOnParentFireRateChanged(float OldValue, float NewValue);

	void SetModifiedReloadTime(float StatModifier);
};
