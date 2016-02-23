#include "MainWindow.h"
#include <QApplication>
#include "ConfigParser.h"
#include "ConsoleModeController.h"
#include "GuiModeController.h"


int main(int argc, char *argv[])
{
	const QString DEFAULT_CONFIG_FILE = "defaultConfig.json";

	QApplication a(argc, argv);
	saveAndLoadConfig::ConfigParser parser;
	if (argc >= 2)
	{
		QString pathToConfigFile(argv[1]);
		ConsoleModeController controller;
		controller.run(pathToConfigFile);
	}  
	else
	{
		GuiModeController controller;
		controller.run(DEFAULT_CONFIG_FILE);
		return a.exec();
	}


}
