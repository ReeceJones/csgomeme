#include "Offsets.h"
#include "FindPattern.h"

sOffsets offsets;
void COffsets::GetOffsets()
{
	offsets.m_fFlags = NetvarManager->GetOffset("DT_CSPlayer", "m_fFlags");
	offsets.D3DDevice = **reinterpret_cast<DWORD**>(FindPattern->IDA("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 0x1);
	offsets.m_aimPunchAngle = NetvarManager->GetOffset("DT_BasePlayer", "m_aimPunchAngle");
	offsets.m_flFlashDuration = NetvarManager->GetOffset("DT_CSPlayer", "m_flFlashDuration");
	offsets.m_iGlowIndex = offsets.m_flFlashDuration + 0x18;
	offsets.GlowManager = *(DWORD*)(FindPattern->IDA("client.dll", "F3 ?? ?? ?? ?? ?? ?? ?? 83 C8 01 C7 05") + 0x4);
	offsets.m_bDormant = 0xe9;
	offsets.m_iTeamNum = NetvarManager->GetOffset("DT_CSPlayer", "m_iTeamNum");
	offsets.m_vecViewOffset = NetvarManager->GetOffset("DT_CSPlayer","m_vecViewOffset[0]");
	offsets.m_vecOrigin = NetvarManager->GetOffset("DT_BasePlayer", "m_vecOrigin");
	offsets.m_iHealth = NetvarManager->GetOffset("DT_CSPlayer", "m_iHealth");
	offsets.m_nWritableBones = NetvarManager->GetOffset("DT_CSPlayer", "m_nForceBone") + 0x20;
	offsets.m_dwOcclusionArray = *(uintptr_t*)(FindPattern->IDA("client.dll", "A1 ? ? ? ? 83 EC 30 56 57 8B F9") + 0x1);
	offsets.m_bDidCheckForOcclusion = *(uintptr_t*)(FindPattern->IDA("client.dll", "A1 ? ? ? ? 83 EC 30 56 57 8B F9") + 0xE); 
	offsets.m_bGunGameImmunity = NetvarManager->GetOffset("DT_CSPlayer", "m_bGunGameImmunity");
	offsets.m_nTickBase = NetvarManager->GetOffset("DT_CSPlayer", "m_nTickBase");
	offsets.m_hActiveWeapon = NetvarManager->GetOffset("DT_CSPlayer", "m_hActiveWeapon");
	offsets.m_flNextPrimaryAttack = NetvarManager->GetOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
	offsets.m_viewPunchAngle = NetvarManager->GetOffset("DT_BasePlayer", "m_viewPunchAngle");
	offsets.m_ArmorValue = NetvarManager->GetOffset("DT_CSPlayer", "m_ArmorValue");
	offsets.m_bHasHelmet = NetvarManager->GetOffset("DT_CSPlayer", "m_bHasHelmet");
	offsets.m_iWeaponID = NetvarManager->GetOffset("DT_WeaponCSBase", "m_fAccuracyPenalty") + 0x30;
	offsets.m_lifeState = NetvarManager->GetOffset("DT_CSPlayer", "m_lifeState"); 
	offsets.m_nMoveType = 0x258;
	offsets.m_flLowerBodyYawTarget = NetvarManager->GetOffset("DT_CSPlayer", "m_flLowerBodyYawTarget");
	offsets.m_hActiveWeapon = NetvarManager->GetOffset("DT_BaseCombatCharacter", "m_hActiveWeapon");
	offsets.m_vecVelocity = NetvarManager->GetOffset("DT_CSPlayer", "m_vecVelocity[0]");
	offsets.m_angRotation = NetvarManager->GetOffset("DT_CSPlayer", "m_angRotation"); //0x128
	offsets.m_angEyeAngles = NetvarManager->GetOffset("DT_CSPlayer", "m_angEyeAngles");
	offsets.CAM_Think = FindPattern->IDA("client.dll", "55 8B EC 83 E4 F8 81 EC C0");
	offsets.deadflag = NetvarManager->GetOffset("DT_CSPlayer", "deadflag");
	offsets.m_bScoped = NetvarManager->GetOffset("DT_CSPlayer", "m_bIsScoped");
	offsets.m_iItemIDHigh = NetvarManager->GetOffset("DT_BaseCombatWeapon", "m_iItemIDHigh");
	offsets.m_iItemIDLow = NetvarManager->GetOffset("DT_BaseCombatWeapon", "m_iItemIDLow");
	offsets.m_iAccountID = NetvarManager->GetOffset("DT_BaseCombatWeapon", "m_iAccountID");
	offsets.m_iEntityQuality = NetvarManager->GetOffset("DT_BaseCombatWeapon", "m_iEntityQuality");
	offsets.m_OriginalOwnerXuidLow = NetvarManager->GetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
	offsets.m_OriginalOwnerXuidHigh = NetvarManager->GetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
	offsets.m_iItemDefinitionIndex = NetvarManager->GetOffset("DT_BaseAttributableItem", "m_iItemDefinitionIndex");
	offsets.m_nFallbackPaintKit = NetvarManager->GetOffset("DT_BaseCombatWeapon", "m_nFallbackPaintKit");
	offsets.m_nFallbackSeed = NetvarManager->GetOffset("DT_BaseCombatWeapon", "m_nFallbackSeed");
	offsets.m_flFallbackWear = NetvarManager->GetOffset("DT_BaseCombatWeapon", "m_flFallbackWear");
	offsets.m_nFallbackStatTrak = NetvarManager->GetOffset("DT_BaseCombatWeapon", "m_nFallbackStatTrak");
	offsets.m_nModelIndex = NetvarManager->GetOffset("DT_BasePlayer", "m_nModelIndex");
	offsets.m_iViewModelIndex = NetvarManager->GetOffset("DT_BaseCombatWeapon", "m_iViewModelIndex");
	offsets.m_iWorldModelIndex = NetvarManager->GetOffset("DT_BaseCombatWeapon", "m_iWorldModelIndex");
	offsets.m_iClip1 = NetvarManager->GetOffset("DT_BaseCombatWeapon", "m_iClip1");
	offsets.m_flSimulationTime = NetvarManager->GetOffset("DT_CSPlayer", "m_flSimulationTime");
	offsets.LoadFromBufferEx = FindPattern->IDA("client.dll", "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04");
	offsets.InitKeyValuesEx = FindPattern->IDA("client.dll", "55 8B EC 51 33 C0 C7 45");
}
COffsets* pOffsets = new COffsets;
CFindPattern* FindPattern = new CFindPattern;