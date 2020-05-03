// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "UnitModifiableStat.h"
#include "HealthComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;

	//default stats
	FireRate = CreateDefaultSubobject<UUnitModifiableStatComponent>(TEXT("FireRate"));
	MoveSpeed = CreateDefaultSubobject<UUnitModifiableStatComponent>(TEXT("MoveSpeed"));

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	FireRate->Update();
	MoveSpeed->Update();
	
}





// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
}

