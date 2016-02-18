#include "ConsoleModeController.h"
#include "Drawer.h"
#include "ConfigParser.h"
#include <iostream>
#include <QImage>


ConsoleModeController::ConsoleModeController()
{
}

ConsoleModeController::~ConsoleModeController()
{
}

void ConsoleModeController::run(QString pathToFile)
{
	saveAndLoadConfig::ConfigParser parser;
	try
	{
		Configuration* config = parser.parse(pathToFile);
		Drawer drawer;
		Circle* circle = config->getCircles().first();
		int sizeX = config->getPanel()->getSizeX();
		int sizeY = config->getPanel()->getSizeY();
		QImage* image = new QImage(sizeX, sizeY, QImage::Format_RGB888);

		const int whiteColorValue = 255;
		memset(image->bits(), whiteColorValue, image->byteCount());
		drawer.drawCircle(image, circle);


		if (!image->save("out.png"))
		{
			std::cerr << "image wasn't saved" << std::endl;
		}
	}
	catch (saveAndLoadConfig::ConfigParserException& exception)
	{
		std::cerr << exception.what() << std::endl;
	}
}

