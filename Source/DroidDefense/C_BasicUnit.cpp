// Fill out your copyright notice in the Description page of Project Settings.

#include "DroidDefense.h"
#include "C_BasicUnit.h"


// Sets default values
AC_BasicUnit::AC_BasicUnit ()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_BasicUnit::BeginPlay()
{
	Super::BeginPlay();
	
	m_TargetLoc = FVector (3200.0f, 6800.0f, 0.0f);

}

// Called every frame
void AC_BasicUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator targetRot = FRotationMatrix::MakeFromX (m_TargetLoc - GetActorLocation ()).Rotator ();

	SetActorRotation (FMath::Lerp (GetActorRotation (), targetRot, 0.5*DeltaTime));

	const FVector moveRot = FRotationMatrix (GetActorRotation ()).GetScaledAxis (EAxis::X);
	AddMovementInput (moveRot, 10.0f * DeltaTime);
	

}

// Called to bind functionality to input
void AC_BasicUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

