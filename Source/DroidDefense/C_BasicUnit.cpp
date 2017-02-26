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
	
}

// Called every frame
void AC_BasicUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_BasicUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

