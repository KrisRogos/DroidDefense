// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include <vector>
#include "C_BasicUnit.h"
#include "C_EnemySpawn.generated.h"

const float k_TimerMax = 10.0f;

UENUM (BlueprintType)
enum class EGameState : uint8
{
    Playing		UMETA(DisplayName = "Playing"),
    Deployed	UMETA(DisplayName = "All units deployed"),
    Won			UMETA(DisplayName = "Won"),
    Lost		UMETA(DisplayName = "Lost")
};

UENUM (BlueprintType)
enum class EUnitTypes : uint8
{
    BasicUnit	UMETA(DisplayName = "Melee"),
    HeavyUnit   UMETA(DisplayName = "Heavy"),
    BasicTank	UMETA(DisplayName = "Tank")
};

USTRUCT(BlueprintType)
struct FUnitSpawnOrder
{
    GENERATED_BODY ()

    UPROPERTY (BlueprintReadWrite)
    EUnitTypes type;
    UPROPERTY (BlueprintReadWrite)
    int amount;
    UPROPERTY (BlueprintReadWrite)
    int spawned;
    UPROPERTY (BlueprintReadWrite)
    float delay;
    UPROPERTY (BlueprintReadWrite)
    float timer;
};

USTRUCT (BlueprintType)
struct FWave
{
    GENERATED_BODY ()

    UPROPERTY (BlueprintReadWrite)
    TArray<FUnitSpawnOrder> spawnList;
    UPROPERTY (BlueprintReadWrite)
    int spawnIndicator;
    UPROPERTY (BlueprintReadWrite)
    float timer;
    UPROPERTY (BlueprintReadWrite)
    float delay;
    UPROPERTY (BlueprintReadWrite)
    bool deployed;
};

UCLASS()
class DROIDDEFENSE_API AC_EnemySpawn : public AActor
{
    GENERATED_BODY ()

    TSubclassOf<class AC_BasicUnit> mBP_DroidUnit;
    TSubclassOf<class AC_BasicUnit> mBP_HeavyUnit;

public:	
    // Sets default values for this actor's properties
    AC_EnemySpawn();

    UPROPERTY (EditAnywhere, DisplayName = "state of the game", Category = "Game")
        EGameState m_State;

    UPROPERTY (EditAnywhere, DisplayName = "timer", Category = "Enemy spawner")
        float m_Timer;

    std::vector<AC_BasicUnit*> mpr_Units;
    
    UPROPERTY (EditAnywhere, BlueprintReadWrite, DisplayName = "Waves", Category = "Enemy spawner")
    TArray<FWave> mr_Waves;

    UPROPERTY (EditAnywhere, DisplayName = "Wave counter", Category = "Enemy spawner")
    int m_CurrentWave;

    UFUNCTION (BlueprintImplementableEvent, DisplayName = "Wave create", Category = "Enemy spawner")
        void CreateWaves ();

    UFUNCTION (BlueprintImplementableEvent, DisplayName = "Spawn unit", Category = "Enemy spawner")
        AC_BasicUnit* SpawnUnit (EUnitTypes a_Type);

    UFUNCTION (BlueprintCallable, DisplayName = "Wave Indicator", Category = "Enemy spawner")
        FText GetWaveIndicator ();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    
    
};
