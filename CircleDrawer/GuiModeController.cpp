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
		QList<Circle*> defaultCircles;
		defaultCircles.append(new Circle(DEFAULT_RADIUS, DEFAULT_POSITION_X, DEFAULT_POSITION_Y));
		config = new Configuration(defaultCircles, new Panel(DEFAULT_SIZE_X, DEFAULT_SIZE_Y));
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
	Circle* circle = config->getCircles().first();

	int r = circle->getR();
	int x = circle->getPositionX();
	int y = circle->getPositionY();

	QVBoxLayout* controlsLayout = new QVBoxLayout;
	rControl = new ControlPanel("R", R_MIN, R_MAX, r);
	xControl = new ControlPanel("Position X", POSITION_MIN, POSITION_MAX, x);
	yControl = new ControlPanel("Position Y", POSITION_MIN, POSITION_MAX, y);


	controlsLayout->addWidget(rControl);
	controlsLayout->addWidget(xControl);
	controlsLayout->addWidget(yControl);
	
	controlsPanel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));
	controlsPanel->setLayout(controlsLayout);

	connect(rControl, SIGNAL(valueChanged(int)), SLOT(setRValue(int)));
	connect(xControl, SIGNAL(valueChanged(int)), SLOT(setXPositionValue(int)));
	connect(yControl, SIGNAL(valueChanged(int)), SLOT(setYPositionValue(int)));
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

			Circle* circle = config->getCircles().first();
			int r = circle->getR();
			int x = circle->getPositionX();
			int y = circle->getPositionY();

			rControl->setValue(r);
			xControl->setValue(x);
			yControl->setValue(y);
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

void GuiModeController::setRValue(int r)
{
	config->getCircles().first()->setR(r);
	drawPanel->update();
}

void GuiModeController::setXPositionValue(int x)
{
	config->getCircles().first()->setPositionX(x);
	drawPanel->update();
}

void GuiModeController::setYPositionValue(int y)
{
	config->getCircles().first()->setPositionY(y);
	drawPanel->update();
}



