/*
BodySlide and Outfit Studio
Copyright (C) 2017  Caliente & ousnius
See the included LICENSE file
*/

#pragma once

#include "BasicTypes.h"
#include "Objects.h"

enum BSShaderType : uint {
	SHADER_TALL_GRASS,
	SHADER_DEFAULT,
	SHADER_SKY = 10,
	SHADER_SKIN = 14,
	SHADER_WATER = 17,
	SHADER_LIGHTING30 = 29,
	SHADER_TILE = 32,
	SHADER_NOLIGHTING
};

enum BSLightingShaderPropertyShaderType : uint {
	Default,
	EnvironmentMap,
	GlowShader,
	Heightmap,
	FaceTint,
	SkinTint,
	HairTint,
	ParallaxOccMaterial,
	WorldMultitexture,
	WorldMap1,
	Unknown10,
	MultiLayerParallax,
	Unknown12,
	WorldMap2,
	SparkleSnow,
	WorldMap3,
	EyeEnvmap,
	Unknown17,
	WorldMap4,
	WorldLODMultitexture
};

class NiProperty : public NiObjectNET {
};

class NiShadeProperty : public NiProperty {
private:
	ushort flags = 0;

public:
	NiShadeProperty() {}
	NiShadeProperty(NiStream& stream);

	static constexpr const char* BlockName = "NiShadeProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);

	NiShadeProperty* Clone() { return new NiShadeProperty(*this); }
};

class NiSpecularProperty : public NiProperty {
private:
	ushort flags = 0;

public:
	NiSpecularProperty() {}
	NiSpecularProperty(NiStream& stream);

	static constexpr const char* BlockName = "NiSpecularProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);

	NiSpecularProperty* Clone() { return new NiSpecularProperty(*this); }
};

struct TexTransform {
	Vector2 translation;
	Vector2 tiling;
	float wRotation = 0.0f;
	uint transformType = 0;
	Vector2 offset;
};

struct TexDesc {
	BlockRef<NiSourceTexture> sourceRef;
	ushort flags = 0;
	bool hasTexTransform = false;
	TexTransform transform;

	void Get(NiStream& stream) {
		sourceRef.Get(stream);
		stream >> flags;
		stream >> hasTexTransform;

		if (hasTexTransform)
			stream >> transform;
	}

	void Put(NiStream& stream) {
		sourceRef.Put(stream);
		stream << flags;
		stream << hasTexTransform;

		if (hasTexTransform)
			stream << transform;
	}

	void GetChildRefs(std::set<int*>& refs) {
		refs.insert(&sourceRef.index);
	}
};

struct ShaderTexDesc {
	bool isUsed = false;
	TexDesc data;
	uint mapIndex = 0;

	void Get(NiStream& stream) {
		stream >> isUsed;

		if (isUsed) {
			data.Get(stream);
			stream >> mapIndex;
		}
	}

	void Put(NiStream& stream) {
		stream << isUsed;

		if (isUsed) {
			data.Put(stream);
			stream << mapIndex;
		}
	}

	void GetChildRefs(std::set<int*>& refs) {
		data.GetChildRefs(refs);
	}
};

class NiTexturingProperty : public NiProperty {
private:
	ushort flags = 0;
	uint textureCount = 0;

	bool hasBaseTex = false;
	TexDesc baseTex;

	bool hasDarkTex = false;
	TexDesc darkTex;

	bool hasDetailTex = false;
	TexDesc detailTex;

	bool hasGlossTex = false;
	TexDesc glossTex;

	bool hasGlowTex = false;
	TexDesc glowTex;

	bool hasBumpTex = false;
	TexDesc bumpTex;
	float lumaScale = 1.0f;
	float lumaOffset = 0.0f;
	Vector4 bumpMatrix;

	bool hasNormalTex = false;
	TexDesc normalTex;

	bool hasUnkTex = false;
	TexDesc unkTex;
	float unkFloat1 = 0.0f;

	bool hasDecalTex0 = false;
	TexDesc decalTex0;

