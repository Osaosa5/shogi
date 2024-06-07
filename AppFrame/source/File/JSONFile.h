#pragma once

#include <string>
#include <nlohmann/json.hpp>

class JSONFile
{
public:
	// “Ç‚İ‚İ
	JSONFile(const std::string filename);
	// ‘‚«‚İ
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

