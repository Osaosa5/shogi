#pragma once

#include "DxLib.h"

/**
	@brief	点の構造体
*/
struct Dot
{
	int x, y;
};

/**
	@brief	線の構造体
*/
struct Line
{
	int x1, y1, x2, y2;
};

/**
	@brief	矩形の構造体
*/
struct Box 
{
	int x, y, w, h;
};

/**
	@brief	円の構造体
*/
struct Circle 
{
	int x, y, r;
};