	bool hasDecalTex1 = false;
	TexDesc decalTex1;

	bool hasDecalTex2 = false;
	TexDesc decalTex2;

	bool hasDecalTex3 = false;
	TexDesc decalTex3;

	uint numShaderTex = 0;
	std::vector<ShaderTexDesc> shaderTex;

public:
	NiTexturingProperty() {}
	NiTexturingProperty(NiStream& stream);

	static constexpr const char* BlockName = "NiTexturingProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);
	void GetChildRefs(std::set<int*>& refs);

	NiTexturingProperty* Clone() { return new NiTexturingProperty(*this); }
};

class NiVertexColorProperty : public NiProperty {
private:
	ushort flags = 0;

public:
	NiVertexColorProperty() {}
	NiVertexColorProperty(NiStream& stream);

	static constexpr const char* BlockName = "NiVertexColorProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);

	NiVertexColorProperty* Clone() { return new NiVertexColorProperty(*this); }
};

class NiDitherProperty : public NiProperty {
private:
	ushort flags = 0;

public:
	NiDitherProperty() {}
	NiDitherProperty(NiStream& stream);

	static constexpr const char* BlockName = "NiDitherProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);

	NiDitherProperty* Clone() { return new NiDitherProperty(*this); }
};

class NiFogProperty : public NiProperty {
private:
	ushort flags = 0;
	float fogDepth = 1.0f;
	Color3 fogColor;

public:
	NiFogProperty() {}
	NiFogProperty(NiStream& stream);

	static constexpr const char* BlockName = "NiFogProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);

	NiFogProperty* Clone() { return new NiFogProperty(*this); }
};

class NiWireframeProperty : public NiProperty {
private:
	ushort flags = 0;

public:
	NiWireframeProperty() {}
	NiWireframeProperty(NiStream& stream);

	static constexpr const char* BlockName = "NiWireframeProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);

	NiWireframeProperty* Clone() { return new NiWireframeProperty(*this); }
};

class NiZBufferProperty : public NiProperty {
private:
	ushort flags = 3;

public:
	NiZBufferProperty() {}
	NiZBufferProperty(NiStream& stream);

	static constexpr const char* BlockName = "NiZBufferProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);

	NiZBufferProperty* Clone() { return new NiZBufferProperty(*this); }
};

class NiShader : public NiProperty {
public:
	virtual bool IsSkinTint() { return false; }
	virtual bool IsSkinned() { return false; }
	virtual void SetSkinned(const bool enable) {}
	virtual bool IsDoubleSided() { return false; }
	virtual bool IsModelSpace() { return false; }
	virtual bool IsEmissive() { return false; }
	virtual bool HasSpecular() { return true; }
	virtual bool HasBacklight() { return false; }
	virtual uint GetShaderType() { return 0; }
	virtual void SetShaderType(const uint type) {}
	virtual Vector2 GetUVOffset() { return Vector2(); }
	virtual Vector2 GetUVScale() { return Vector2(1.0f, 1.0f); }
	virtual Vector3 GetSpecularColor() { return Vector3(); }
	virtual void SetSpecularColor(const Vector3& color) {}
	virtual float GetSpecularStrength() { return 0.0f; }
	virtual void SetSpecularStrength(const float strength) {}
	virtual float GetGlossiness() { return 0.0f; }
	virtual void SetGlossiness(const float gloss) {}
	virtual float GetEnvironmentMapScale() { return 0.0f; }
	virtual int GetTextureSetRef() { return 0xFFFFFFFF; }
	virtual void SetTextureSetRef(const int texSetRef) {}
	virtual Color4 GetEmissiveColor() { return Color4(); }
	virtual void SetEmissiveColor(const Color4& color) {}
	virtual float GetEmissiveMultiple() { return 0.0f; }
	virtual void SetEmissiveMultiple(const float emissive) {}
	virtual float GetAlpha() { return 1.0f; }
	virtual std::string GetWetMaterialName() { return std::string(); }
	virtual void SetWetMaterialName(const std::string& matName) {}
};

