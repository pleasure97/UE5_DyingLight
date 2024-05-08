// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/Controller/ParkourPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Data/Input/BasicInputDataConfig.h"
#include "ParkourPlayer/Character/ParkourPlayer.h"
#include "Kismet/KismetSystemLibrary.h"

void AParkourPlayerController::BeginPlay()
{
}

void AParkourPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	const UBasicInputDataConfig* BasicInputDataConfig = GetDefault<UBasicInputDataConfig>();
	EnhancedInputComponent->BindAction(BasicInputDataConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(BasicInputDataConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
}

void AParkourPlayerController::Move(const FInputActionValue& InputActionValue)
{
	AParkourPlayer* ParkourPlayer = Cast<AParkourPlayer>(GetPawn()); 

	const FRotator& Rotation = GetControlRotation(); 
	const FRotator& YawRotation = FRotator(0.f, Rotation.Yaw, 0.); 

	const FVector& ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); 
	const FVector& RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); 

	const FVector& ActionValue = InputActionValue.Get<FVector>(); 


	if (ParkourPlayer->CanMove)
	{
		ParkourPlayer->AddMovementInput(ForwardVector, ActionValue.Y); 
	}
	
}

void AParkourPlayerController::GrappleRope(const FInputActionValue& InputActionValue)
{
	AParkourPlayer* ParkourPlayer = Cast<AParkourPlayer>(GetPawn());

	if (ParkourPlayer->CanGrappleHook)
	{
		ParkourPlayer->CanGrappleHook = false; 
		ParkourPlayer->GrappleHookEnabled = true;

		const FVector& Start = ParkourPlayer->GrappleRope->GetComponentLocation(); 
		const FVector& End = Start + ParkourPlayer->GetFollowCamera()->GetForwardVector() * ParkourPlayer->GrappleHookDistance; 

		TArray<AActor*> IgnoreActors; 

		FHitResult HitResult;

		const bool bHit = 
			UKismetSystemLibrary::LineTraceSingle(ParkourPlayer, Start, End, ETraceTypeQuery::TraceTypeQuery1, false, IgnoreActors, EDrawDebugTrace::ForDuration, HitResult, true);

		if (bHit)
		{
			ParkourPlayer->HookLocation = HitResult.Location; 

			// shoot grapple hook 
			ParkourPlayer->GrappleRope->SetVisibility(true); 



			ParkourPlayer->GrappleRope->SetWorldLocation(NewLocation); 
			ParkourPlayer->LaunchCharacter(FVector(0.f, 0.f, 500.f), true, true); 

			FTimerHandle Timer; 
			GetWorldTimerManager().SetTimer(Timer, 0.4f, false); 

			// reset grapple hook 


			GetWorldTimerManager().ClearTimer(Timer); 



		}
		else
		{
			// reset grapple hook 

		}


	}

}

void AParkourPlayerController::Slide(const FInputActionValue& InputActionValue)
{

}

void AParkourPlayerController::Mantle(const FInputActionValue& InputActionValue)
{

}

void AParkourPlayerController::LedgeClimb(const FInputActionValue& InputActionValue)
{
}


