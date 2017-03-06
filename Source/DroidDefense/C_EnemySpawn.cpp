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
	
	FUnitSpawnOrder nOrder1;
	nOrder1.type = EUnitTypes::BasicUnit;
	nOrder1.amount = 5;
	nOrder1.spawned = 0;
	nOrder1.delayBetween = 1.0f;
	nOrder1.delayAfter = 10.0f;

	FWave nWave1;
	nWave1.spawnIndicator = 0;
	nWave1.timer = 0;
	nWave1.spawnList.Add (nOrder1);

	mr_Waves.Add (nWave1);

	FUnitSpawnOrder nOrder2;
	nOrder2.type = EUnitTypes::BasicUnit;
	nOrder2.amount = 10;
	nOrder2.spawned = 0;
	nOrder2.delayBetween = 0.8f;
	nOrder2.delayAfter = 10.0f;

	FUnitSpawnOrder nOrder3;
	nOrder3.type = EUnitTypes::BasicUnit;
	nOrder3.amount = 5;
	nOrder3.spawned = 0;
	nOrder3.delayBetween = 1.5f;
	nOrder3.delayAfter = 10.0f;


	FWave nWave2;
	nWave2.spawnIndicator = 0;
	nWave2.timer = 0;
	nWave2.spawnList.Add (nOrder2);
	nWave2.spawnList.Add (nOrder3);

	mr_Waves.Add (nWave2);

}

FText AC_EnemySpawn::GetWaveIndicator ()
{
	FString ret;
	switch (m_State)
	{
	case EGameState::Playing:
		ret = FString::Printf (TEXT ("%i of %i - order: %i of %i - unit: %i of %i"), m_CurrentWave + 1, mr_Waves.Num (),
			mr_Waves[m_CurrentWave].spawnIndicator + 1, mr_Waves[m_CurrentWave].spawnList.Num (),
			mr_Waves[m_CurrentWave].spawnList[mr_Waves[m_CurrentWave].spawnIndicator].spawned + 1, mr_Waves[m_CurrentWave].spawnList[mr_Waves[m_CurrentWave].spawnIndicator].amount);
		break;
	case EGameState::Deployed:
		ret = FString::Printf (TEXT ("Final!!!"));
		break;
	case EGameState::Won:
		ret = "Victory!!";
		break;
	case EGameState::Lost:
		ret = "You lost!";
		break;
	default:
		break;
	}


	return FText::FromString(ret);
}

// Called when the game starts or when spawned
void AC_EnemySpawn::BeginPlay()
{
	Super::BeginPlay();
	
	m_State = EGameState::Playing;

}

// Called every frame
void AC_EnemySpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (m_CurrentWave < mr_Waves.Num())
	{
		mr_Waves[m_CurrentWave].timer += DeltaTime;
		mr_Waves[m_CurrentWave].spawnList[mr_Waves[m_CurrentWave].spawnIndicator].timer += DeltaTime;

		if (mr_Waves[m_CurrentWave].spawnList[mr_Waves[m_CurrentWave].spawnIndicator].timer > mr_Waves[m_CurrentWave].spawnList[mr_Waves[m_CurrentWave].spawnIndicator].delayBetween)
		{
			mr_Waves[m_CurrentWave].spawnList[mr_Waves[m_CurrentWave].spawnIndicator].timer = 0;

			UWorld* world = GetWorld ();

			FVector loc = GetActorLocation ();
			FRotator rot = FRotator::ZeroRotator;

			mpr_Units.emplace_back (world->SpawnActor<AC_BasicUnit> (mBP_DroidUnit, loc, rot));
			mpr_Units.back ()->Init (FVector (3200.0f, 7200.0f, 0.0f));

			mr_Waves[m_CurrentWave].spawnList[mr_Waves[m_CurrentWave].spawnIndicator].spawned++;

			if (mr_Waves[m_CurrentWave].spawnList[mr_Waves[m_CurrentWave].spawnIndicator].spawned >= mr_Waves[m_CurrentWave].spawnList[mr_Waves[m_CurrentWave].spawnIndicator].amount)
			{
				mr_Waves[m_CurrentWave].spawnIndicator++;

				if (mr_Waves[m_CurrentWave].spawnIndicator >= mr_Waves[m_CurrentWave].spawnList.Num ())
				{
					m_CurrentWave++;
				}
			}
		}
	}

	if (m_CurrentWave >= mr_Waves.Num ())
	{
		m_State = EGameState::Deployed;
	}
	


    m_Timer += DeltaTime;

}

