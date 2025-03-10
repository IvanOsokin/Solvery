#include "Text.h"

Text& Text::Replace(const std::string& oldPattern, const std::string& newPattern)
{
	if (!oldPattern.empty())
	{
		size_t nextPosition = 0UL;
		size_t currentPosition = _data.find(oldPattern, nextPosition);
		while (std::string::npos != currentPosition)
		{
			_data.replace(currentPosition, oldPattern.size(), newPattern);
			if (newPattern.size() > oldPattern.size())
			{
				nextPosition = currentPosition + newPattern.size();
			}
			currentPosition = _data.find(oldPattern, nextPosition);
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

bool Text::TailStartsWithPattern(const std::string& pattern, size_t& patternLastPosition) const
{
	if (_data.empty() || pattern.empty())
	{
		return false;
	}

	size_t nextPosition = 0UL;
	patternLastPosition = _data.find(pattern[0], nextPosition);
	while (std::string::npos != patternLastPosition)
	{
		size_t substrSize = _data.size() - patternLastPosition;
		size_t p = _data.find(pattern.substr(0, substrSize), nextPosition);
		if (std::string::npos != p)
		{
			break;
		}
		nextPosition = patternLastPosition + 1;
		patternLastPosition = _data.find(pattern[0], nextPosition);
	}

	if (std::string::npos == patternLastPosition)
	{
		return false;
	}

	if (_data.size() - patternLastPosition >= pattern.size())
	{
		patternLastPosition = std::string::npos;
		return false;
	}
	return true;
}
