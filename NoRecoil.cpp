#include "Features.h"
#include "Definitions.h"
#include "Entity.h"
#include "Interfaces.h"
#include "Settings.h"

void CAimbot::NoRecoil(CUserCmd* pCmd)
{
	CBaseEntity* LocalPlayer = Interfaces::EntityList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	if (Settings.Aimbot.NoRecoil == 2)
	{	
		if (pCmd->buttons & IN_ATTACK)
		{
			pCmd->viewangles -= LocalPlayer->GetAimPunch() * 2.00f;
			pCmd->viewangles.Normalize();
		}
	}
	else if (Settings.Aimbot.NoRecoil == 1)
	{
		QAngle ViewAngle;
		QAngle Punch;
		static QAngle OldPunch;
		QAngle NewAngle;

		Interfaces::Engine->GetViewAngles(ViewAngle);
		Punch = LocalPlayer->GetAimPunch();
		NewAngle = ViewAngle - (Punch - OldPunch) * 2.f;
		Interfaces::Engine->SetViewAngles(NewAngle);
		OldPunch = Punch;
	}
}