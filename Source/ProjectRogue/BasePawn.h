// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "BasePawn.generated.h"

class UCurveFloat;
struct FTimeline;

UCLASS()
class PROJECTROGUE_API ABasePawn : public APawn
{
	GENERATED_BODY()

	

public:

	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, VisibleAnywhere, BlueprintReadOnly)
	class UUnitModifiableStatComponent* FireRate = nullptr;

	/* The speed of the character */
	UPROPERTY(Category = Gameplay, VisibleAnywhere, BlueprintReadOnly)
	class UUnitModifiableStatComponent* MoveSpeed = nullptr;

	/* The health of the character */
	UPROPERTY(Category = Gameplay, VisibleAnywhere, BlueprintReadOnly)
	class UHealthComponent* Health = nullptr;

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MeshComponent;

public:	

	// Sets default values for this character's properties
	ABasePawn();

	void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:

	void Tick(float DeltaTime) override;

	FTimeline* MaterialDamageEffectTimeline;

	UPROPERTY(EditDefaultsOnly, Category= "Animation")
	UCurveFloat* MaterialDamageEffectCurve;

private:
	UPROPERTY()
	UMaterialInstanceDynamic* MainMaterialInstance;




private:
	UFUNCTION()
	void HandleOnDeath();
	
	UFUNCTION()
	void HandleOnDamageTaken(float DamageAmount, bool IsDead);

	UFUNCTION()
	void HandleOnDamageEffectUpdate(float EffectIntensityScalar);
};
