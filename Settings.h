#pragma once
#include <Windows.h>
#include "Vector.h"

class CSettings
{
public:
	struct
	{
		bool MenuOpened;
		bool FileOpened;
		struct
		{
			bool Save;
		} FileMenu;
	}Menu;

	struct
	{
		bool AntiUntrust = true;
		bool Enabled;
		int AimbotMode;
		int Bone;
		int EntityChecks;
		float AutowallDamage;
		bool AutoShoot;
		bool EnginePrediction;
		int Key;
		float Fov;
		bool SilentAim;
		int NoRecoil;
		bool AntiAim;
		int AntiAimYaw;
		int AntiAimPitch;
		bool LispY;
		bool LispX;
		bool AutoStop;
		bool AutoCrouch;
		bool HitchanceEnabled;
		int Hitchance;
		float SmoothX = 1.f;
		float SmoothY = 1.f;
		bool Resolver;
		bool LagCompensation;
	}Aimbot;
	struct
	{
		bool Bunnyhop;
		bool NameSpam;
		int AutoStrafe;
		bool NameStealer;
		bool FakeLag;
		int FakeLagAmount;
		char ConfigBuffer[MAX_PATH];
		bool ShowConfig;
	}Misc;
	struct
	{
		bool Enabled;
		bool Glow;
		float ViewModelFov = 68;
		bool NoVisRecoil;
		float AimPunchFactor;
		bool CustomPlayers;
		bool CustomGloves = true;
		bool DrawPlayerBoxes;
		float BoxWidth = 1.8f;
		bool DrawName;
		bool DrawWeapon;
		int DrawHealthBar;
		int DrawArmorBar;
		float GlowColorTerrorist[3] = { 1.f, 0.117f, 0.f };
		float GlowColorCounterTerrorist[3] = { 0.f, 0.615f, 1.f };
		float BoxColorTerrorist[3] = { 1.f, 0.117f, 0.f };
		float BoxColorCounterTerrorist[3] = { 0.f, 0.615f, 1.f };
		float ThirdPerson;
		QAngle VisualAngle;
		bool Chams;
		bool IgnoreZ;
		int VisualStyle;
		int IgnoreZStyle;
		float ChamsColorTerroristVisual[3] = { 1.f, 0.117f, 0.f };;
		float ChamsColorCounterTerroristVisual[3] = { 0.f, 0.615f, 1.f };
		float ChamsColorTerroristIgnoreZ[3] = { 1.f, 0.117f, 0.f };;
		float ChamsColorCounterTerroristIgnoreZ[3] = { 0.f, 0.615f, 1.f };
	}Visuals;
};
extern CSettings Settings;