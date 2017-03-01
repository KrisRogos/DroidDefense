// Copyright Kris Rogos

#include "DroidDefense.h"
#include "C_BasicTower.h"


// Sets default values
AC_BasicTower::AC_BasicTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_BasicTower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_BasicTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

