#include "Features.h"
#include "Definitions.h"
#include "Entity.h"
#include "Interfaces.h"
#include "Settings.h"
#include "Math.h"
#include "FindPattern.h"

void CMisc::DoMisc_CreatemovePreAimbot(CUserCmd* pCmd, bool &bSendPacket)
{
	if (Settings.Misc.Bunnyhop)
		this->Bunnyhop(pCmd);
	if (Settings.Misc.AutoStrafe == 1)
		this->NormalAutoStrafe(pCmd);
	if (Settings.Misc.AutoStrafe == 2)
		this->SilentAutoStrafe(pCmd);
	if (Settings.Misc.AutoStrafe == 3)
		this->RageAutoStrafe(pCmd);
}

void CMisc::DoMisc_CreatemovePostAimbot(CUserCmd* pCmd, bool &bSendPacket)
{
	if (Settings.Misc.FakeLag)
		this->FakeLag(pCmd, bSendPacket);
}

void CMisc::DoMisc_BeginFrame()
{
	if (Settings.Misc.NameSpam)
		this->SpamName("GetpGooseHookWareTuxBaitGang.cc.pl.net.us.xyz.team");
	if (Settings.Misc.NameStealer)
		this->NameStealer();
}
CMisc* g_pMisc = new CMisc;