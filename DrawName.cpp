#include "Features.h"
#include "Settings.h"
#include "Entity.h"
#include "Interfaces.h"
#include "Util.h"

void CVisuals::DrawName(CBaseEntity* Entity)
{
	player_info_t info = Entity->GetPlayerInfo();
	Drawing.DrawString(ESPFont, (this->TopX + this->BottomX) / 2, this->TopY - 7, Color(255, 255, 255), FONT_CENTER, info.name);
}

void CVisuals::DrawWeapon(CBaseEntity* Entity)
{
	auto Weapon = Entity->GetWeapon();
	if (!Weapon) 
		return;
	int Max = Entity->GetWeapon()->GetMaxAmmo();
	int Current = Entity->GetWeapon()->GetCurrentAmmo();
	Drawing.DrawString(ESPFont, (this->TopX + this->BottomX) / 2, this->BottomY + 11, Color(255, 255, 255), FONT_CENTER, "%s (%i / %i)", Weapon->GetWeaponName().c_str(), Current, Max);

	//CBaseEntity* LocalPlayer = Interfaces::EntityList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	//Vector LocalPos = LocalPlayer->GetOrigin();
	//Vector EntityPos = Entity->GetOrigin();
	//Vector Delta = LocalPos - EntityPos;
	//float Y = Delta.y * Delta.y;
	//float X = Delta.x * Delta.x;
	//float Dist = sqrt(X + Y);
	//float DistFinal = floorf(Dist);
	//Drawing.DrawString(ESPFont, this->BottomX, this->TopY, Color(255, 255, 255), FONT_LEFT, "%i", (int)DistFinal);
}