// Fill out your copyright notice in the Description page of Project Settings.


#include "FiringComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../ProjectRogueProjectile.h"
#include "../BasePawn.h"
#include "UnitModifiableStat.h"

// Sets default values for this component's properties
UFiringComponent::UFiringComponent() :
	baseReloadTime(1),
	LastFireTime(0),
	ModifiedReloadTime(1)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


void UFiringComponent::SetBulletSpawnPoint(const FTransform& SpawnPointTransform)
{
	BulletSpawnPoint = SpawnPointTransform;
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

	FUnitModifiableStat& FireRateStat = ParentActor->FireRate;
	
	SetModifiedReloadTime(FireRateStat.GetCurrentValue());
	FireRateStat.OnChanged().AddDynamic(this, &UFiringComponent::HandleOnParentFireRateChanged);

	ShotSpeed.Update();
	ShotScale.Update();
	ShotDamage.Update();
}






// Called every frame
void UFiringComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UFiringComponent::CanFire() const
{
	return LastFireTime + ModifiedReloadTime <= GetWorld()->GetTimeSeconds();
}

float UFiringComponent::GetReloadProgressPercentage() const
{
	if (CanFire()) {
		return 1.0f;
	}

	float CurrentTime = GetWorld()->GetTimeSeconds();	
	return  (CurrentTime - LastFireTime) / ModifiedReloadTime;
}

float UFiringComponent::GetRemainingReloadTime() const
{
	if (CanFire()) {
		return 0.0f;
	}

	float CurrentTime = GetWorld()->GetTimeSeconds();
	return ModifiedReloadTime - (CurrentTime - LastFireTime);
}

float UFiringComponent::GetReloadTime() const
{
	return ModifiedReloadTime;
}

void UFiringComponent::Fire()
{
	if (CanFire()) {
		auto Projectile = GetWorld()->SpawnActorDeferred<AProjectRogueProjectile>(ProjectileBlueprint, BulletSpawnPoint*GetOwner()->GetActorTransform(), GetOwner());
		
		Projectile->SetDamage(ShotDamage.GetCurrentValue());
		
		// set parameters
		UGameplayStatics::FinishSpawningActor(Projectile, Projectile->GetTransform());
		

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