class BSShaderProperty : public NiShader {
public:
	ushort shaderFlags = 1;
	BSShaderType shaderType = SHADER_DEFAULT;
	uint shaderFlags1 = 0x82000000;
	uint shaderFlags2 = 1;
	float environmentMapScale = 1.0f;
	Vector2 uvOffset;
	Vector2 uvScale = Vector2(1.0f, 1.0f);

	void Get(NiStream& stream);
	void Put(NiStream& stream);

	uint GetShaderType();
	void SetShaderType(const uint type);
	bool HasSpecular();
	float GetEnvironmentMapScale();
	Vector2 GetUVOffset();
	Vector2 GetUVScale();
};

class WaterShaderProperty : public BSShaderProperty {
public:
	WaterShaderProperty() {}
	WaterShaderProperty(NiStream& stream);

	static constexpr const char* BlockName = "WaterShaderProperty";
	virtual const char* GetBlockName() { return BlockName; }

	WaterShaderProperty* Clone() { return new WaterShaderProperty(*this); }
};

class HairShaderProperty : public BSShaderProperty {
public:
	HairShaderProperty() {}
	HairShaderProperty(NiStream& stream);

	static constexpr const char* BlockName = "HairShaderProperty";
	virtual const char* GetBlockName() { return BlockName; }

	HairShaderProperty* Clone() { return new HairShaderProperty(*this); }
};

class DistantLODShaderProperty : public BSShaderProperty {
public:
	DistantLODShaderProperty() {}
	DistantLODShaderProperty(NiStream& stream);

	static constexpr const char* BlockName = "DistantLODShaderProperty";
	virtual const char* GetBlockName() { return BlockName; }

	DistantLODShaderProperty* Clone() { return new DistantLODShaderProperty(*this); }
};

class BSDistantTreeShaderProperty : public BSShaderProperty {
public:
	BSDistantTreeShaderProperty() {}
	BSDistantTreeShaderProperty(NiStream& stream);

	static constexpr const char* BlockName = "BSDistantTreeShaderProperty";
	virtual const char* GetBlockName() { return BlockName; }

	BSDistantTreeShaderProperty* Clone() { return new BSDistantTreeShaderProperty(*this); }
};

class TallGrassShaderProperty : public BSShaderProperty {
private:
	NiString fileName;

public:
	TallGrassShaderProperty() {}
	TallGrassShaderProperty(NiStream& stream);

	static constexpr const char* BlockName = "TallGrassShaderProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);

	TallGrassShaderProperty* Clone() { return new TallGrassShaderProperty(*this); }
};

class VolumetricFogShaderProperty : public BSShaderProperty {
public:
	VolumetricFogShaderProperty() {}
	VolumetricFogShaderProperty(NiStream& stream);

	static constexpr const char* BlockName = "VolumetricFogShaderProperty";
	virtual const char* GetBlockName() { return BlockName; }

	VolumetricFogShaderProperty* Clone() { return new VolumetricFogShaderProperty(*this); }
};

class BSShaderTextureSet : public NiObject {
public:
	int numTextures = 10;
	std::vector<NiString> textures;

	BSShaderTextureSet();
	BSShaderTextureSet(NiVersion& version);
	BSShaderTextureSet(NiStream& stream);

	static constexpr const char* BlockName = "BSShaderTextureSet";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);
	BSShaderTextureSet* Clone() { return new BSShaderTextureSet(*this); }
};

class BSLightingShaderProperty : public BSShaderProperty {
private:
	StringRef wetMaterialName;
	BlockRef<BSShaderTextureSet> textureSetRef;

public:
	Vector3 emissiveColor;
	float emissiveMultiple = 1.0f;
	uint textureClampMode = 3;
	float alpha = 1.0f;
	float refractionStrength = 0.0f;
	float glossiness = 1.0f;
	Vector3 specularColor = Vector3(1.0f, 1.0f, 1.0f);
	float specularStrength = 1.0f;
	float lightingEffect1 = 0.3f;			// User Version <= 12, User Version 2 < 130
	float lightingEffect2 = 2.0f;			// User Version <= 12, User Version 2 < 130

