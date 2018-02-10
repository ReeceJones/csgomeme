#include "Entity.h"
#include "Interfaces.h"

CBaseCombatWeapon* CBaseEntity::GetWeapon()
{
	DWORD weaponData = *(DWORD*)((DWORD)this + offsets.m_hActiveWeapon);
	return (CBaseCombatWeapon*)Interfaces::EntityList->GetClientEntityFromHandle(weaponData);
}

player_info_t CBaseEntity::GetPlayerInfo()
{
	player_info_t PlayerInfo;
	Interfaces::Engine->GetPlayerInfo(this->GetIndex(), &PlayerInfo);
	return PlayerInfo;
}