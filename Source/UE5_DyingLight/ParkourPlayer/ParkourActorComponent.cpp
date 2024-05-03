// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/ParkourActorComponent.h"




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

void UParkourActorComponent::ClimbTrace(ACharacter* CharacterRef, FVector & Start, FVector & Middle, FVector & Last, bool& Success, float Radius)
{
	UKismetSystemLibrary* Trace;
	TArray<AActor*>ignore;
	FHitResult HitResult;
	ignore.Add(CharacterRef);
	const FVector TraceVector = CharacterRef->GetActorLocation() + FVector(0, 0, 80);
	for (int i = 0; i < 5; i++)
	{
		//Trace->SphereTraceSingle(GetWorld(), ActorLocation + (ActorLocation.UpVector * (i*50)), ActorLocation + (ActorLocation.UpVector * (i*50) + (ForwardVector * 100), TraceTypeQuery1, false, ignore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
		Trace->LineTraceSingle(GetWorld(), TraceVector + FVector(0, 0, (i * 10)), TraceVector + FVector(0, 0, (i * 10)) + (50 * CharacterRef->GetActorForwardVector()), TraceTypeQuery1, false, ignore, Setting, HitResult, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
		if (!HitResult.bBlockingHit)
		{
			GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Blue, "HitBreak");
			Trace->SphereTraceSingle(GetWorld(), HitResult.TraceEnd + (HitResult.Location.UpVector * 20), HitResult.TraceEnd + (HitResult.Location.UpVector * 80), 10, TraceTypeQuery1, false, ignore, Setting, HitResult, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
			if (!HitResult.bBlockingHit)
			{
				Trace->SphereTraceSingle(GetWorld(), HitResult.TraceEnd, HitResult.TraceEnd + (HitResult.Location.UpVector * -100), 10, TraceTypeQuery1, false, ignore, Setting, HitResult, true, FLinearColor::Blue, FLinearColor::Green, 5.0f);
				if (HitResult.bBlockingHit)
				{
					Success = true;
					FVector LocRadius = Radius * (HitResult.Normal * -1.0f);

					CharacterRef->SetActorLocation(HitResult.Location + FVector(LocRadius.X, LocRadius.Y, -115.0f));
				}
				else
				{
					Success = false;
				}
				break;
			}
		}
	}
}



void UParkourActorComponent::ClimbOn(ACharacter* CharacterRef, FVector ActionValue ,bool& CanHanging, float& HangingValue)
{
	UKismetSystemLibrary* Trace;
	TArray<AActor*>ignore;
	FHitResult HitResult;
	ignore.Add(CharacterRef);
	if (CanHanging)
	{
		// Hanging 조건문 활성화시 수행을 위한 캐릭터 무브먼트 설정
		CharacterRef->GetCharacterMovement()->MaxFlySpeed = 100.0f;
		CharacterRef->GetCharacterMovement()->BrakingFrictionFactor = 1000000000.0f;
		CharacterRef->GetCharacterMovement()->bOrientRotationToMovement = false;
		CharacterRef->GetCharacterMovement()->bUseControllerDesiredRotation = false;
		CharacterRef->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		// Hanging은 가능하지만 혹시 잡는 위치가 벽은 아닌지
		// 확인을 위한 트레이스 UpVector로 그려짐
		Trace->LineTraceSingle(GetWorld(),
			CharacterRef->GetActorLocation() + (CharacterRef->GetActorForwardVector() * 50) + FVector(0, 0, 160),
			CharacterRef->GetActorLocation() + (CharacterRef->GetActorForwardVector() * 50) + FVector(0, 0, 115),
			TraceTypeQuery1, false,
			ignore, Setting,
			HitResult, true,
			FColor::Red, FColor::Green, 5.0f
		);
		// 앞이 아직 벽이라서 Hanging이 여전히 수행 가능한지
		// 확인하기 위한 트레이스
		if (!HitResult.bBlockingHit)
		{
			Trace->LineTraceSingle(GetWorld(),
				CharacterRef->GetActorLocation(),
				CharacterRef->GetActorLocation() + (CharacterRef->GetActorForwardVector() * 50),
				TraceTypeQuery1, false,
				ignore, Setting,
				HitResult, true,
				FColor::Red, FColor::Green, 5.0f
			);
			HangingValue = ActionValue.X; // HaningBlendSpace에 방향 값을 주기 위한 변수
			CharacterRef->AddMovementInput(CharacterRef->GetActorRightVector(), ActionValue.X);
			FRotator ActorDirection = UKismetMathLibrary::MakeRotFromX(HitResult.Normal * -1.0f);
			CharacterRef->SetActorRotation(ActorDirection);
			// 정면에 그려지는 트레이스의 값에 따라
			// 정면에 잡을 벽이 없으면 캐릭터 움직임을 기본으로 설정
			if (!HitResult.bBlockingHit)
			{
				CanHanging = false;
				CharacterRef->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
				CharacterRef->GetCharacterMovement()->bOrientRotationToMovement = true;
			}
		}
		// 잡는 위치가 벽이지만 위에 잡는 위치가 벽이여서
		// 캐릭터 움직임 기본으로 설정
		else
		{
			CanHanging = false;
			CharacterRef->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			CharacterRef->GetCharacterMovement()->bOrientRotationToMovement = true;
		}
	}
}



void UParkourActorComponent::ClimbUp(ACPP_Parkouror* CharacterRef, bool& CanMove, bool& CanHanging)
{
	FVector ActorLocalVector = CharacterRef->GetActorLocation();
	UKismetSystemLibrary* Trace;
	const FRotator Rotation = CharacterRef->K2_GetActorRotation();
	const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0.);
	const FVector ForwardVector = YawRotation.Vector();
	const FVector TraceHitLocation;
	TArray<AActor*>ignore;
	FHitResult HitResult;
	ignore.Add(CharacterRef);
	const FVector TraceVector = ActorLocalVector + FVector(0, 0, 80);
	// 여전히 올라갈 수 있는 위치인지 확인하기 위해 검사하는 트레이스
	// 검사하면서 동작에 수행할 Vector값도 같이 넘겨준다 and 이벤트도 실행
	for (int i = 0; i < 5; i++)
	{
		//Trace->SphereTraceSingle(GetWorld(), ActorLocation + (ActorLocation.UpVector * (i*50)), ActorLocation + (ActorLocation.UpVector * (i*50) + (ForwardVector * 100), TraceTypeQuery1, false, ignore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
		Trace->LineTraceSingle(GetWorld(), TraceVector + FVector(0, 0, (i * 10)), TraceVector + FVector(0, 0, (i * 10)) + (ForwardVector * 50), TraceTypeQuery1, false, ignore, Setting, HitResult, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
		if (!HitResult.bBlockingHit)
		{
			GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Blue, "HitBreak");
			Trace->SphereTraceSingle(GetWorld(), HitResult.TraceEnd + (HitResult.Location.UpVector * 20), HitResult.TraceEnd + (HitResult.Location.UpVector * 80), 10, TraceTypeQuery1, false, ignore, Setting, HitResult, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
			if (!HitResult.bBlockingHit)
			{
				Trace->SphereTraceSingle(GetWorld(), HitResult.TraceEnd, HitResult.TraceEnd + (HitResult.Location.UpVector * -100), 10, TraceTypeQuery1, false, ignore, Setting, HitResult, true, FLinearColor::Blue, FLinearColor::Green, 5.0f);
				if (HitResult.bBlockingHit)
				{
					// 캐릭터한테 값 반환과 이벤트 실행 지시
					CharacterRef->StartParkour = ActorLocalVector;
					CharacterRef->MiddleParkour = FVector(ActorLocalVector.X, ActorLocalVector.Y, HitResult.Location.Z - 7.3);
					CharacterRef->LastParkour = HitResult.Location;
					CharacterRef->Warping();
					CanMove = false;
					CanHanging = false;
				}
				else
				{
					CanMove = true;
				}
				break;
			}
		}
	}
	// 캐릭터한테 값 반환과 이벤트 실행 지시 동문
	CharacterRef->StartParkour = ActorLocalVector;
	CharacterRef->MiddleParkour = FVector(ActorLocalVector.X, ActorLocalVector.Y, HitResult.Location.Z - 7.3);
	CharacterRef->LastParkour = HitResult.Location;
	CharacterRef->Warping();
}


