// Copyright Kris Rogos

#include "DroidDefense.h"
#include "C_BasicTower.h"


// Sets default values
AC_BasicTower::AC_BasicTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint> bp_Bullet (TEXT ("Blueprint'/Game/DroidDefense/Ammo/BP_Bullet.BP_Bullet'"));
	if (bp_Bullet.Object) mBP_Bullet = (UClass*)bp_Bullet.Object->GeneratedClass;

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

	// make sure to update the timer
	m_FireTimer -= DeltaTime;

	if (m_FireTimer < 0.0f)
	{
		// let the blueprint know this tower can now fire
		m_CanFire = true;

		// timer reset
		m_FireTimer = m_FireTimerMax;
	}

}

