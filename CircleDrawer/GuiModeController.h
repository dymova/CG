#pragma once
#include "ConfigParser.h"
#include "Serializer.h"
#include "DrawPanel.h"
#include "ControlPanel.h"
#include "MainWindow.h"

class GuiModeController : QObject
{
	Q_OBJECT
public:
	GuiModeController();
	~GuiModeController();
	void run();

	const int R_MIN = 0;
	const int R_MAX = 10000;
	const int POSITION_MIN = -10000;
	const int POSITION_MAX = 10000;

	const int DEFAULT_RADIUS = 20;
	const int DEFAULT_POSITION_X = 0;
	const int DEFAULT_POSITION_Y = 0;
	const int DEFAULT_SIZE_Y = 300;
	const int DEFAULT_SIZE_X = 300;


private:
	saveAndLoadConfig::ConfigParser* parser;
	saveAndLoadConfig::Serializer* serializer;
	Configuration* config;

	MainWindow* mainWindow;
	DrawPanel* drawPanel;

	ControlPanel* rControl;
	ControlPanel* xControl;
	ControlPanel* yControl;
	void initControllersPanel(QGroupBox*& controlsPanel);

public slots:
	void open(QString str);
	void save(QString str) const;
	void setRValue(int r);
	void setXPositionValue(int x);
	void setYPositionValue(int y);
};

