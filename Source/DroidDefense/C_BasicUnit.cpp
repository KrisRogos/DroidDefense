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
    
    m_TargetLoc = FVector (3200.0f, 8000.0f, 0.0f);
    m_TargetX = 17;
    m_TargetY = 8;

}

bool AC_BasicUnit::AStarTrace ()
{
    return false;
}

void AC_BasicUnit::Init (FVector a_TargetLoc, int a_X, int a_Y)
{
    m_TargetLoc = a_TargetLoc;
    m_TargetX = a_X;
    m_TargetY = a_Y;
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

