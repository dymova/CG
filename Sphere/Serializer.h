#pragma once
#include "Configuration.h"
#include <stdexcept>

namespace saveAndLoadConfig
{
	class Serializer
	{
    private:
        const QString KEY_GLYPHS= "glyphs";
        const QString KEY_PANEL = "panel";

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

