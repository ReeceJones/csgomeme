#include "Features.h"
#include "Settings.h"
#include "Entity.h"
#include "Interfaces.h"
#include "Util.h"

void CVisuals::DrawBox(CBaseEntity* Entity)
{
	Color EntityColorTerrorist = Color(Settings.Visuals.BoxColorTerrorist[0] * 255, Settings.Visuals.BoxColorTerrorist[1] * 255, Settings.Visuals.BoxColorTerrorist[2] * 255);
	Color EntityColorCounterTerrorist = Color(Settings.Visuals.BoxColorCounterTerrorist[0] * 255, Settings.Visuals.BoxColorCounterTerrorist[1] * 255, Settings.Visuals.BoxColorCounterTerrorist[2] * 255);
	Color RenderColor;
	
	switch (Entity->GetTeam())
	{
	case Terrorists:
		RenderColor = EntityColorTerrorist;
		break;
	case CounterTerrorists:
		RenderColor = EntityColorCounterTerrorist;
		break;
	}/*
	Interfaces::Surface->DrawSetColor(RenderColor);
	Interfaces::Surface->DrawOutlinedRect(this->TopX, this->TopY, this->BottomX, this->BottomY);
	Interfaces::Surface->DrawSetColor(Color(0, 0, 0));
	Interfaces::Surface->DrawOutlinedRect(this->TopX - 1, this->TopY - 1, this->BottomX + 1, this->BottomY + 1);*/
	Drawing.DrawOutlinedRect(this->TopX, this->TopY, this->BottomX, this->BottomY, RenderColor);
	Drawing.DrawOutlinedRect(this->TopX - 1, this->TopY - 1, this->BottomX + 1, this->BottomY + 1, Color(0, 0, 0));
}

void CVisuals::DrawHealthBar(CBaseEntity* Entity)
{
	int Health = Entity->GetHealth();
	int Height = this->TopY - this->BottomY;
	int FixedLineHeight = Height - ((Height * Health) / 100);
	Drawing.DrawLine(this->TopX - 5, this->TopY - FixedLineHeight, this->TopX - 5, this->BottomY, Color(0, 255, 0));
	Drawing.DrawOutlinedRect(this->TopX - 6, this->TopY - 1, this->TopX - 3, this->BottomY + 1, Color(0, 0, 0));
}

void CVisuals::DrawArmorBar(CBaseEntity* Entity)
{
	int Health = Entity->GetHealth();
	int Height = this->TopY - this->BottomY;
	int Armor = Entity->GetArmor();
	int FixedLineHeight = Height - ((Height * Armor) / 100);
	Drawing.DrawLine(this->BottomX + 4, this->TopY - FixedLineHeight, this->BottomX + 4, this->BottomY, Color(0, 100, 255));
	Drawing.DrawOutlinedRect(this->BottomX + 3, this->TopY - 1, this->BottomX + 6, this->BottomY + 1, Color(0, 0, 0));
}