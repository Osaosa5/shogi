
#include "DxLib.h"
#include "EventSystem.h"


/**
* @brief	�I������
* @param	input	����
* @param	axis	��
* @param	size	�I�����̐�
* @param	select	���݂̑I����
* @return	�I�𒆂̗v�f
* @details	���͂ɉ����đI������ύX����
* @details	���͂��Ȃ��ꍇ�͂��̂܂܂̒l��Ԃ�
*/
int SelectFocus(int input, std::string axis, int size, int select)
{
	// ���͂ɉ����đI������ύX
	if (axis == "x") {
		if(input & PAD_INPUT_LEFT)	return (select + size - 1) % size;
		if(input & PAD_INPUT_RIGHT)	return (select + 1) % size;
	}
	else if (axis == "y") {
		if(input & PAD_INPUT_UP)	return (select + size - 1) % size;
		if(input & PAD_INPUT_DOWN)	return (select + 1) % size;
	}

	// ���͂��Ȃ��ꍇ�͂��̂܂܂̒l��Ԃ�
	return select;
}
