#include "SCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "SMagicProjectile.h"
#include "SInteractComponent.h"

ASCharacter::ASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(GetRootComponent());

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	InteractComp = CreateDefaultSubobject<USInteractComponent>(TEXT("InteractComp"));
	
	SpringArmComp->bUsePawnControlRotation = true; // camera reacts to both: vertical and horizontal mouse movement
	bUseControllerRotationYaw = false; // allows to "orbit" horizontally around the character (see face etc.)
	GetCharacterMovement()->bOrientRotationToMovement = true; // rotate the character toward the direction of acceleration
}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	const APlayerController* PlayerController = GetController<APlayerController>();
	const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMappingContext, 0);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ASCharacter::Move);
	EnhancedInputComponent->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ASCharacter::Jump);
	EnhancedInputComponent->BindAction(Input_LookMouse, ETriggerEvent::Triggered, this, &ASCharacter::LookMouse);
	EnhancedInputComponent->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, &ASCharacter::PrimaryAttack);
	EnhancedInputComponent->BindAction(Input_UltimateAttack, ETriggerEvent::Triggered, this, &ASCharacter::UltimateAttack);
	EnhancedInputComponent->BindAction(Input_Interact, ETriggerEvent::Triggered, this->InteractComp.Get(), &USInteractComponent::PrimaryInteract);
}

void ASCharacter::Move(const FInputActionInstance& Instance)
{
	// Coordinate system:
	// X - forward
	// Y - right
	// Z - up
	
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;

	// Enhanced Input Mapping Context:
	// W (forward): YXZ
	// S (backward): YXZ + Negate
	// A (left): Negate
	// D (right)
	
	const FVector2D AxisValue = Instance.GetValue().Get<FVector2D>();
	
	// forward/backward
	AddMovementInput(ControlRotation.Vector(), AxisValue.Y);

	// left/right
	const FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, AxisValue.X);
}

void ASCharacter::LookMouse(const FInputActionValue& InputValue)
{
	const FVector2D AxisValue = InputValue.Get<FVector2D>();

	AddControllerYawInput(AxisValue.X);
	AddControllerPitchInput(AxisValue.Y);
}

void ASCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	FHitResult Hit;
	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + (GetControlRotation().Vector() * 5000);
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	
	if (GetWorld()->LineTraceSingleByProfile(Hit, StartLocation, EndLocation, "Projectile", CollisionQueryParams))
	{
		EndLocation = Hit.ImpactPoint;
	}
	
	const FVector RightHandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FRotator AdjustedRotation = FRotationMatrix::MakeFromX(EndLocation - RightHandLocation).Rotator();
	const FTransform SpawnTransform = FTransform(AdjustedRotation,RightHandLocation);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;
	
	GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTransform, SpawnParameters);
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(ProjectileAttackTimerHandle, this, &ASCharacter::PrimaryAttack_Timer, PrimaryAttackDelay);
}

void ASCharacter::PrimaryAttack_Timer()
{
	SpawnProjectile(MagicProjectileClass);
}

void ASCharacter::UltimateAttack()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(ProjectileAttackTimerHandle, this, &ASCharacter::UltimateAttack_Timer, PrimaryAttackDelay);
}

void ASCharacter::UltimateAttack_Timer()
{
	SpawnProjectile(UltimateProjectileClass);
}
