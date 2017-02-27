// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include <vector>
#include "C_BasicUnit.h"
#include "C_EnemySpawn.generated.h"

const float k_TimerMax = 5.0f;

UCLASS()
class DROIDDEFENSE_API AC_EnemySpawn : public AActor
{
    GENERATED_BODY ()

        TSubclassOf<class AC_BasicUnit> mBP_DroidUnit;

public:	
	// Sets default values for this actor's properties
	AC_EnemySpawn();

    UPROPERTY (EditAnywhere, DisplayName = "timer", Category = "Enemy spawner")
        float m_Timer;

    std::vector<AC_BasicUnit*> mpr_Units;
    

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
