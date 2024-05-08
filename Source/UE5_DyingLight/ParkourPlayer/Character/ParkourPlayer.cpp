// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/Character/ParkourPlayer.h"

// Sets default values
AParkourPlayer::AParkourPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize a skeletal mesh compoennt and related anim blueprint 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	if (SkeletalMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMeshAsset.Object); 
	}
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, 0.f, -90.f)); 

	// Create a cable component 
	GrappleRope = CreateDefaultSubobject<UCableComponent>(TEXT("GrappleRope")); 
	GrappleRope->SetupAttachment(RootComponent); 
	GrappleRope->SetRelativeLocation(FVector(0.f, 0.f, 40.f)); 
	GrappleRope->EndLocation = FVector(0.f, 0.f, 40.f); 
	GrappleRope->CableLength = 0.f; 
	GrappleRope->CableWidth = 8.f; 

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
	
	// Create an AI Perception Stimuli Source Component
	AIPerceptionStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSource"));

	// Create a Motion Warping Component
	MotionWarping = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping")); 
}


// Called when the game starts or when spawned
void AParkourPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AParkourPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AParkourPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); 
}

float AParkourPlayer::ShootGrappleHook()
{
	return 0.0f;
}


