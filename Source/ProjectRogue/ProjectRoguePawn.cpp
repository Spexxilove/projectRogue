// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectRoguePawn.h"
#include "ProjectRogueProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "UnitModifiableStat.h"
#include "FiringComponent.h"
#include "Components/ArrowComponent.h"


const FName AProjectRoguePawn::MoveForwardBinding("MoveForward");
const FName AProjectRoguePawn::MoveRightBinding("MoveRight");
const FName AProjectRoguePawn::FireBinding("Fire");

AProjectRoguePawn::AProjectRoguePawn():ABasePawn()
{	
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	
	
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	MeshComponent->SetStaticMesh(ShipMesh.Object);
	
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm


	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	bCanFire = true;
	FiringComponent = CreateDefaultSubobject<UFiringComponent>(TEXT("Gun"));
	UArrowComponent* BulletSpawnPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("BulletSpawnPoint"));
	BulletSpawnPosition->SetRelativeLocation(GunOffset);

	FiringComponent->SetBulletSpawnPoint(BulletSpawnPosition->GetRelativeTransform());
}

void AProjectRoguePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAction(FireBinding, EInputEvent::IE_Pressed, this, &AProjectRoguePawn::Fire);
}

void AProjectRoguePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed.GetCurrentValue() * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}

	// Aim
	UpdateRotation();
	
}

void AProjectRoguePawn::UpdateRotation()
{
	
	// rotate towards target
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
		return;

	// Get the coordinates of the mouse from our controller  
	float LocationX;
	float LocationY;
	PlayerController->GetMousePosition(LocationX, LocationY);
	// Do a trace and see if there the position intersects something in the world  
	FVector2D MousePosition(LocationX, LocationY);
	FHitResult HitResult;
	const bool bTraceComplex = false;

	if (PlayerController->GetHitResultAtScreenPosition(MousePosition, ECC_Visibility, bTraceComplex, HitResult) == true) {
		FVector TargetLocation = HitResult.Location;
		FVector ActorLocation = this->ActorToWorld().GetLocation();
		// set z difference to 0 to always shoot horizontal
		TargetLocation.Z = ActorLocation.Z;

		RotateTowards(TargetLocation - ActorLocation);
	}
	
}


void AProjectRoguePawn::ShotTimerExpired()
{
	bCanFire = true;
}

void AProjectRoguePawn::Fire()
{
	// Try and Fire shot
	FiringComponent->Fire();
}

void AProjectRoguePawn::RotateTowards(FVector AimDirection)
{
	this->SetActorRotation(AimDirection.ToOrientationRotator());
}

