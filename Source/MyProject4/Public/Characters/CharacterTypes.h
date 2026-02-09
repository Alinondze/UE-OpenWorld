#pragma once

UENUM(BlueprintType)
enum class  ECharacterState : uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_EquippedOneHandedWeapon UMETA(DisplayName = "Equipped One-Handed Weapon"),
	ECS_EquippedTwoHandldWeapon UMETA(DisplayName = "Equipped Two-Handed Weapon")
};