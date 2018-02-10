#pragma once
#include "InputSystem.h"
#include "Entity.h"
#include "Trace.h"
#include "Vector.h"
#include "Structs.h"
#include "Drawing.h"

extern bool SendPacket;
extern HFont ESPFont;

class CMisc
{
public:
	void DoMisc_CreatemovePreAimbot(CUserCmd* pCmd, bool &bSendPacket);
	void DoMisc_CreatemovePostAimbot(CUserCmd* pCmd, bool &bSendPacket);
	void DoMisc_BeginFrame();
private:
	void NormalAutoStrafe(CUserCmd* pCmd);
	void SilentAutoStrafe(CUserCmd* pCmd);
	void RageAutoStrafe(CUserCmd* pCmd);
	void Bunnyhop(CUserCmd* pCmd);
	void ChangeName(const char* name);
	void SpamName(const char* name);
	void NameStealer();
	void FakeLag(CUserCmd* pCmd, bool &bSendPacket);
}; extern CMisc* g_pMisc;

class CAimbot
{
public:
	void DoAimbot(CUserCmd* pCmd, bool &bSendPacket);
	void EnginePrediction(CUserCmd* pCmd);
	void ClampAngles(CUserCmd* pCmd);
	void AntiAim(CUserCmd* pCmd, bool &bSendPacket);
private:
	bool ValidTarget(CBaseEntity* Entity);
	int GetBestTarget(CUserCmd* pCmd, Vector &vPosition);
	void NoRecoil(CUserCmd* pCmd);
	bool ShouldShoot(CBaseEntity* Entity);
	bool CanShoot();
	void Stop(CUserCmd* pCmd);
	void Crouch(CUserCmd* pCmd);
	Vector GetHitboxPosition(CBaseEntity* Entity, int Hitbox);
	bool GetBestHitbox(CBaseEntity* Entity, Vector& Hitbox);
	float GetLagCompensation();
}; extern CAimbot* g_pAimbot;

class CVisuals
{
public:
	void DoVisuals_Createmove();
	void DoVisuals_PaintTraverse();
	void DoVisuals_OverrideView();
private:
	bool WorldToScreen(Vector& vOrigin, Vector& vScreen);
	void Glow();
	void DrawBox(CBaseEntity* Entity);
	void DrawName(CBaseEntity* Entity);
	void DrawWeapon(CBaseEntity* Entity);
	void DrawHealthBar(CBaseEntity* Entity);
	void DrawArmorBar(CBaseEntity* Entity);
	void ThirdPerson();
	int TopX, TopY, BottomX, BottomY;
}; extern CVisuals* g_pVisuals;
struct FireBulletData
{
	Vector src;
	trace_t enter_trace;
	Vector direction;
	CTraceFilter filter;
	float trace_length;
	float trace_length_remaining;
	float current_damage;
	int penetrate_count;
};

class CAutowall
{
public:
	float GetDamage(const Vector& point);
private:
	float GetHitgroupDamageMultiplier(int HitGroup);
	void ScaleDamage(int HitGroup, CBaseEntity* Entity, float ArmorRatio, float &CurrentDamage);
	bool TraceToExit(Vector &End, trace_t *TraceEnter, Vector Start, Vector Direcion, trace_t *TraceExit);
	bool HandleBulletPenetration(WeaponInfo_t* WeaponInfo, FireBulletData &data);
	bool SimulateFireBullet(CBaseCombatWeapon* pWeapon, FireBulletData &data);
}; extern CAutowall* g_pAutowall;

class CDrawing
{
public:
	void DrawCircle(float x, float y, float r, float s, Color color);
	void DrawString(HFont font, int x, int y, Color color, DWORD alignment, const char* msg, ...);
	void DrawStringUnicode(HFont font, int x, int y, Color color, bool bCenter, const wchar_t* msg, ...);
	void DrawRect(int x, int y, int w, int h, Color col);
	void DrawRectRainbow(int x, int y, int width, int height, float flSpeed, float &flRainbow);
	void DrawRectGradientHorizontal(int x, int y, int width, int height, Color color1, Color color2);
	void DrawPixel(int x, int y, Color col);
	void DrawOutlinedRect(int x, int y, int w, int h, Color col);
	void DrawOutlinedCircle(int x, int y, int r, Color col);
	void DrawLine(int x0, int y0, int x1, int y1, Color col);
	void DrawCorner(int iX, int iY, int iWidth, int iHeight, bool bRight, bool bDown, Color colDraw);
	void DrawPolygon(int count, Vertex_t* Vertexs, Color color);
	void DrawRoundedBox(int x, int y, int w, int h, int r, int v, Color col);
	bool ScreenTransform(const Vector &point, Vector &screen);
	int GetStringWidth(HFont font, const char* msg, ...);
}; extern CDrawing Drawing;