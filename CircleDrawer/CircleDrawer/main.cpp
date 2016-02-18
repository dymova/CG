#include "MainWindow.h"
#include <QApplication>
#include <QPushButton>
#include "ConfigParser.h"
#include "ConsoleModeController.h"


int main(int argc, char *argv[])
{
	const QString DEFAULT_CONFIG_FILE = "defaultConfig.json";

	QApplication a(argc, argv);
	saveAndLoadConfig::ConfigParser parser;
//	if (argc >= 2)
//	{
//		QString pathToConfigFile(argv[1]);
//		ConsoleModeController controller;
//		controller.run(pathToConfigFile);
//	}  
//	else
//	{
		MainWindow w(DEFAULT_CONFIG_FILE);
		w.show();

//	}
	return a.exec();
}
