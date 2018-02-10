#include "Features.h"
#include "Definitions.h"
#include "Entity.h"
#include "Interfaces.h"
#include "Settings.h"
#include "Math.h"

bool CAimbot::ValidTarget(CBaseEntity* Entity)
{
	CBaseEntity* LocalPlayer = Interfaces::EntityList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	if (!Entity || Entity == nullptr)
		return false;
	if (Entity->GetDormant())
		return false;
	if (Entity->GetTeam() == LocalPlayer->GetTeam() || Entity->GetTeam() == Hostage)
		return false;
	if (Entity->GetClientClass()->m_ClassID != 35)
		return false;
	if (Entity->GetHealth() <= 0)
		return false;
	if (Entity->GetGunGameImmunity())
		return false;

	return true;
}

int CAimbot::GetBestTarget(CUserCmd* pCmd, Vector &vPosition)
{
	float Fov = Settings.Aimbot.Fov;
	int iTempTarget = -1;
	CBaseEntity* LocalPlayer = Interfaces::EntityList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	for (auto i = 0; i <= Interfaces::EntityList->GetHighestEntityIndex(); i++)
	{
		CBaseEntity* Entity = Interfaces::EntityList->GetClientEntity(i);
		if (this->ValidTarget(Entity))
		{
			QAngle qTempTarget = g_Math.CalcAngle(LocalPlayer->GetEyePosition(), Entity->GetEyePosition());
			Vector Position;
			bool Autowall; 
			if (Settings.Aimbot.AimbotMode == 1) 
				Autowall = this->GetBestHitbox(Entity, Position);
			else
			{
				Position = Entity->GetBonePositionB(Settings.Aimbot.Bone);
				if (g_pAutowall->GetDamage(Position) >= Settings.Aimbot.AutowallDamage)
					Autowall = true;
			}
			QAngle LocalAngles;
			Interfaces::Engine->GetViewAngles(LocalAngles);
			float fTempFov = g_Math.GetFov(LocalAngles, qTempTarget);
			if (fTempFov < Fov && ((g_pAutowall->GetDamage(Position) >= Settings.Aimbot.AutowallDamage && Autowall && Settings.Aimbot.EntityChecks == AUTOWALL)
					|| this->ShouldShoot(Entity) && Settings.Aimbot.EntityChecks == VISIBLE))
			{
				Fov = fTempFov;
				iTempTarget = i;
				vPosition = Position;
			}
		}
	}
	return iTempTarget;
}

bool CAimbot::ShouldShoot(CBaseEntity* Entity)
{
	CBaseEntity* LocalPlayer = Interfaces::EntityList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	Ray_t ray;
	trace_t tr;
	ray.Init(LocalPlayer->GetEyePosition(), Entity->GetBonePositionB(8));
	CTraceFilter filter;
	filter.pSkip = LocalPlayer;

	Interfaces::EngineTrace->TraceRay(ray, CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX, &filter, &tr);

	if (tr.m_pEnt == Entity && this->CanShoot())
		return true;

	return false;
}

bool CAimbot::CanShoot()
{
	CBaseEntity* LocalPlayer = Interfaces::EntityList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	float flServerTime = (float)LocalPlayer->GetTickBase() * Interfaces::GlobalVarsBase->interval_per_tick;
	float flNextPrimaryAttack = LocalPlayer->GetWeapon()->GetNextPrimaryAttack();

	bool BulletTime = true;

	if (flNextPrimaryAttack > flServerTime)
		BulletTime = false;
	return BulletTime;
}