// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/Component/GrapplingRopeComponent.h"
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

		Delegate.BindUFunction(this, TEXT("OnSunPower"));

		GrappleShootTimeline->AddInterpFloat(ObjectFinder.Object, Delegate);
		GrappleShootTimeline->SetPlayRate(0.5f);
		GrappleShootTimeline->SetLooping(true);
	}
	
}


// Called when the game starts
void UGrapplingRopeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor* Owner = GetOwner(); 

	if (Owner)
	{
		GrappleRope = NewObject<UCableComponent>(Owner, UCableComponent::StaticClass(), TEXT("GrappleRope"));
		if (GrappleRope)
		{
			GrappleRope->RegisterComponent(); 
			GrappleRope->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale)); 

			GrappleRope->SetRelativeLocation(FVector(0.f, 0.f, 40.f));
			GrappleRope->EndLocation = FVector(0.f, 0.f, 40.f);
			GrappleRope->CableLength = 0.f;
			GrappleRope->CableWidth = 8.f;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to setup grapple rope in GrapplingRopeComponent::BeginPlay()"))
		}
		
		// To be implemented
		GrappleShootTimeline = NewObject<UTimelineComponent>(Owner, )
	}

	UCurveFloat* InterpSpeed = Cast<UCurveFloat>(StaticLoadObject(UCurveFloat::StaticClass(), nullptr, TEXT("/Script/Engine.CurveFloat'/Game/Blueprints/Curves/Curve_GrappleShootTimeline.Curve_GrappleShootTimeline'")));

}


// Called every frame
void UGrapplingRopeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGrapplingRopeComponent::GrappleHook()
{
	AActor* Owner = GetOwner(); 

	ensure(Owner); 

	// Check for surface 
	if (CanGrappleHook)
	{
		CanGrappleHook = false;
		GrappleHookEnabled = true;

		UCameraComponent* FollowCamera = Cast<UCameraComponent>(Owner->GetComponentByClass(UCameraComponent::StaticClass()));

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

			// To be implemented 
			// ShootGrappleHook
			/*GrappleRope->SetVisibility(true);
			FMath::VInterpTo(GrappleRope->GetComponentLocation(), HookLocation, UGameplayStatics::GetWorldDeltaSeconds(), )*/


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

