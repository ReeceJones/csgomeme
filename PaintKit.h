#pragma once
#include "Drawing.h"

class CCustomString
{
public:
	char* m_pszString;
	int m_iUnknown0, m_iUnknown1;
	int m_iLength;
};

class CPaintKit
{
public:
	int id;

	CCustomString name;
	CCustomString description_string;
	CCustomString description_tag;
	CCustomString pattern;
	CCustomString logo_material;

private:
	DWORD pad0[2];

public:
	int style;

	Color color0;
	Color color1;
	Color color2;
	Color color3;

private:
	DWORD pad1[4];

public:
	float wear_default;
	float wear_remap_min;
	float wear_remap_max;

	BYTE seed;

	BYTE phongexponent;
	BYTE phongalbedoboost;
	BYTE phongintensity;

	float pattern_scale;
	float pattern_offset_y_start;
	float pattern_offset_y_end;
	float pattern_offset_x_start;
	float pattern_offset_x_end;
	float pattern_rotate_start;
	float pattern_rotate_end;

	float logo_scale;
	float logo_offset_x;
	float logo_offset_y;
	float logo_rotation;

	int ignore_weapon_size_scale;

	int view_model_exponent_override_size;

	int only_first_material;

private:
	DWORD pad2[2];
};