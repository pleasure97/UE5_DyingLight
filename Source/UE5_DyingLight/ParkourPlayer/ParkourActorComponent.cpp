// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/ParkourActorComponent.h"
#include "GameFramework/Character.h"


// Sets default values for this component's properties
UParkourActorComponent::UParkourActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UParkourActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UParkourActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UParkourActorComponent::ClimbTrace(ACharacter* Actor, FVector& Start, FVector& Middle, FVector& Last, bool Sussess)
{
	UKismetSystemLibrary* Trace;
	TArray<AActor*>ignore;
	FHitResult HitResult;
	ignore.Add(Actor);
	enum EDrawDebugTrace::Type Setting = EDrawDebugTrace::ForDuration;
	const FVector TraceVector = Actor->GetActorLocation() + FVector(0, 0, 80);
	for (int i = 0; i < 5; i++)
	{
		//Trace->SphereTraceSingle(GetWorld(), ActorLocation + (ActorLocation.UpVector * (i*50)), ActorLocation + (ActorLocation.UpVector * (i*50) + (ForwardVector * 100), TraceTypeQuery1, false, ignore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
		Trace->LineTraceSingle(GetWorld(), TraceVector + FVector(0,0,(i * 10)), TraceVector + FVector(0, 0, (i * 10)) + (50 * Actor->GetActorForwardVector()), TraceTypeQuery1, false, ignore, Setting, HitResult, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
		if (!HitResult.bBlockingHit)
		{
			GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Blue, "HitBreak");
			Trace->SphereTraceSingle(GetWorld(), HitResult.TraceEnd + (HitResult.Location.UpVector * 20), HitResult.TraceEnd + (HitResult.Location.UpVector * 80), 10, TraceTypeQuery1, false, ignore, Setting, HitResult, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
			if (!HitResult.bBlockingHit)
			{
				Trace->SphereTraceSingle(GetWorld(), HitResult.TraceEnd, HitResult.TraceEnd + (HitResult.Location.UpVector * -100), 10, TraceTypeQuery1, false, ignore, Setting, HitResult, true, FLinearColor::Blue, FLinearColor::Green, 5.0f);
				if (HitResult.bBlockingHit)
				{
					Start = Actor->GetActorLocation();
					Middle = FVector(Start.X, Start.Y, HitResult.Location.Z - 7.3);
					Last = HitResult.Location;
					Sussess = true;
				}
				else
				{
					Sussess = false;
				}
				break;
			}
		}
	}
}

