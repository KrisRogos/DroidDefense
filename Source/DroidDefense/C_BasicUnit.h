// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "C_BasicUnit.generated.h"

UCLASS()
class DROIDDEFENSE_API AC_BasicUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
    AC_BasicUnit ();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// goal location
	UPROPERTY(BlueprintReadWrite, DisplayName = "Target Location", Category = "Unit data")
	FVector m_TargetLoc;

	void Init (FVector a_TargetLoc);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
