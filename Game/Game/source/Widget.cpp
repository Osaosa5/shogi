
#include "Widget.h"

Widget::Widget(ObjectManager* ptrObjManager)
{
	_ptrObjManager = ptrObjManager;
	_isView = true;
}

Widget::~Widget()
{
}

