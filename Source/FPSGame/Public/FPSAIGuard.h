// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState : uint8 {


	Idle,
	Suspicious,
	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;
	
	FRotator OriginalRotation;
	
	FTimerHandle TimerHandle_ResetOrientation;

	UPROPERTY(ReplicatedUsing=OnRep_GuardState)
	EAIState GuardState;

	UFUNCTION()
	void OnRep_GuardState();

	//Lets the guard go on patrol
	UPROPERTY(EditInstanceOnly, Category = "AI")
	bool bIsPatrolling;

	//First of two patrol points to patrol between.
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition="bIsPatrolling"))
	AActor* FirstPatrolPoint;


	//Second of two patrol points to patrol between.
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bIsPatrolling"))
	AActor* SecondPatrolPoint;


	//The current point the actor is either moving to or standing at.
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bIsPatrolling"))
	AActor* CurrentPatrolPoint;

	void MoveToNextPatrolPoint();


	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	 UFUNCTION()
	void ResetOrientation();

	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChange(EAIState NewState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
