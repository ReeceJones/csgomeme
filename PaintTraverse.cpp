#include "Interfaces.h"
#include "Hooks.h"
#include "Features.h"
#include "Settings.h"
#include "Util.h"

PaintTraverseFn PaintTraverse_Original;
void __fastcall Hooks::PaintTraverse_Hooked(void* ecx, void* edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{

	auto cName = Interfaces::Panel->GetName(vguiPanel);
	//if (!strcmp(cName, "HudZoom")) //Fullscreen Root Panel
	if (!strcmp(cName, "Fullscreen Root Panel"))
	{
		if (Interfaces::Engine->IsInGame() && Interfaces::Engine->IsConnected() && !Interfaces::Engine->IsTakingScreenshot())
		{	
			CBaseEntity* LocalPlayer = Interfaces::EntityList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
			Interfaces::Surface->DrawSetColor(Color(0, 0, 0));
			if (LocalPlayer && LocalPlayer != nullptr && Settings.Visuals.Enabled)
				g_pVisuals->DoVisuals_PaintTraverse();
		}
	}
	PaintTraverse_Original(ecx, edx, vguiPanel, forceRepaint, allowForce); 
}