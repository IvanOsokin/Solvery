#pragma once

#include "pch.h"

class Text
{
public:
	Text() = default;
	explicit Text(const Text& other) = default;
	explicit Text(Text&& other) = default;
	explicit Text(const std::string& string) : _data(string) { }
	explicit Text(std::string&& string) : _data(std::move(string)) { }
	~Text() = default;

	Text& Replace(const std::string& oldPattern, const std::string& newPattern);
	Text& Append(const Text& text);
	inline const std::string& Data() const { return _data; }
	bool TailStartsWithPattern(const std::string& pattern, size_t& patternLastPosition) const;
	inline size_t Size() const { return _data.size(); }

private:
	std::string _data;
};

