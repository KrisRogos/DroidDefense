// Copyright Kris Rogos

#pragma once

#include "GameFramework/Actor.h"
#include "C_BasicTower.generated.h"

UCLASS()
class DROIDDEFENSE_API AC_BasicTower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_BasicTower();

	UPROPERTY (BlueprintReadWrite, DisplayName = "Part cost", Category = "Tower data")
		int m_Cost;

	UPROPERTY (BlueprintReadWrite, DisplayName = "Detection Range", Category = "Tower data")
		float m_Range;

	UPROPERTY (BlueprintReadWrite, DisplayName = "Fire Rate", Category = "Tower data")
		float m_FireTimerMax;

		float m_FireTimer;

		UPROPERTY (BlueprintReadWrite, DisplayName = "Can fire", Category = "Tower data")
			bool m_CanFire;

	UPROPERTY (BlueprintReadWrite, DisplayName = "Damage", Category = "Tower data")	
		float m_Damage;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
