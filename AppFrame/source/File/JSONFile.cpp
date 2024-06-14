#include <fstream>
#include <iostream>
#include "JSONFile.h"

JSONFile::JSONFile(const std::string filename)
{
	// メンバの初期化
	Init();
	_filename = filename;

	// ファイルを開く
	std::ifstream ifs(filename);
	// ファイルを開けなかったら処理を終わらせる
	if (!ifs) return;

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
	// ファイルを開けなかったら処理を終わらせる
	if(!ofs) return;

	// ファイルに書き込むデータをシリアライズする
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
