// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "C_BasicTower.h"
#include "C_WorldTile.generated.h"

UENUM(BlueprintType)
enum class EMapStatus : uint8
{
    EMPTY       UMETA (DisplayName = "Empty tile"),
    TOWER       UMETA (DisplayName = "Has a tower")
};

UCLASS()
class DROIDDEFENSE_API AC_WorldTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_WorldTile();

    UPROPERTY (EditAnywhere, DisplayName = "X id", Category = "World Tile")
        uint8 X;

    UPROPERTY (EditAnywhere, DisplayName = "Y id", Category = "World Tile")
        uint8 Y;

    UPROPERTY (EditAnywhere, BlueprintReadWrite, DisplayName = "Tile state", Category = "World Tile")
        EMapStatus m_Status;

    UPROPERTY (EditAnywhere, BlueprintReadWrite, DisplayName = "Tile content", Category = "World Tile")
        AC_BasicTower* m_Tower;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
