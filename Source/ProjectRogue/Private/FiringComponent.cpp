// Fill out your copyright notice in the Description page of Project Settings.


#include "FiringComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../ProjectRogueProjectile.h"
#include "../BasePawn.h"
#include "UnitModifiableStat.h"

// Sets default values for this component's properties
UFiringComponent::UFiringComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFiringComponent::BeginPlay()
{
	Super::BeginPlay();

	ABasePawn* ParentActor = Cast<ABasePawn>( GetOwner() );
	
	if (!ParentActor) {
		UE_LOG(LogInit, Warning, TEXT("FiringComponent is not a child of BasePawn"));
		return;
	}

	UUnitModifiableStatComponent* FireRateStat = ParentActor->FireRate;
	if (!ensure(FireRateStat)) {
		return;
	}
	SetModifiedReloadTime(FireRateStat->GetCurrentValue());
	FireRateStat->OnChanged().AddDynamic(this, &UFiringComponent::HandleOnParentFireRateChanged);

	
}


// Called every frame
void UFiringComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UFiringComponent::CanFire()
{
	return LastFireTime + ModifiedReloadTime <= GetWorld()->GetTimeSeconds();
}

float UFiringComponent::GetReloadProgressPercentage()
{
	if (CanFire()) {
		return 1.0f;
	}

	float CurrentTime = GetWorld()->GetTimeSeconds();	
	return  (CurrentTime - LastFireTime) / ModifiedReloadTime;
}

float UFiringComponent::GetRemainingReloadTime()
{
	if (CanFire()) {
		return 0.0f;
	}

	float CurrentTime = GetWorld()->GetTimeSeconds();
	return ModifiedReloadTime - (CurrentTime - LastFireTime);
}

float UFiringComponent::GetReloadTime()
{
	return ModifiedReloadTime;
}

void UFiringComponent::Fire()
{
	if (CanFire()) {
		//TODO: actually fire
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

void UFiringComponent::HandleOnParentFireRateChanged(float OldValue, float NewValue)
{
	SetModifiedReloadTime(NewValue);
}

void UFiringComponent::SetModifiedReloadTime(float StatModifier)
{
	//TODO: adjust the values for this
	ModifiedReloadTime = baseReloadTime / StatModifier;
}



