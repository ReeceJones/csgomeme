#pragma once
#include "Enums.h"
#include "Structs.h"
class IMaterialVar;
class ITexture;
class IMaterialProxy;
class Vector;
typedef __int16					int16;
typedef unsigned __int16		uint16;
typedef __int32					int32;
typedef unsigned __int32		uint32;
typedef __int64					int64;
typedef unsigned __int64		uint64;
typedef uint64 VertexFormat_t;
struct MaterialPropertyTypes_t;

class IMaterial
{
public:
	virtual const char *	GetName() const = 0;
	virtual const char *	GetTextureGroupName() const = 0;

	virtual PreviewImageRetVal_t GetPreviewImageProperties(int *width, int *height, ImageFormat *imageFormat, bool* isTranslucent) const = 0;

	virtual PreviewImageRetVal_t GetPreviewImage(unsigned char *data, int width, int height, ImageFormat imageFormat) const = 0;
	virtual int				GetMappingWidth() = 0;
	virtual int				GetMappingHeight() = 0;

	virtual int				GetNumAnimationFrames() = 0;

	virtual bool			InMaterialPage(void) = 0;
	virtual	void			GetMaterialOffset(float *pOffset) = 0;
	virtual void			GetMaterialScale(float *pScale) = 0;
	virtual IMaterial		*GetMaterialPage(void) = 0;

	virtual IMaterialVar *	FindVar(const char *varName, bool *found, bool complain = true) = 0;

	virtual void			IncrementReferenceCount(void) = 0;
	virtual void			DecrementReferenceCount(void) = 0;

	inline void AddRef() { IncrementReferenceCount(); }
	inline void Release() { DecrementReferenceCount(); }

	virtual int 			GetEnumerationID(void) const = 0;

	virtual void			GetLowResColorSample(float s, float t, float *color) const = 0;

	virtual void			RecomputeStateSnapshots() = 0;

	virtual bool			IsTranslucent() = 0;

	virtual bool			IsAlphaTested() = 0;

	virtual bool			IsVertexLit() = 0;

	virtual VertexFormat_t	GetVertexFormat() const = 0;

	virtual bool			HasProxy(void) const = 0;

	virtual bool			UsesEnvCubemap(void) = 0;

	virtual bool			NeedsTangentSpace(void) = 0;

	virtual bool			NeedsPowerOfTwoFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool			NeedsFullFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;

	virtual bool			NeedsSoftwareSkinning(void) = 0;

	virtual void			AlphaModulate(float alpha) = 0;
	virtual void			ColorModulate(float r, float g, float b) = 0;

	virtual void			SetMaterialVarFlag(MaterialVarFlags_t flag, bool on) = 0;
	virtual bool			GetMaterialVarFlag(MaterialVarFlags_t flag) = 0;

	virtual void			GetReflectivity(Vector& reflect) = 0;

	virtual bool			GetPropertyFlag(MaterialPropertyTypes_t type) = 0;

	virtual bool			IsTwoSided() = 0;

	virtual void			SetShader(const char *pShaderName) = 0;

	virtual int				GetNumPasses(void) = 0;

	virtual int				GetTextureMemoryBytes(void) = 0;

	virtual void			Refresh() = 0;

	virtual bool			NeedsLightmapBlendAlpha(void) = 0;

	virtual bool			NeedsSoftwareLighting(void) = 0;

	virtual int				ShaderParamCount() const = 0;
	virtual IMaterialVar	**GetShaderParams(void) = 0;

	virtual bool			IsErrorMaterial() const = 0;

	virtual void			Unused() = 0;

	virtual float			GetAlphaModulation() = 0;
	virtual void			GetColorModulation(float *r, float *g, float *b) = 0;

	virtual bool			IsTranslucentUnderModulation(float fAlphaModulation = 1.0f) const = 0;

	virtual IMaterialVar *	FindVarFast(char const *pVarName, unsigned int *pToken) = 0;

	virtual void			SetShaderAndParams(void *pKeyValues) = 0;
	virtual const char *	GetShaderName() const = 0;

	virtual void			DeleteIfUnreferenced() = 0;

	virtual bool			IsSpriteCard() = 0;

	virtual void			CallBindProxy(void *proxyData) = 0;

	virtual void			RefreshPreservingMaterialVars() = 0;

	virtual bool			WasReloadedFromWhitelist() = 0;

	virtual bool			SetTempExcluded(bool bSet, int nExcludedDimensionLimit) = 0;

	virtual int				GetReferenceCount() const = 0;
};