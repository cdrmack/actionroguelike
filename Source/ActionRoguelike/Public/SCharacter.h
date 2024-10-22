#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class USInteractComponent;
class UAnimMontage;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USInteractComponent> InteractComp;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Move;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Jump;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Dash;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_LookMouse;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_UltimateAttack;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Interact;
	
	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> MagicProjectileClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> UltimateProjectileClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> DashProjectileClass;
	
	UPROPERTY(EditAnywhere, Category="Attack")
	TObjectPtr<UAnimMontage> AttackAnim;

	UPROPERTY(EditAnywhere, Category="Attack")
	float PrimaryAttackDelay = 0.18f; // Animation Notifies or Animation Events would be better
	
protected:
	virtual void BeginPlay() override;

private:
	void Move(const FInputActionInstance& Instance);
	void LookMouse(const FInputActionValue& InputValue);

	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);
	void PrimaryAttack();
	void PrimaryAttack_Timer();
	void UltimateAttack();
	void UltimateAttack_Timer();
	void Dash();
	void Dash_Timer();
	
	FTimerHandle ProjectileAttackTimerHandle;
};
