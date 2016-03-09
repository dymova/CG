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

    const int XY_MIN = -10000;
    const int XY_MAX = 10000;
    const int DEFAULT_X1 = 0;
    const int DEFAULT_Y1 = -162;
    const int DEFAULT_X2 = 130;
    const int DEFAULT_Y2 = 10;

    const int DEFAULT_WIDTH = 300;
    const int DEFAULT_HEIGHT = 300;


private:
	saveAndLoadConfig::ConfigParser* parser;
	saveAndLoadConfig::Serializer* serializer;
	Configuration* config;

	MainWindow* mainWindow;
	DrawPanel* drawPanel;

    ControlPanel* x1Control;
    ControlPanel* y1Control;
    ControlPanel* x2Control;
    ControlPanel* y2Control;

	void initControllersPanel(QGroupBox*& controlsPanel);

public slots:
	void open(QString str);
	void save(QString str) const;
    void setX1Value(int x);
    void setY1Value(int y);
    void setY2Value(int y);
    void setX2Value(int x);
};

