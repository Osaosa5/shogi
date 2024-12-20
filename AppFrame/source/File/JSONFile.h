#pragma once

#include <string>
#include <nlohmann/json.hpp>

class JSONFile
{
public:
	// 読み込み
	JSONFile(const std::string filename);
	// 書き込み
	JSONFile(const std::string filename, nlohmann::json writeDate);	

	~JSONFile();
	std::string	Filename() { return _filename; }
	nlohmann::json Data() { return _jsonData; }
	bool Success() { return _success; }

private:
	void Init();

	std::string		_filename;
	nlohmann::json	_jsonData;

	bool	_success;
};

