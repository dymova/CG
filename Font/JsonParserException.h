#pragma once
#include <stdexcept>

class JsonParserException : public std::runtime_error
{
public:
	explicit JsonParserException(std::string message);
};
