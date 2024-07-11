
#include "DxLib.h"
#include "JsonManeger.h"


// �ÓI�����o����
std::unordered_map<std::string, nlohmann::json> JsonManeger::_mapJson;

void JsonManeger::Init()
{
	_mapJson.clear();
}

void JsonManeger::Release()
{
	ClearJson();
}

void JsonManeger::ClearJson()
{
    // ���ׂẴf�[�^�̍폜������
    _mapJson.clear();
}

nlohmann::json JsonManeger::LoadJsonFile(const TCHAR* FileName)
{
    // �L�[�̌���
    auto itr = _mapJson.find(FileName);
    if (itr != _mapJson.end())
    {
        // �L�[��������
        return itr->second;
    }
    // �L�[����������
    JSONFile JSON(FileName);
    // �L�[�ƃf�[�^��map�ɓo�^
    _mapJson[FileName] = JSON.Data();

    return JSON.Data();
}
