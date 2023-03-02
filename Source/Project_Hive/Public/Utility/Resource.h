// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Resource.generated.h"


/** Resources to buy things */
USTRUCT(BlueprintType)
struct FResource
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Gold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Wood;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Food;

	bool operator<=(const FResource& Other) const
	{
		return this->Gold <= Other.Gold && this->Wood <= Other.Wood && this->Food <= Other.Food;
	}

	FResource& operator+=(const FResource& Other)
	{
		this->Gold += Other.Gold;
		this->Wood += Other.Wood;
		this->Food += Other.Food;
		return *this;
	}

	FResource& operator-=(const FResource& Other)
	{
		this->Gold -= Other.Gold;
		this->Wood -= Other.Wood;
		this->Food -= Other.Food;
		return *this;
	}
};

