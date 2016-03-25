#include "JsonParserException.h"


JsonParserException::JsonParserException(std::string message):
	std::runtime_error("Json parser error: " + message)
{
}
