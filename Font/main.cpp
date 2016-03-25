#include "MainWindow.h"
#include <QApplication>
#include "ConfigParser.h"
#include "ConsoleModeController.h"
#include "GuiModeController.h"
#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    if (argc > 2)
	{
        QString pathToConfigFile(argv[1]);
        QString pathToOutputFile(argv[2]);
		ConsoleModeController controller;
        controller.run(pathToConfigFile, pathToOutputFile);
	}  
	else
	{
		GuiModeController controller;
		controller.run();
		return a.exec();
	}


}
