#include <fstream>
#include <iostream>
#include "JSONFile.h"

JSONFile::JSONFile(const std::string filename)
{
	// メンバの初期化
	Init();
	_filename = filename;

	// ファイルを開く
	std::ifstream ifs(filename);	// 入力をバイナリ形式で
	if (!ifs) {
		// 開くの失敗
		return;
	}

	ifs >> _jsonData;
	ifs.close();

	_success = true;
}

JSONFile::JSONFile(const std::string filename, nlohmann::json writeDate)
{
	// メンバの初期化
	Init();
	_filename = filename;

	std::ofstream ofs(filename);
	if(!ofs) {
		// 開くの失敗
		return;
	}

	ofs << writeDate.dump() << std::endl;
	ofs.close();

	_success = true;
}

JSONFile::~JSONFile()
{
	_jsonData.clear();
}

void JSONFile::Init()
{
	_filename = "";
	_jsonData.clear();
	_success = false;
}
