#include "Hooks.h"
#include "Interfaces.h"
#include "Enums.h"
#include "Settings.h"

DrawModelExecuteFn DrawModelExecute_Original;

IMaterial* Visible_Textured;
IMaterial* Visible_Flat;
IMaterial* Visible_WireFramed;

IMaterial* IgnoreZ_Textured;
IMaterial* IgnoreZ_Flat;
IMaterial* IgnoreZ_WireFramed;

void ForceMaterial(IMaterial* material, Color color) {
	if (material != nullptr) {
		Interfaces::RenderView->SetColorModulation(color.Base());
		Interfaces::ModelRender->ForcedMaterialOverride(material);
	}
}

IMaterial* GetBestMaterial(bool IgnoreZ)
{
	if (IgnoreZ) {
		if (Settings.Visuals.IgnoreZStyle == CHAMSTYLE_TEXTURED)
			return IgnoreZ_Textured;
		else if (Settings.Visuals.IgnoreZStyle == CHAMSTYLE_FLAT)
			return IgnoreZ_Flat;
		else if (Settings.Visuals.IgnoreZStyle == CHAMSTYLE_WIREFRAME)
			return IgnoreZ_WireFramed;
	}
	else {
		if (Settings.Visuals.VisualStyle == CHAMSTYLE_TEXTURED)
			return Visible_Textured;
		else if (Settings.Visuals.VisualStyle == CHAMSTYLE_FLAT)
			return Visible_Flat;
		else if (Settings.Visuals.VisualStyle == CHAMSTYLE_WIREFRAME)
			return Visible_WireFramed;
	}
}

void __stdcall Hooks::DrawModelExecute_Hooked(void* context, void* state, const ModelRenderInfo_t& info, matrix3x4_t* pCustomBoneToWorld) {
	CBaseEntity* LocalPlayer = Interfaces::EntityList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	HookManagers::ModelRender->UnHook();
	if (Interfaces::Engine->IsInGame() && Interfaces::Engine->IsConnected() && LocalPlayer) {
		if (info.pModel) {
			std::string modelName = Interfaces::ModelInfo->GetModelName(info.pModel);

			if (modelName.find("models/player") != std::string::npos && Settings.Visuals.Chams && Settings.Visuals.Enabled) {
				CBaseEntity* ModelEntity = static_cast<CBaseEntity*>(Interfaces::EntityList->GetClientEntity(info.entity_index));
				if (ModelEntity && ModelEntity->GetAlive() && !ModelEntity->GetDormant()) {
					Color RenderColorVisible;
					Color RenderColorIgnoreZ;

					switch (ModelEntity->GetTeam())
					{
					case Terrorists:
						RenderColorVisible = Color(Settings.Visuals.ChamsColorTerroristVisual[0] * 255,
							Settings.Visuals.ChamsColorTerroristVisual[1] * 255,
							Settings.Visuals.ChamsColorTerroristVisual[2] * 255);
						RenderColorIgnoreZ = Color(Settings.Visuals.ChamsColorTerroristIgnoreZ[0] * 255,
							Settings.Visuals.ChamsColorTerroristIgnoreZ[1] * 255,
							Settings.Visuals.ChamsColorTerroristIgnoreZ[2] * 255);
						break;
					case CounterTerrorists:
						RenderColorVisible = Color(Settings.Visuals.ChamsColorCounterTerroristVisual[0] * 255,
							Settings.Visuals.ChamsColorCounterTerroristVisual[1] * 255,
							Settings.Visuals.ChamsColorCounterTerroristVisual[2] * 255);
						RenderColorIgnoreZ = Color(Settings.Visuals.ChamsColorCounterTerroristIgnoreZ[0] * 255,
							Settings.Visuals.ChamsColorCounterTerroristIgnoreZ[1] * 255,
							Settings.Visuals.ChamsColorCounterTerroristIgnoreZ[2] * 255);
						break;
					}

					if (Settings.Visuals.IgnoreZ)
					{
						ForceMaterial(GetBestMaterial(true), RenderColorIgnoreZ);
						Interfaces::ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);
					}

					ForceMaterial(GetBestMaterial(false), RenderColorVisible);
					Interfaces::ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);
				}
			}
		}
	}
	Interfaces::ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);
	Interfaces::ModelRender->ForcedMaterialOverride(nullptr);
	HookManagers::ModelRender->ReHook();
}