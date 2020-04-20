// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnitModifiableStat.h"
#include "BasePawn.generated.h"


UCLASS()
class PROJECTROGUE_API ABasePawn : public APawn
{
	GENERATED_BODY()

	

public:
	// Sets default values for this character's properties
	ABasePawn();

	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	UUnitModifiableStatComponent* FireRate;

	/* The speed of the character */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	UUnitModifiableStatComponent* MoveSpeed;

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MeshComponent;

protected:


public:	


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
