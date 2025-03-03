#include "Text.h"

Text& Text::Replace(const std::string& oldPattern, const std::string& newPattern)
{
	if (!oldPattern.empty())
	{
		size_t nextPos = 0UL;
		size_t pos = _data.find(oldPattern, nextPos);
		while (std::string::npos != pos)
		{
			_data.replace(pos, oldPattern.size(), newPattern);
			if (newPattern.size() > oldPattern.size())
			{
				nextPos = pos + newPattern.size();
			}
		}
	}
	return *this;
}

Text& Text::Append(const Text& text)
{
	if (!text._data.empty())
	{
		_data.append(text._data);
	}
	return *this;
}

bool Text::TailStartsWithPattern(const std::string& pattern, size_t& patternLastPos) const
{
	patternLastPos = std::string::npos;

	if (_data.empty() || pattern.empty())
	{
		return false;
	}

	size_t nextPos = 0UL;
	patternLastPos = _data.find(pattern[0], nextPos);
	while (std::string::npos != patternLastPos)
	{
		size_t substrSize = _data.size() - patternLastPos;
		auto p = _data.find(pattern.substr(0, substrSize), nextPos);
		if (std::string::npos != p)
		{
			break;
		}
		nextPos = patternLastPos + 1;
	}

	if (std::string::npos == patternLastPos)
	{
		return false;
	}

	if (_data.size() - patternLastPos >= pattern.size())
	{
		patternLastPos = std::string::npos;
		return false;
	}
	return true;
}
