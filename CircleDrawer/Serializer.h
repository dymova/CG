#pragma once
#include "Configuration.h"
#include <stdexcept>

namespace saveAndLoadConfig
{
	class Serializer
	{
	public:
		Serializer();
		~Serializer();
		void serialize(QString file, Configuration* config);
	};

	class ConfigSerializerException : public std::runtime_error
	{
	public:
		explicit ConfigSerializerException(std::string message) :
			std::runtime_error("Config serializer error: " + message)
		{
		}
	};
}

