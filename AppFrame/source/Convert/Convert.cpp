
#include "DxLib.h"
#include "Convert.h"

/**
* @brief ��ʍ��W���t��HD���W�ɕϊ�����
* @param pos	��ʍ��W
* @param dispW	��ʂ̉���
* @param dispH	��ʂ̏c��
* @return �t��HD���W�ɕϊ��������W
* @details �E�B���h�E�̃T�C�Y���ς�������ł��A�t��HD���W�ɕϊ�����
*/
VECTOR ConvertPosToFullHD(VECTOR pos, float dispW, float dispH)
{
	float x = dispW * pos.x / 1920;
	float y = dispH * pos.y / 1080;
	float z = 0;
	return VGet(x, y, z);
}
