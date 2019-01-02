#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"

UCLASS()
class GOLDENEGG_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAvatar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// New! These 2 new member function declarations 
	// they will be used to move our player around! 
	void MoveForward(float amount);
	void MoveRight(float amount);

	void Yaw(float amount);
	void Pitch(float amount);

	float Hp;
	float MaxHp;
};