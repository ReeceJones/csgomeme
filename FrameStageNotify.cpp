#include "Hooks.h"
#include "Interfaces.h"
#include "Definitions.h"
#include "Settings.h"
#include "Features.h"
#include "NetvarManager.h"
#include "FindPattern.h"
#include "PaintKit.h"

typedef unsigned short MaterialHandle_t;
void RecvProxy_Viewmodel(const CRecvProxyData* pData, void* pStruct, void* pOut)
{
	int iModel = pData->m_Value.m_Int;

	auto nCTDefault = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl");
	auto nBayonet = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
	auto nGut = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_gut.mdl");
	auto nTDefault = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl");
	auto nButterfly = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
	auto nFlip = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_flip.mdl");
	auto nGunGame = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_gg.mdl");
	auto nFalchion = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
	auto nM9Bayonet = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
	auto nKarambit = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
	auto nHuntsman = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl");
	auto nDagger = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_push.mdl");
	auto nBowie = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");

	CBaseEntity *localPlayer = static_cast<CBaseEntity*>(Interfaces::EntityList->GetClientEntity(Interfaces::Engine->GetLocalPlayer()));
	if (localPlayer)
	{
		if (localPlayer->GetWeapon())
		{
			if (iModel == nBayonet
				|| iModel == nButterfly
				|| iModel == nCTDefault
				|| iModel == nTDefault
				|| iModel == nFlip
				|| iModel == nGut
				|| iModel == nHuntsman
				|| iModel == nGunGame
				|| iModel == nKarambit
				|| iModel == nM9Bayonet
				|| iModel == nFalchion)
			{
				iModel = nHuntsman;
			}
		}
	}

	*static_cast<int*>(pOut) = iModel;
}

