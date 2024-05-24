#pragma once

#include <string>

class ObjectManager;

class Object
{
public:
	Object();
	virtual ~Object();

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

private:
	// アクセスを許可するためにfriend宣言を行う
	friend class ObjectManager;
	// アクセスするための情報
	std::string _name;	// 名前
	int _id;			// ID
};