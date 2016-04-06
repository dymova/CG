#include "ConsoleModeController.h"
#include "Drawer.h"
#include "ConfigParser.h"
#include <iostream>
#include <QImage>
#include <QColor>
#include "JsonParserException.h"


ConsoleModeController::ConsoleModeController()
{
}

ConsoleModeController::~ConsoleModeController()
{
}

void ConsoleModeController::run(QString pathToConfigFile, QString pathToOutputFile)
{
	saveAndLoadConfig::ConfigParser parser;
	try
	{
        Configuration* config = parser.parse(pathToConfigFile);
		Drawer drawer;
        int width = config->getPanel()->getWidth();
        int height = config->getPanel()->getHeight();
        QImage* image = new QImage(width, height, QImage::Format_RGB888);

		const int whiteColorValue = 255;
		memset(image->bits(), whiteColorValue, image->byteCount());

        QColor black(0, 0, 0);
        QColor blue(0, 77, 255);

        drawer.drawAxis(image);

        if(config->isOutline())
        {
            drawer.drawOutline(image, config, black);
        }

        if(config->isFill())
        {
            drawer.drawFill(image, config, blue);
        }

        if (!image->save(pathToOutputFile))
		{
			std::cerr << "image wasn't saved" << std::endl;
		}
	}
	catch (JsonParserException& exception)
	{
		std::cerr << exception.what() << std::endl;
	}
}

