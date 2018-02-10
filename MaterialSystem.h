#pragma once
#include "IMaterial.h"
#include "Util.h"
#include <string>
#include <sstream>
#include "KeyValues.h"

typedef unsigned short MaterialHandle_t;
class IMaterialSystem
{
public:
	IMaterial* CreateMaterial(std::string type, std::string texture, bool ignorez, bool nofog, bool model, bool nocull, bool halflambert, bool wireframe)
	{
		std::stringstream materialData;
		materialData << "\"" + type + "\"\n"
			"{\n"
			"\t\"$basetexture\" \"" + texture + "\"\n"
			"\t\"$ignorez\" \"" + std::to_string(ignorez) + "\"\n"
			"\t\"$nofog\" \"" + std::to_string(nofog) + "\"\n"
			"\t\"$model\" \"" + std::to_string(model) + "\"\n"
			"\t\"$nocull\" \"" + std::to_string(nocull) + "\"\n"
			"\t\"$halflambert\" \"" + std::to_string(halflambert) + "\"\n"
			"\t\"$wireframe\" \"" + std::to_string(wireframe) + "\"\n"
			"}\n" << std::flush;

		std::string materialName = "custom_" + std::to_string(std::rand() % 10 + 999991);
		KeyValues* keyValues = new KeyValues(materialName.c_str());

		g_pUtil->InitKeyValues(keyValues, type.c_str());
		g_pUtil->LoadFromBuffer(keyValues, materialName.c_str(), materialData.str().c_str(), nullptr, NULL, nullptr);
		typedef IMaterial*(__thiscall* OriginalFn)(void*, const char *pMaterialName, KeyValues *pVMTKeyValues);
		IMaterial* createdMaterial = g_pUtil->CallVFunc<OriginalFn>(this, 83)(this, materialName.c_str(), keyValues);

		createdMaterial->IncrementReferenceCount();
		return createdMaterial;
	}

	IMaterial* FindMaterial(char const* pMaterialName, const char* pTextureGroupName, bool complain = true, const char* pComplainPrefix = nullptr)
	{
		typedef IMaterial* (*oFindMaterial)(void*, char const*, const char*, bool, const char*);
		return g_pUtil->CallVFunc<oFindMaterial>(this, 84)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
	}

	MaterialHandle_t FirstMaterial()
	{
		typedef MaterialHandle_t(*oFirstMaterial)(void*);
		return g_pUtil->CallVFunc<oFirstMaterial>(this, 86)(this);
	}

	MaterialHandle_t NextMaterial(MaterialHandle_t h)
	{
		typedef MaterialHandle_t(*oNextMaterial)(void*, MaterialHandle_t);
		return g_pUtil->CallVFunc<oNextMaterial>(this, 87)(this, h);
	}

	MaterialHandle_t InvalidMaterial()
	{
		typedef MaterialHandle_t(*oInvalidMaterial)(void*);
		return g_pUtil->CallVFunc<oInvalidMaterial>(this, 88)(this);
	}

	IMaterial* GetMaterial(MaterialHandle_t h)
	{
		typedef IMaterial* (*oGetMaterial)(void*, MaterialHandle_t);
		return g_pUtil->CallVFunc<oGetMaterial>(this, 89)(this, h);
	}
};