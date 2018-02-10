#include "Features.h"
#include "Definitions.h"
#include "Entity.h"
#include "Interfaces.h"
#include "Settings.h"
#include "GlowManager.h"

CVisuals* g_pVisuals = new CVisuals;

void CVisuals::DoVisuals_OverrideView()
{
	if (Settings.Visuals.ThirdPerson > 0.f)
		this->ThirdPerson();
	else
	{
		static QAngle vecAngles;
		Interfaces::Engine->GetViewAngles(vecAngles);
		Interfaces::Input->m_fCameraInThirdPerson = false;
		Interfaces::Input->m_vecCameraOffset = Vector(vecAngles.x, vecAngles.y, 0);
	}
}

void CVisuals::DoVisuals_Createmove()
{
	if (Settings.Visuals.Glow)
		this->Glow();
}

void CVisuals::DoVisuals_PaintTraverse()
{
	CBaseEntity* LocalPlayer = Interfaces::EntityList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	for (int i = 0; i < Interfaces::EntityList->GetHighestEntityIndex(); i++)
	{
		CBaseEntity* Entity = Interfaces::EntityList->GetClientEntity(i);
		if (Entity == nullptr || !Entity->GetAlive() || Entity->GetDormant() || Entity->GetHealth() == 0)
			continue;
		if (Entity == LocalPlayer && Settings.Visuals.ThirdPerson == false)
			continue;

		this->TopX = 0;
		this->TopY = 0;
		this->BottomX = 0;
		this->BottomY = 0;
		Vector vHead = Entity->GetBonePositionB(8);
		Vector vOrigin = Entity->GetOrigin();
		vHead.x = vOrigin.x;
		Vector vHeadScreen, vOriginScreen;
		if (this->WorldToScreen(vOrigin, vOriginScreen) && this->WorldToScreen(vHead, vHeadScreen))
		{
			int EntityHeight = vOriginScreen.y - vHeadScreen.y;
			int EntityWidth = EntityHeight / Settings.Visuals.BoxWidth;
			this->TopX = vHeadScreen.x - (EntityWidth / 2);
			this->TopY = vHeadScreen.y - ((EntityHeight / 2.2) / 3);
			this->BottomX = vOriginScreen.x + (EntityWidth / 2);
			this->BottomY = vOriginScreen.y + 2;

			if (Settings.Visuals.DrawPlayerBoxes)
				this->DrawBox(Entity);
			if (Settings.Visuals.DrawName)
				this->DrawName(Entity);
			if (Settings.Visuals.DrawWeapon)
				this->DrawWeapon(Entity);
			if (Settings.Visuals.DrawHealthBar == 1)
				this->DrawHealthBar(Entity);
			if (Settings.Visuals.DrawArmorBar == 1)
				this->DrawArmorBar(Entity);
		}
	}
}