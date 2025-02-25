#pragma once

#include <string>

class Text
{
public:
	Text() = default;
	Text(const Text& other) = default;
	Text(Text&& other) = default;
	Text(const std::string& string) : _data(string) { }
	Text(std::string&& string) : _data(string) { }
	~Text() = default;

	Text& Replace(const std::string& oldPattern, const std::string& newPattern);
	Text& Append(const Text& text);
	inline const std::string& Data() const { return _data; }
	bool TailStartsWithPattern(const std::string& pattern, size_t& patternLastPos) const;
	inline size_t Size() const { return _data.size(); }

private:
	std::string _data;
};

