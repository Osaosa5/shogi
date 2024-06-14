#include <fstream>
#include <iostream>
#include "JSONFile.h"

JSONFile::JSONFile(const std::string filename)
{
	// �����o�̏�����
	Init();
	_filename = filename;

	// �t�@�C�����J��
	std::ifstream ifs(filename);
	// �t�@�C�����J���Ȃ������珈�����I��点��
	if (!ifs) return;

	ifs >> _jsonData;
	ifs.close();

	_success = true;
}

JSONFile::JSONFile(const std::string filename, nlohmann::json writeDate)
{
	// �����o�̏�����
	Init();
	_filename = filename;

	std::ofstream ofs(filename);
	// �t�@�C�����J���Ȃ������珈�����I��点��
	if(!ofs) return;

	// �t�@�C���ɏ������ރf�[�^���V���A���C�Y����
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