	float subsurfaceRolloff = 0.0f;			// User Version == 12, User Version 2 >= 130
	float unkFloat1 = 0.0f;					// User Version == 12, User Version 2 >= 130
	float backlightPower = 0.0f;			// User Version == 12, User Version 2 >= 130
	float grayscaleToPaletteScale = 1.0f;	// User Version == 12, User Version 2 >= 130
	float fresnelPower = 5.0f;				// User Version == 12, User Version 2 >= 130
	float wetnessSpecScale = 0.6f;			// User Version == 12, User Version 2 >= 130
	float wetnessSpecPower = 1.4f;			// User Version == 12, User Version 2 >= 130
	float wetnessMinVar = 0.2f;				// User Version == 12, User Version 2 >= 130
	float wetnessEnvmapScale = 1.0f;		// User Version == 12, User Version 2 >= 130
	float wetnessFresnelPower = 1.6f;		// User Version == 12, User Version 2 >= 130
	float wetnessMetalness = 0.0f;			// User Version == 12, User Version 2 >= 130

	ushort unkEnvmap = 0;											// Shader Type == 1, User Version == 12, User Version 2 >= 130
	Vector3 skinTintColor;											// Shader Type == 5
	uint unkSkinTint = 0;											// Shader Type == 5, User Version == 12, User Version 2 >= 130
	Vector3 hairTintColor;											// Shader Type == 6
	float maxPasses = 1.0f;											// Shader Type == 7
	float scale = 1.0f;												// Shader Type == 7
	float parallaxInnerLayerThickness = 0.0f;						// Shader Type == 11
	float parallaxRefractionScale = 1.0f;							// Shader Type == 11
	Vector2 parallaxInnerLayerTextureScale = Vector2(1.0f, 1.0f);	// Shader Type == 11
	float parallaxEnvmapStrength = 1.0f;							// Shader Type == 11
	Color4 sparkleParameters;										// Shader Type == 14
	float eyeCubemapScale = 1.0f;									// Shader Type == 16
	Vector3 eyeLeftReflectionCenter;								// Shader Type == 16
	Vector3 eyeRightReflectionCenter;								// Shader Type == 16

	BSLightingShaderProperty();
	BSLightingShaderProperty(NiVersion& version);
	BSLightingShaderProperty(NiStream& stream);

	static constexpr const char* BlockName = "BSLightingShaderProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);
	void GetStringRefs(std::set<StringRef*>& refs);
	void GetChildRefs(std::set<int*>& refs);
	BSLightingShaderProperty* Clone() { return new BSLightingShaderProperty(*this); }

	bool IsSkinTint();
	bool IsSkinned();
	void SetSkinned(const bool enable);
	bool IsDoubleSided();
	bool IsModelSpace();
	bool IsEmissive();
	bool HasBacklight();
	uint GetShaderType();
	void SetShaderType(const uint type);
	Vector3 GetSpecularColor();
	void SetSpecularColor(const Vector3& color);
	float GetSpecularStrength();
	void SetSpecularStrength(const float strength);
	float GetGlossiness();
	void SetGlossiness(const float gloss);
	int GetTextureSetRef();
	void SetTextureSetRef(const int texSetRef);
	Color4 GetEmissiveColor();
	void SetEmissiveColor(const Color4& color);
	float GetEmissiveMultiple();
	void SetEmissiveMultiple(const float emissive);
	float GetAlpha();
	std::string GetWetMaterialName();
	void SetWetMaterialName(const std::string& matName);
};