FrameStageNotifyFn FrameStageNotify_Original;
void __stdcall Hooks::FrameStageNotify_Hooked(ClientFrameStage_t CurrentStage)
{
	QAngle aimold;
	QAngle viewold;
	QAngle* aim = NULL;
	QAngle* view = NULL;
	if (Interfaces::Engine->IsConnected() && Interfaces::Engine->IsInGame())
	{

		if (FRAME_RENDER_START)
		{
			CBaseEntity* LocalPlayer = Interfaces::EntityList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
			if (!LocalPlayer)
				return;

			bool ThirdPerson = *reinterpret_cast<bool*>(reinterpret_cast<DWORD>(Interfaces::Input) + 0xa5);
			if (ThirdPerson)
			{
				*reinterpret_cast<QAngle*>(reinterpret_cast<DWORD>(LocalPlayer) + offsets.deadflag + 0x4) = Settings.Visuals.VisualAngle;
			}


			auto nCTDefault = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl");
			auto nBayonet = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
			auto nGut = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_gut.mdl");
			auto nTDefault = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl");
			auto nButterfly = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
			auto nFlip = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_flip.mdl");
			auto nGunGame = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_gg.mdl");
			auto nFalchion = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
			auto nM9Bayonet = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
			auto nKarambit = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
			auto nHuntsman = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl");
			auto nDagger = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_push.mdl");
			auto nBowie = Interfaces::ModelInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");

			for (int i = Interfaces::EntityList->GetHighestEntityIndex(); i >= 0; --i)
			{
				CBaseEntity* Entity = Interfaces::EntityList->GetClientEntity(i);
				if (Entity)
				{
					Interfaces::Client->GetAllClasses();
					ULONG hOwnerEntity = *reinterpret_cast<PULONG>(DWORD(Entity) + 0x148);

					CBaseEntity* Owner = Interfaces::EntityList->GetClientEntityFromHandle(hOwnerEntity);

					if (Owner && Owner == LocalPlayer)
					{
						std::string WeaponString = Interfaces::ModelInfo->GetModelName(Entity->GetModel());

						if ((!(WeaponString.find("models/weapons", 0) != std::string::npos))
							|| (WeaponString.find("c4_planted", 0) != std::string::npos)
							|| (WeaponString.find("thrown", 0) != std::string::npos)
							|| (WeaponString.find("smokegrenade", 0) != std::string::npos)
							|| (WeaponString.find("flashbang", 0) != std::string::npos)
							|| (WeaponString.find("fraggrenade", 0) != std::string::npos)
							|| (WeaponString.find("molotov", 0) != std::string::npos)
							|| (WeaponString.find("decoy", 0) != std::string::npos)
							|| (WeaponString.find("incendiarygrenade", 0) != std::string::npos)
							|| (WeaponString.find("ied", 0) != std::string::npos)
							|| (WeaponString.find("w_eq_", 0) != std::string::npos))
							continue;
						CBaseCombatWeapon* Weapon = reinterpret_cast<CBaseCombatWeapon*>(Entity);
						NetvarManager->HookProp("DT_BaseViewModel", "m_nModelIndex", RecvProxy_Viewmodel);
						player_info_t LocalInfo = LocalPlayer->GetPlayerInfo();
						auto WeaponID = *reinterpret_cast<int*>(reinterpret_cast<DWORD>(Weapon) + offsets.m_iItemDefinitionIndex);

						if (WeaponID == 59
							|| WeaponID == 500
							|| WeaponID == 42
							|| WeaponID == 507
							|| WeaponID == 506
							|| WeaponID == 508
							|| WeaponID == 509
							|| WeaponID == 515
							|| WeaponID == 516
							|| WeaponID == 505
							|| WeaponID == 512)
						{
							*reinterpret_cast<int*>(DWORD(Weapon) + offsets.m_nModelIndex) = nHuntsman;
							*reinterpret_cast<int*>(DWORD(Weapon) + offsets.m_iViewModelIndex) = nHuntsman;
							*reinterpret_cast<int*>(DWORD(Weapon) + offsets.m_iWorldModelIndex) = nHuntsman + 1;
							*reinterpret_cast<int*>(DWORD(Weapon) + offsets.m_iItemDefinitionIndex) = 509;
							*reinterpret_cast<int*>(DWORD(Weapon) + offsets.m_iEntityQuality) = 3;
							*reinterpret_cast<int*>(DWORD(Weapon) + offsets.m_iEntityQuality) = 0;
							*reinterpret_cast<int*>(DWORD(Weapon) + offsets.m_nFallbackStatTrak) = 0;
							*reinterpret_cast<int*>(DWORD(Weapon) + offsets.m_nFallbackPaintKit) = 570;
							*reinterpret_cast<int*>(DWORD(Weapon) + offsets.m_nFallbackSeed) = 0;
							*reinterpret_cast<float*>(DWORD(Weapon) + offsets.m_flFallbackWear) = 0.0000001f;
						}

						*reinterpret_cast<int*>(DWORD(Weapon) + offsets.m_OriginalOwnerXuidHigh) = LocalInfo.xuidhigh;
						*reinterpret_cast<int*>(DWORD(Weapon) + offsets.m_OriginalOwnerXuidLow) = LocalInfo.xuidlow;
						*reinterpret_cast<int*>(DWORD(Weapon) + offsets.m_iAccountID) = LocalInfo.xuidlow;
						*reinterpret_cast<int*>(DWORD(Weapon) + offsets.m_iItemIDHigh) = -1;
					}
				}
			}




			if (LocalPlayer->GetHealth() > 0)
			{
				if (Settings.Visuals.NoVisRecoil)
				{
					aim = reinterpret_cast<QAngle*>(DWORD(LocalPlayer) + offsets.m_aimPunchAngle);
					view = reinterpret_cast<QAngle*>(DWORD(LocalPlayer) + offsets.m_viewPunchAngle);
					aimold = *aim;
					viewold = *view;
					*aim = *aim * Settings.Visuals.AimPunchFactor;
					*view = QAngle(0, 0, 0);
				}
			}
		}
	}

	if (FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		if (Settings.Aimbot.Resolver)
		{
			for (int i = 1; i < Interfaces::Engine->GetMaxClients(); ++i)
			{
				CBaseEntity* Entity = Interfaces::EntityList->GetClientEntity(i);
				CBaseEntity* LocalPlayer = Interfaces::EntityList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
				if (!Entity
					|| Entity == LocalPlayer
					|| Entity->GetDormant()
					|| !Entity->GetAlive()
					|| Entity->GetTeam() == LocalPlayer->GetTeam())
					continue;
				Entity->GetEyeAngles()->y = Entity->GetLowerBodyYawTarget(); //Entity->GetHeadRotation()->y
			}
		}
	}

	FrameStageNotify_Original(CurrentStage);
	if (aim && view && Settings.Visuals.NoVisRecoil)
	{
		*aim = aimold;
		*view = viewold;
	}
}