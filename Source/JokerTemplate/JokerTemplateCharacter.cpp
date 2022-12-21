// Copyright Epic Games, Inc. All Rights Reserved.

#include "JokerTemplateCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "MedBag.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AJokerTemplateCharacter

AJokerTemplateCharacter::AJokerTemplateCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;
	HealthComponent = CreateDefaultSubobject<UHealth>(TEXT("HealthComponent"));

	
		Volume = CreateDefaultSubobject<UBoxComponent>(TEXT("Volume"));
		Volume->SetupAttachment(GetRootComponent());
		Volume->InitBoxExtent(FVector(10.f, 10.f, 10.f));
		Volume->SetCollisionResponseToAllChannels(ECR_Overlap);
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f; // The camera follows at this distance behind the character	
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	//Volume->OnComponentBeginOverlap.AddDynamic(this, &AJokerTemplateCharacter::OnVolumeBeginOverlap);
	//Volume->OnComponentEndOverlap.AddDynamic(this, &AJokerTemplateCharacter::OnVolumeEndOverlap);
}
void AJokerTemplateCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	Volume->SetRelativeLocation(FVector(0));
}
	



//////////////////////////////////////////////////////////////////////////
// Input

void AJokerTemplateCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Heal", IE_Pressed, this, &AJokerTemplateCharacter::StartHealing);
	PlayerInputComponent->BindAction("Damage", IE_Pressed, this, &AJokerTemplateCharacter::StartDamage);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AJokerTemplateCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AJokerTemplateCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AJokerTemplateCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AJokerTemplateCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AJokerTemplateCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AJokerTemplateCharacter::TouchStopped);
}

void AJokerTemplateCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AJokerTemplateCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AJokerTemplateCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AJokerTemplateCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AJokerTemplateCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AJokerTemplateCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AJokerTemplateCharacter::StartDamage()
{
	HealthComponent->TakeDamage(20.00f);
}


void AJokerTemplateCharacter::StartHealing()
{
	HealthComponent->TakeHeal(15.00f);
}

//void AJokerTemplateCharacter::OnVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{	UE_LOG(LogTemp, Warning, TEXT("OVERLAP OCCURED"));
//	if (Cast<AMedBag>(OtherActor))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("OVERLAP OCCURED"));
//		OtherActor->Destroy();
//	}
//}

//void AJokerTemplateCharacter::OnVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	if (Cast<AMedBag>(OtherActor))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("OVERLAP OCCURED"));
//	}
//}