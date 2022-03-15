// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLaunchPad.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComp->SetBoxExtent(FVector(200.0f, 200.0f, 20.0f));
	RootComponent = BoxComp;

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::HandleOverlap);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200.0f, 200.0f, 20.0f);
	DecalComp->SetupAttachment(RootComponent);
}

void AFPSLaunchPad::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);
	if (MyPawn == nullptr) {
		return;
	}

	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);

	if (OtherCharacter) {
		FRotator LaunchDirection = GetActorRotation();
		LaunchDirection.Pitch += LaunchAngle;
		FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

		OtherCharacter->LaunchCharacter(LaunchVelocity, true, true);
	}
}