class BSEffectShaderProperty : public BSShaderProperty {
public:
	NiString sourceTexture;
	uint textureClampMode = 0;
	float falloffStartAngle = 1.0f;
	float falloffStopAngle = 1.0f;
	float falloffStartOpacity = 0.0f;
	float falloffStopOpacity = 0.0f;
	Color4 emissiveColor;
	float emissiveMultiple = 0.0f;
	float softFalloffDepth = 0.0f;
	NiString greyscaleTexture;

	NiString envMapTexture;
	NiString normalTexture;
	NiString envMaskTexture;
	float envMapScale = 1.0f;

	BSEffectShaderProperty() {}
	BSEffectShaderProperty(NiStream& stream);

	static constexpr const char* BlockName = "BSEffectShaderProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);
	BSEffectShaderProperty* Clone() { return new BSEffectShaderProperty(*this); }

	bool IsSkinTint();
	bool IsSkinned();
	void SetSkinned(const bool enable);
	bool IsDoubleSided();
	bool IsModelSpace();
	bool IsEmissive();
	bool HasBacklight();
	float GetEnvironmentMapScale();
	Color4 GetEmissiveColor();
	void SetEmissiveColor(const Color4& color);
	float GetEmissiveMultiple();
	void SetEmissiveMultiple(const float emissive);
};

class BSWaterShaderProperty : public BSShaderProperty {
private:
	uint waterFlags = 0;

public:
	BSWaterShaderProperty() {}
	BSWaterShaderProperty(NiStream& stream);

	static constexpr const char* BlockName = "BSWaterShaderProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);
	BSWaterShaderProperty* Clone() { return new BSWaterShaderProperty(*this); }

	bool IsSkinTint();
	bool IsSkinned();
	void SetSkinned(const bool enable);
	bool IsDoubleSided();
	bool IsModelSpace();
	bool IsEmissive();
	bool HasBacklight();
};

class BSSkyShaderProperty : public BSShaderProperty {
private:
	NiString baseTexture;
	uint skyFlags = 0;

public:
	BSSkyShaderProperty() {}
	BSSkyShaderProperty(NiStream& stream);

	static constexpr const char* BlockName = "BSSkyShaderProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);
	BSSkyShaderProperty* Clone() { return new BSSkyShaderProperty(*this); }

	bool IsSkinTint();
	bool IsSkinned();
	void SetSkinned(const bool enable);
	bool IsDoubleSided();
	bool IsModelSpace();
	bool IsEmissive();
	bool HasBacklight();
};

class BSShaderLightingProperty : public BSShaderProperty {
public:
	uint textureClampMode = 3;				// User Version <= 11

	void Get(NiStream& stream);
	void Put(NiStream& stream);
};

enum SkyObjectType : uint {
	BSSM_SKY_TEXTURE,
	BSSM_SKY_SUNGLARE,
	BSSM_SKY,
	BSSM_SKY_CLOUDS,
	BSSM_SKY_STARS = 5,
	BSSM_SKY_MOON_STARS_MASK = 7
};

class SkyShaderProperty : public BSShaderLightingProperty {
private:
	NiString fileName;
	SkyObjectType skyObjectType = BSSM_SKY_TEXTURE;

public:
	SkyShaderProperty() {}
	SkyShaderProperty(NiStream& stream);

	static constexpr const char* BlockName = "SkyShaderProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);

	SkyShaderProperty* Clone() { return new SkyShaderProperty(*this); }
};

class TileShaderProperty : public BSShaderLightingProperty {
private:
	NiString fileName;

public:
	TileShaderProperty() {}
	TileShaderProperty(NiStream& stream);

	static constexpr const char* BlockName = "TileShaderProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);

	TileShaderProperty* Clone() { return new TileShaderProperty(*this); }
};

class BSShaderNoLightingProperty : public BSShaderLightingProperty {
public:
	NiString baseTexture;
	float falloffStartAngle = 1.0f;			// User Version 2 > 26
	float falloffStopAngle = 0.0f;			// User Version 2 > 26
	float falloffStartOpacity = 1.0f;		// User Version 2 > 26
	float falloffStopOpacity = 1.0f;		// User Version 2 > 26

