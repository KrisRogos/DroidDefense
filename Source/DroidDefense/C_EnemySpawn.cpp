// Fill out your copyright notice in the Description page of Project Settings.

#include "DroidDefense.h"
#include "C_EnemySpawn.h"


// Sets default values
AC_EnemySpawn::AC_EnemySpawn()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //static ConstructorHelpers::FObjectFinder<UBlueprint> bp_Droid (TEXT ("Blueprint'/Game/DroidDefense/Units/BP_DroidUnit.BP_DroidUnit'"));
    //if (bp_Droid.Object) mBP_DroidUnit = (UClass*)bp_Droid.Object->GeneratedClass;

    //static ConstructorHelpers::FObjectFinder<UBlueprint> bp_Heavy (TEXT ("Blueprint'/Game/DroidDefense/Units/BP_HeavyUnit.BP_HeavyUnit'"));
    //if (bp_Heavy.Object) mBP_HeavyUnit = (UClass*)bp_Heavy.Object->GeneratedClass;

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
    
    // Waves are created in a blueprint for easier edit
    CreateWaves ();

    m_State = EGameState::Playing;

}

// Called every frame
void AC_EnemySpawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (m_CurrentWave < mr_Waves.Num() && mr_Waves[m_CurrentWave].spawnIndicator < mr_Waves[m_CurrentWave].spawnList.Num())
    {
        mr_Waves[m_CurrentWave].timer += DeltaTime;
        mr_Waves[m_CurrentWave].spawnList[mr_Waves[m_CurrentWave].spawnIndicator].timer += DeltaTime;

        if (mr_Waves[m_CurrentWave].spawnList[mr_Waves[m_CurrentWave].spawnIndicator].timer > mr_Waves[m_CurrentWave].spawnList[mr_Waves[m_CurrentWave].spawnIndicator].delayBetween)
        {
            mr_Waves[m_CurrentWave].spawnList[mr_Waves[m_CurrentWave].spawnIndicator].timer = 0;

            // spawn the unit itself (using a blueprint)
            mpr_Units.emplace_back (SpawnUnit (mr_Waves[m_CurrentWave].spawnList[mr_Waves[m_CurrentWave].spawnIndicator].type));

            mpr_Units.back ()->Init (FVector (3200.0f, 7200.0f, 0.0f), 18, 8);

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

