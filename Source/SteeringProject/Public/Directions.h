#pragma once

UENUM(BlueprintType)
enum class EDirection : uint8 {
	North = 0	UMETA(DisplayName = "North"),
	East = 1	UMETA(DisplayName = "East"),
	South = 2   UMETA(DisplayName = "South"),
	West = 3	UMETA(DisplayName = "West"),
	None = 5	UMETA(DisplayName = "None")
};