	BSShaderNoLightingProperty() {}
	BSShaderNoLightingProperty(NiStream& stream);

	static constexpr const char* BlockName = "BSShaderNoLightingProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);
	BSShaderNoLightingProperty* Clone() { return new BSShaderNoLightingProperty(*this); }

	bool IsSkinTint();
	bool IsSkinned();
	void SetSkinned(const bool enable);
};

class BSShaderPPLightingProperty : public BSShaderLightingProperty {
private:
	BlockRef<BSShaderTextureSet> textureSetRef;

public:
	float refractionStrength = 0.0f;		// User Version == 11 && User Version 2 > 14
	int refractionFirePeriod = 0;			// User Version == 11 && User Version 2 > 14
	float parallaxMaxPasses = 4.0f;			// User Version == 11 && User Version 2 > 24
	float parallaxScale = 1.0f;				// User Version == 11 && User Version 2 > 24
	Color4 emissiveColor;					// User Version >= 12

	BSShaderPPLightingProperty() {}
	BSShaderPPLightingProperty(NiStream& stream);

	static constexpr const char* BlockName = "BSShaderPPLightingProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);
	void GetChildRefs(std::set<int*>& refs);
	BSShaderPPLightingProperty* Clone() { return new BSShaderPPLightingProperty(*this); }

	bool IsSkinTint();
	bool IsSkinned();
	void SetSkinned(const bool enable);
	int GetTextureSetRef();
	void SetTextureSetRef(const int texSetRef);
};

class Lighting30ShaderProperty : public BSShaderPPLightingProperty {
public:
	Lighting30ShaderProperty() {}
	Lighting30ShaderProperty(NiStream& stream);

	static constexpr const char* BlockName = "Lighting30ShaderProperty";
	virtual const char* GetBlockName() { return BlockName; }

	Lighting30ShaderProperty* Clone() { return new Lighting30ShaderProperty(*this); }
};

class NiAlphaProperty : public NiProperty {
public:
	ushort flags = 4844;
	byte threshold = 128;

	NiAlphaProperty() {}
	NiAlphaProperty(NiStream& stream);

	static constexpr const char* BlockName = "NiAlphaProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);
	NiAlphaProperty* Clone() { return new NiAlphaProperty(*this); }
};


class NiMaterialProperty : public NiProperty {
private:
	Vector3 colorSpecular;
	Vector3 colorEmissive;
	float glossiness = 1.0f;
	float alpha = 1.0f;
	float emitMulti = 1.0f;					// Version == 20.2.0.7 && User Version >= 11 && User Version 2 > 21

public:
	Vector3 colorAmbient;					// !(Version == 20.2.0.7 && User Version >= 11 && User Version 2 > 21)
	Vector3 colorDiffuse;					// !(Version == 20.2.0.7 && User Version >= 11 && User Version 2 > 21)

	NiMaterialProperty() {}
	NiMaterialProperty(NiStream& stream);

	static constexpr const char* BlockName = "NiMaterialProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);
	NiMaterialProperty* Clone() { return new NiMaterialProperty(*this); }

	bool IsEmissive();
	Vector3 GetSpecularColor();
	void SetSpecularColor(const Vector3& color);
	float GetGlossiness();
	void SetGlossiness(const float gloss);
	Color4 GetEmissiveColor();
	void SetEmissiveColor(const Color4& color);
	float GetEmissiveMultiple();
	void SetEmissiveMultiple(const float emissive);
	float GetAlpha();
};

class NiStencilProperty : public NiProperty {
public:
	ushort flags = 19840;
	uint stencilRef = 0;
	uint stencilMask = 0xFFFFFFFF;

	NiStencilProperty() {}
	NiStencilProperty(NiStream& stream);

	static constexpr const char* BlockName = "NiStencilProperty";
	virtual const char* GetBlockName() { return BlockName; }

	void Get(NiStream& stream);
	void Put(NiStream& stream);
	NiStencilProperty* Clone() { return new NiStencilProperty(*this); }
};
