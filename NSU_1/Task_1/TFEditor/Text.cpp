#include "Text.h"

Text& Text::Replace(const std::string& oldPattern, const std::string& newPattern)
{
	if (!oldPattern.empty())
	{
		size_t pos = std::string::npos;
		size_t nextPos = 0UL;
		while ((pos = _data.find(oldPattern, nextPos)) != std::string::npos)
		{
			_data.replace(pos, oldPattern.size(), newPattern);
			if (newPattern.size() > oldPattern.size()) nextPos = pos + newPattern.size();
		}
	}
	return *this;
}

Text& Text::Append(const Text& text)
{
	if (!text._data.empty()) _data.append(text._data);
	return *this;
}

bool Text::TailStartsWithPattern(const std::string& pattern, size_t& patternLastPos) const
{
	patternLastPos = std::string::npos;

	if (_data.empty() || pattern.empty()) return false;

	patternLastPos = 0;
	size_t nextPos = 0UL;
	while ((patternLastPos = _data.find(pattern[0], nextPos)) != std::string::npos)
	{
		size_t substrSize = _data.size() - patternLastPos;
		auto p = _data.find(pattern.substr(0, substrSize), nextPos);
		if (p != std::string::npos) break;
		nextPos = patternLastPos + 1;
	}

	if (patternLastPos == std::string::npos) return false;

	if (_data.size() - patternLastPos >= pattern.size())
	{
		patternLastPos = std::string::npos;
		return false;
	}
	return true;
}
