#pragma once

#include <fstream>

#include "Utils.h"

class TextFile
{
public:
	virtual ~TextFile() = default;

	virtual bool Open() = 0;

protected:
	fs::path _fileName;
	std::fstream _fs;
};

