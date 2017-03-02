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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};