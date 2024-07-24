
#include "DxLib.h"
#include "Convert.h"

/**
* @brief 画面座標をフルHD座標に変換する
* @param pos	画面座標
* @param dispW	画面の横幅
* @param dispH	画面の縦幅
* @return フルHD座標に変換した座標
* @details ウィンドウのサイズが変わった時でも、フルHD座標に変換する
*/
VECTOR ConvertPosToFullHD(VECTOR pos, float dispW, float dispH)
{
	float x = dispW * pos.x / 1920;
	float y = dispH * pos.y / 1080;
	float z = 0;
	return VGet(x, y, z);
}
