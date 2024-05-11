// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/Component/GrapplingRopeComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UGrapplingRopeComponent::UGrapplingRopeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	GrappleShootTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("GrappleShootTimeline"));
	{
		static ConstructorHelpers::FObjectFinder<UCurveFloat> ObjectFinder(TEXT("/Script/Engine.CurveFloat'/Game/Blueprints/Curves/Curve_GrappleShootTimeline.Curve_GrappleShootTimeline'"));
		ensure(ObjectFinder.Object);

		FOnTimelineFloat Delegate;

		Delegate.BindUFunction(this, TEXT("ShootGrappleHook"));

		GrappleShootTimeline->AddInterpFloat(ObjectFinder.Object, Delegate);
	}

}
// Called when the game starts
void UGrapplingRopeComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner(); 
	ensure(Owner); 

	FollowCamera = Cast<UCameraComponent>(Owner->GetComponentByClass(UCameraComponent::StaticClass()));
	ensure(FollowCamera); 

	GrappleRope = Cast<UCableComponent>(Owner->GetComponentByClass(UCableComponent::StaticClass())); 
	ensure(GrappleRope); 
}


// Called every frame
void UGrapplingRopeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrapplingRopeComponent::GrappleHook(const FInputActionValue& Value)
{
	AActor* Owner = GetOwner(); 

	ensure(Owner); 

	// Check for surface 
	if (CanGrappleHook)
	{
		CanGrappleHook = false;
		GrappleHookEnabled = true;

		const FVector& Start = GrappleRope->GetComponentLocation();
		const FVector& End = Start + FollowCamera->GetForwardVector() * GrappleHookDistance;
		TArray<AActor*> IgnoreActors;
		FHitResult HitResult;

		const bool bHit =
			UKismetSystemLibrary::LineTraceSingle(Owner, Start, End, ETraceTypeQuery::TraceTypeQuery1, false, IgnoreActors, EDrawDebugTrace::ForDuration, HitResult, true);

		FTimerHandle TimerHandle;

		if (bHit)
		{
			HookLocation = HitResult.Location; 
			
			GrappleShootTimeline->PlayFromStart(); 
			
			ACharacter* OwnerCharacter = Cast<ACharacter>(Owner); 
			OwnerCharacter->LaunchCharacter(FVector(0.f, 0.f, 500.f), true, true); 
			
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
				{
					UE_LOG(LogTemp, Warning, TEXT("Delay in GrappleHook executed"));
				}, 0.2, false);
			
			FVector LaunchVelocity = (HookLocation - OwnerCharacter->GetActorLocation()) * 2.5f; 
			OwnerCharacter->LaunchCharacter(LaunchVelocity, false, false); 

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
				{
					UE_LOG(LogTemp, Warning, TEXT("Delay in GrappleHook executed again"));
				}, 0.4, false);

			// ResetGrappleHook
			GrappleRope->SetVisibility(false);
			GrappleHookEnabled = false;

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
				{
					UE_LOG(LogTemp, Warning, TEXT("Delay in GrappleHook executed"));
				}, 0.2, false);

			CanGrappleHook = true;
		}
		else
		{
			// ResetGrappleHook
			GrappleRope->SetVisibility(false); 
			GrappleHookEnabled = false; 

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
				{
					UE_LOG(LogTemp, Warning, TEXT("Delay in GrappleHook executed"));
				}, 0.2, false);

			CanGrappleHook = true; 
		}
	}
}

void UGrapplingRopeComponent::ShootGrappleHook(float InterpSpeed)
{
	GrappleRope->SetVisibility(true); 
	
	FVector NewLocation = FMath::VInterpTo(GrappleRope->GetComponentLocation(), HookLocation, UGameplayStatics::GetWorldDeltaSeconds(this), InterpSpeed); 

	GrappleRope->SetWorldLocation(NewLocation); 
}


