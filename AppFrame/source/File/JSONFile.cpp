#include <fstream>
#include <iostream>
#include "JSONFile.h"

JSONFile::JSONFile(const std::string filename)
{
	// �����o�̏�����
	Init();
	_filename = filename;

	// �t�@�C�����J��
	std::ifstream ifs(filename);	// ���͂��o�C�i���`����
	if (!ifs) {
		// �J���̎��s
		return;
	}

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
	if(!ofs) {
		// �J���̎��s
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
