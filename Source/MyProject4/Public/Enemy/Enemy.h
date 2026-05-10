
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
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigatir, AActor* DamageCause)override;
	virtual void Destroyed() override;
private:
	

	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	

	UPROPERTY()
	AActor* CombatTarget;

	UPROPERTY(EditAnywhere)
	double  CombatRadius = 500.f;

	UPROPERTY(EditAnywhere)
	double  AttackRadius = 150.f;

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
	float WaitMin = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float WaitMax = 10.f;

	/**AI behavior **/
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

	/*Combat*/
	void StartAttackTimer();
	void ClearAttackTimer();

	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMin = 0.5f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMax = 1.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float PatrollingSpeed = 125.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float ChasingSpeed = 300.f;

	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeapon> WeaponClass;
protected:
	
	virtual void BeginPlay() override;

	virtual void Die() override;

	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	void CheckCombatTarget();
	void CheckPatrolTarget();
	AActor* ChoosePatrolTarget();
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void HandleDamage(float DamageAmount) override;
	virtual int32 PlayDeathMontage() override;

	UPROPERTY(EditAnywhere,Category = Combat )
	float DeathLifeSpan = 8.f;
	UFUNCTION()
	void PawnSeen(APawn* PawnSeen);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EDeathPose> DeathPose;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;
public:	
	
	

};
