#pragma once

#include "DxLib.h"

#include <type_traits>

VECTOR ConvertPosToFullHD(VECTOR pos, float dispW, float dispH);

template<typename T>
int ConvertEnumToInt(T e)
{
	static_assert(std::is_enum<T>::value, "T must be an enum type");
	return static_cast<int>(e);
}

template<typename T>
T ConvertIntToEnum(int i)
{
	static_assert(std::is_enum<T>::value, "T must be an enum type");
	return static_cast<T>(i);
}