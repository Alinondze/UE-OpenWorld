
#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"



class UHealthBarComponent;
class AAIController;
class UPawnSensingComponent;

UCLASS()
class MYPROJECT4_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	
	AEnemy();

    virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigatir, AActor* DamageCause)override;
	virtual void Destroyed() override;

	/*HitInterface*/
    virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	/*HitInterface*/
private:
	

	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere, Category = Combat)
	double  CombatRadius = 1000.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	double  AttackRadius = 150.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	double AcceptanceRadius = 50.f;
	/*
	* Navigation
	*/
	UPROPERTY()
	AAIController* EnemyController;

	UPROPERTY(EditInstanceOnly,Category = "AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere)
	double  PatrolRadius = 100.f;

	FTimerHandle PatrolTimer;
	void PatrolTimerFinisher();

	UPROPERTY(EditAnywhere,Category="AI Navigation")
	float PatrolWaitMin = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMax = 10.f;

	/**AI behavior **/
	void InitializeEnemy();
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatrolling();
	void ChaseTarget();
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsChasing();
	bool IsInsideAttackRadius();
	bool IsAttacking();
	bool IsDead();
	bool IsEngaged();
	void ClearPatrolTimer();
	void CheckCombatTarget();
	void CheckPatrolTarget();
	void SpawnDefaultWeapon();

	/*Combat*/
	void StartAttackTimer();
	void ClearAttackTimer();
	AActor* ChoosePatrolTarget();

	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMin = 0.5f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMax = 1.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float PatrollingSpeed = 125.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float ChasingSpeed = 300.f;

    UPROPERTY(EditAnywhere,Category = Combat )
	float DeathLifeSpan = 8.f;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(EditAnywhere,Category = Combat )
	TSubclassOf<class ASoul> SoulClass;
protected:
	
	virtual void BeginPlay() override;

	

	/* ABaseCharacter*/
	virtual void Die_Implementation() override;
	void SpawnSoul();
    virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void HandleDamage(float DamageAmount) override;
	virtual void AttackEnd() override;
	/* ABaseCharacter*/

	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);

	//Callback for OnPawnSeen in UPawnSensingComponent
	UFUNCTION()
	void PawnSeen(APawn* PawnSeen); 

	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;

	

};
