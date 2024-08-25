#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_Damageable.generated.h"

UINTERFACE(MinimalAPI)
class UI_Damageable : public UInterface
{
	GENERATED_BODY()
};

class DATADRIVENFPT_API II_Damageable
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void I_TakeDamage(float Damage);
};
