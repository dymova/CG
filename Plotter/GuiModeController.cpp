#include "GuiModeController.h"
#include "JsonParserException.h"
#include <QtWidgets/QMessageBox>
#include "MainWindow.h"
#include <QtWidgets/QVBoxLayout>


GuiModeController::GuiModeController()
{
}



GuiModeController::~GuiModeController()
{
	delete config;
	delete serializer;
	delete parser;
	delete mainWindow;
}

void GuiModeController::run()
{
	parser = new saveAndLoadConfig::ConfigParser();
	try
	{
        Lemniscate* defaultCircle = new Lemniscate(DEFAULT_XY, DEFAULT_XY, DEFAULT_XY, DEFAULT_XY);
        config = new Configuration(defaultCircle, new Panel(DEFAULT_SIZE_X, DEFAULT_SIZE_Y));
		serializer = new saveAndLoadConfig::Serializer();

		drawPanel = new DrawPanel(config);
		QGroupBox* controlsPanel;
		initControllersPanel(controlsPanel);

		mainWindow = new MainWindow(drawPanel, controlsPanel);

		connect(mainWindow, SIGNAL(open(QString)), SLOT(open(QString)));
		connect(mainWindow, SIGNAL(save(QString)), SLOT(save(QString)));

		mainWindow->show();
	}
	catch (JsonParserException& exception)
	{
		QMessageBox::critical(0, "Error", exception.what());
	}

}
void GuiModeController::initControllersPanel(QGroupBox*& controlsPanel)
{
	controlsPanel = new QGroupBox("Controls");
    Lemniscate* lemniscate = config->getLemniscate();

    int x1 = lemniscate->getX1();
    int y1 = lemniscate->getY1();
    int x2 = lemniscate->getX2();
    int y2 = lemniscate->getY2();

	QVBoxLayout* controlsLayout = new QVBoxLayout;
    x1Control = new ControlPanel("X1", XY_MIN, XY_MAX, x1);
    y1Control = new ControlPanel("Y1", XY_MIN, XY_MAX, y1);
    x2Control = new ControlPanel("X2", XY_MIN, XY_MAX, x2);
    y2Control = new ControlPanel("Y2", XY_MIN, XY_MAX, y2);


    controlsLayout->addWidget(x1Control);
    controlsLayout->addWidget(y1Control);
    controlsLayout->addWidget(x2Control);
    controlsLayout->addWidget(y2Control);
	
	controlsPanel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));
	controlsPanel->setLayout(controlsLayout);

    connect(x1Control, SIGNAL(valueChanged(int)), SLOT(setX1Value(int)));
    connect(y1Control, SIGNAL(valueChanged(int)), SLOT(setY1Value(int)));
    connect(x2Control, SIGNAL(valueChanged(int)), SLOT(setX2Value(int)));
    connect(y2Control, SIGNAL(valueChanged(int)), SLOT(setY2Value(int)));
}

void GuiModeController::open(QString str)
{
	if (!str.isEmpty())
	{
		
		try
		{
			Configuration* oldConfig = config;
			config = parser->parse(str);
			delete oldConfig;
			drawPanel->setConfig(config);
			drawPanel->update();

            Lemniscate* lemniscate = config->getLemniscate();
            int x1 = lemniscate->getX1();
            int y1 = lemniscate->getY1();
            int x2 = lemniscate->getX2();
            int y2 = lemniscate->getY2();

            x1Control->setValue(x1);
            y1Control->setValue(y1);
            x2Control->setValue(x2);
            y2Control->setValue(y2);
		}
		catch (JsonParserException& exception)
		{
			QMessageBox::critical(0, "Error", exception.what());
		}

	}
}

void GuiModeController::save(QString str) const
{
	if (!str.isEmpty())
	{
		try
		{
			serializer->serialize(str, config);
		}
		catch (saveAndLoadConfig::ConfigSerializerException& exception)
		{
			QMessageBox::critical(0, "Error", exception.what());
		}

	}
}

void GuiModeController::setX1Value(int x)
{
    config->getLemniscate()->setX1(x);
	drawPanel->update();
}

void GuiModeController::setY1Value(int y)
{
    config->getLemniscate()->setY1(y);
	drawPanel->update();
}

void GuiModeController::setX2Value(int x)
{
    config->getLemniscate()->setX2(x);
	drawPanel->update();
}

void GuiModeController::setY2Value(int y)
{
    config->getLemniscate()->setY2(y);
    drawPanel->update();
}



