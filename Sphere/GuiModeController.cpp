#include "GuiModeController.h"
#include "JsonParserException.h"
#include <QtWidgets/QMessageBox>
#include "MainWindow.h"
#include <QtWidgets/QVBoxLayout>
#include <QDebug>

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
        config = new Configuration( new Panel(DEFAULT_HEIGHT, DEFAULT_WIDTH),
                                   DEFAULT_X, DEFAULT_Y,
                                   DEFAULT_SCALE, DEFAULT_FILTER, DEFAULT_SOURCE);
		serializer = new saveAndLoadConfig::Serializer();

        drawPanel = new DrawPanel(config, this);
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

    int x = config->getPositionX();
    int y = config->getPositionY();
    int scale = config->getScale();



	QVBoxLayout* controlsLayout = new QVBoxLayout;
    xControl = new ControlPanel("X", XY_MIN, XY_MAX, x);
    yControl = new ControlPanel("Y", XY_MIN, XY_MAX, y);
    scaleControl = new ControlPanel("Scale", SCALE_MIN, SCALE_MAX, scale);

    QGroupBox *groupBox = new QGroupBox("filter");
    nearestRadioButton = new QRadioButton("nearest");
    bilinearRadioButton = new QRadioButton("bilinear");
    if(config->getFilterType() == NEAREST)
    {
        nearestRadioButton->setChecked(true);
    }
    else
    {
        bilinearRadioButton->setChecked(true);
    }
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(nearestRadioButton);
    vbox->addWidget(bilinearRadioButton);
    groupBox->setLayout(vbox);

    controlsLayout->addWidget(xControl);
    controlsLayout->addWidget(yControl);
    controlsLayout->addWidget(scaleControl);
    controlsLayout->addWidget(groupBox);

	
	controlsPanel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));
	controlsPanel->setLayout(controlsLayout);

    connect(xControl, SIGNAL(valueChanged(int)), SLOT(setXValue(int)));
    connect(yControl, SIGNAL(valueChanged(int)), SLOT(setYValue(int)));
    connect(scaleControl, SIGNAL(valueChanged(int)), SLOT(setScaleValue(int)));

//    connect(nearestRadioButton, SIGNAL(stateChanged(int)), SLOT(setNearestFilter(int)));
    connect(nearestRadioButton, SIGNAL(clicked()), SLOT(setNearestFilter()));
    connect(bilinearRadioButton, SIGNAL(clicked()), SLOT(setBilinearFilter()));
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

            xControl->setValue(config->getPositionX());
            yControl->setValue(config->getPositionY());
            scaleControl->setValue(config->getScale());
            if(config->getFilterType() == NEAREST)
            {
                nearestRadioButton->setChecked(true);
            }
            else
            {
                bilinearRadioButton->setChecked(true);
            }
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

void GuiModeController::setXValue(int x)
{
    config->setPositionX(x);
    xControl->setValue(config->getPositionX());
	drawPanel->update();
}

void GuiModeController::setYValue(int y)
{
    config->setPositionY(y);
    yControl->setValue(config->getPositionY());
	drawPanel->update();
}

void GuiModeController::setScaleValue(int x)
{
    config->setScale(x);
    drawPanel->update();
}

void GuiModeController::setNearestFilter()
{
    config->setFilterType(NEAREST);
    drawPanel->update();
}

void GuiModeController::setBilinearFilter()
{
    config->setFilterType(BILINEAR);
    drawPanel->update();
}






