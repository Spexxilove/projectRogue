// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "UnitModifiableStat.h"
#include "HealthComponent.h"
#include "Components/TimelineComponent.h"



// Sets default values
ABasePawn::ABasePawn()
{	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;
	

	//default stats
	//TODO: move to own Stats component
	FireRate = CreateDefaultSubobject<UUnitModifiableStatComponent>(TEXT("FireRate"));
	MoveSpeed = CreateDefaultSubobject<UUnitModifiableStatComponent>(TEXT("MoveSpeed"));

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

	MainMaterialInstance = MeshComponent->CreateAndSetMaterialInstanceDynamic(0);

	MaterialDamageEffectTimeline = new FTimeline();
	if (MaterialDamageEffectCurve) {
		FOnTimelineFloat TimelineCallback;
		TimelineCallback.BindUFunction(this, FName("HandleOnDamageEffectUpdate"));
		MaterialDamageEffectTimeline->AddInterpFloat(MaterialDamageEffectCurve, TimelineCallback);
	}

	// update stats
	FireRate->Update();
	MoveSpeed->Update();

	// bind health events
	Health->OnDeath().AddDynamic(this, &ABasePawn::HandleOnDeath);
	Health->OnDamageTaken().AddDynamic(this, &ABasePawn::HandleOnDamageTaken);


}





// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
}

void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MaterialDamageEffectTimeline->TickTimeline(DeltaTime);
}

void ABasePawn::HandleOnDeath()
{
	Destroy();
}

void ABasePawn::HandleOnDamageTaken(float DamageAmount, bool IsDead)
{
	if (IsDead) {
		return;
	}

	MaterialDamageEffectTimeline->PlayFromStart();
	// do some stuff
}

void ABasePawn::HandleOnDamageEffectUpdate(float EffectIntensityScalar)
{
	MainMaterialInstance->SetScalarParameterValue(FName("DamagedEffect"), EffectIntensityScalar);
}

