#include "Features.h"
#include "Convar.h"
#include "Interfaces.h"


void CMisc::ChangeName(const char* name)
{
	static ConVar* nameConvar = Interfaces::Cvar->FindVar("name");
	*(int*)((DWORD)&nameConvar->fnChangeCallback + 0xC) = NULL;
	nameConvar->SetValue(name);
}

void CMisc::SpamName(const char* name)
{
	static bool bSwitch = false;
	if (bSwitch)
		this->ChangeName("GetpAyyGooseHookWareTuxBaitGang.cc.pl.net.us.xyz.club.org.team");
	else
		this->ChangeName("\xADGetpAyyGooseHookWareTuxBaitGang.cc.pl.net.us.xyz.club.org.team");
	bSwitch = !bSwitch;
}

void CMisc::NameStealer()
{
	CBaseEntity* LocalPlayer = Interfaces::EntityList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	if (LocalPlayer == nullptr || !LocalPlayer)
		return;

	for (int i = 0; i < Interfaces::EntityList->GetHighestEntityIndex(); i++)
	{
		CBaseEntity* Entity = Interfaces::EntityList->GetClientEntity(i);
		if (Entity == nullptr || !Entity)
			return;
		player_info_t EntityInfo = Entity->GetPlayerInfo();

		char NameBuffer[42069] = "\n\xAD\xAD\xAD";
		strcat(NameBuffer, EntityInfo.name);
		this->ChangeName(NameBuffer);
	}
}