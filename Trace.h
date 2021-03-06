#pragma once

#include "Vector.h"
#include "Structs.h"
#include "Enums.h"
#include "Entity.h"

class VectorAligned : public Vector
{
public:
	VectorAligned() {}

	VectorAligned(const Vector &vec)
	{
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
	}

	float w;
};

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY, TRACE_ENTITIES_ONLY, TRACE_EVERYTHING_FILTER_PROPS,
	TRACE_FILTERSKY
};

struct Ray_t
{
	Ray_t() { }

	VectorAligned		m_Start;
	VectorAligned		m_Delta;
	VectorAligned		m_StartOffset;
	VectorAligned		m_Extents;
	const matrix3x4_t	*m_pWorldAxisTransform;
	bool				m_IsRay;
	bool				m_IsSwept;

	void Init(Vector vecStart, Vector vecEnd)
	{
		m_Delta = VectorAligned(vecEnd - vecStart);
		m_IsSwept = (m_Delta.LengthSqr() != 0);
		m_Extents.Zero();
		m_pWorldAxisTransform = NULL;
		m_IsRay = true;
		m_StartOffset.Zero();
		m_Start = vecStart;
	}
};

struct cplane_t
{
	Vector	normal;
	float	dist;
	byte	type;
	byte	signbits;
	byte	pad[2];
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(CBaseEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}
	virtual TraceType_t	GetTraceType()
	{
		return TRACE_EVERYTHING;
	}
	void* pSkip;
};

class CTraceFilter : public ITraceFilter
{
public:
	virtual bool ShouldHitEntity(CBaseEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}

	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}
	void* pSkip;
};

class CTraceFilterSkipTwoEntities : public ITraceFilter
{
public:
	CTraceFilterSkipTwoEntities(void *pPassEnt1, void *pPassEnt2)
	{
		pPassEntity1 = pPassEnt1;
		pPassEntity2 = pPassEnt2;
	}

	virtual bool ShouldHitEntity(CBaseEntity *pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pPassEntity1 || pEntityHandle == pPassEntity2);
	}

	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	void *pPassEntity1;
	void *pPassEntity2;
};
class IHandleEntity;
typedef bool(*ShouldHitFunc_t)(IHandleEntity *pHandleEntity, int contentsMask);

class CTraceFilterSimple : public CTraceFilter
{
public:
	CTraceFilterSimple(const IHandleEntity *passentity, int collisionGroup, ShouldHitFunc_t pExtraShouldHitCheckFn = NULL);
	virtual bool ShouldHitEntity(IHandleEntity *pHandleEntity, int contentsMask);
	virtual void SetPassEntity(const IHandleEntity *pPassEntity) { m_pPassEnt = pPassEntity; }
	virtual void SetCollisionGroup(int iCollisionGroup) { m_collisionGroup = iCollisionGroup; }

	const IHandleEntity *GetPassEntity(void) { return m_pPassEnt; }

private:
	const IHandleEntity *m_pPassEnt;
	int m_collisionGroup;
	ShouldHitFunc_t m_pExtraShouldHitCheckFunction;

};
class CSimpleTraceFilter : public ITraceFilter
{
public:
	CSimpleTraceFilter(PVOID pEnt)
	{
		m_pPassEnt = pEnt;
	}

	virtual bool ShouldHitEntity(IHandleEntity *pHandleEntity, int contentsMask)
	{
		return pHandleEntity != m_pPassEnt;
	}

	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	PVOID m_pPassEnt;
};
class IClientUnknown : public IHandleEntity
{
public:
	virtual PVOID GetCollideable() = 0;
	virtual PVOID GetClientNetworkable() = 0;
	virtual PVOID GetClientRenderable() = 0;
	virtual PVOID GetIClientEntity() = 0;
	virtual CBaseEntity *GetBaseEntity() = 0;
	virtual PVOID GetClientThinkable() = 0;
	virtual void *class1(void) = 0;
	virtual void *class2(void) = 0;
};
class CTraceFilterNoPlayer : public CTraceFilter
{
public:
	CTraceFilterNoPlayer() {}
	virtual bool ShouldHitEntity(IHandleEntity *pServerEntity, int contentsMask)
	{
		IClientUnknown *pUnk = static_cast<IClientUnknown*>(pServerEntity);
		CBaseEntity *pEnt = pUnk->GetBaseEntity();
		return !(pEnt->GetTeam() > 0);
	}
};
class CBaseTrace
{
public:
	Vector			startpos;
	Vector			endpos;
	cplane_t		plane;

	float			fraction;

	int				contents;
	unsigned short	dispFlags;

	bool			allsolid;
	bool			startsolid;

	CBaseTrace() {}
};

struct csurface_t
{
	const char*		name;
	short			surfaceProps;
	unsigned short	flags;
};

class CGameTrace : public CBaseTrace
{
public:
	bool                    DidHitWorld() const;
	bool                    DidHitNonWorldEntity() const;
	int                     GetEntityIndex() const;
	bool                    DidHit() const;
	bool					IsVisible() const;

public:

	float                   fractionleftsolid;
	csurface_t              surface;
	int                     hitgroup;
	short                   physicsbone;
	unsigned short          worldSurfaceIndex;
	CBaseEntity*            m_pEnt;
	int                     hitbox;

	CGameTrace() { }

private:
	CGameTrace(const CGameTrace& vOther);
};

typedef CGameTrace trace_t;

