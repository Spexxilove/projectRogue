// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

// Sets default values
ABasePawn::ABasePawn()
{
	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;

	FireRate = CreateDefaultSubobject<UUnitModifiableStatComponent>(TEXT("FireRateComponent"));
	MoveSpeed = CreateDefaultSubobject<UUnitModifiableStatComponent>(TEXT("MoveSpeedComponent"));
}





// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
}

