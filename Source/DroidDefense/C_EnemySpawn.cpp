// Fill out your copyright notice in the Description page of Project Settings.

#include "DroidDefense.h"
#include "C_EnemySpawn.h"


// Sets default values
AC_EnemySpawn::AC_EnemySpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UBlueprint> bp_Droid (TEXT ("Blueprint'/Game/DroidDefense/Units/BP_DroidUnit.BP_DroidUnit'"));
    if (bp_Droid.Object) mBP_DroidUnit = (UClass*)bp_Droid.Object->GeneratedClass;

}

// Called when the game starts or when spawned
void AC_EnemySpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_EnemySpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    m_Timer += DeltaTime;

    if (m_Timer > k_TimerMax)
    {
        // reset timer
        m_Timer = 0.0f;

        UWorld* world = GetWorld ();

        FVector loc = GetActorLocation();
        FRotator rot = FRotator::ZeroRotator;

        mpr_Units.emplace_back( world->SpawnActor<AC_BasicUnit> (mBP_DroidUnit, loc, rot) );
		mpr_Units.back()->Init (FVector (3200.0f, 7200.0f, 0.0f));

    }

}

