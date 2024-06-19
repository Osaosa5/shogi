
#include "DxLib.h"
#include "JsonManeger.h"


// 静的メンバ実体
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
    // すべてのデータの削除をする
    _mapJson.clear();
}

nlohmann::json JsonManeger::LoadJsonFile(const TCHAR* FileName)
{
    // キーの検索
    auto itr = _mapJson.find(FileName);
    if (itr != _mapJson.end())
    {
        // キーがあった
        return itr->second;
    }
    // キーが無かった
    JSONFile JSON(FileName);
    // キーとデータをmapに登録
    _mapJson[FileName] = JSON.Data();

    return JSON.Data();
}
