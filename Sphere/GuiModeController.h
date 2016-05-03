#pragma once
#include "ConfigParser.h"
#include "Serializer.h"
#include "ControlPanel.h"
#include "MainWindow.h"
#include <QRadioButton>


class GuiModeController : QObject
{
	Q_OBJECT
public:
	GuiModeController();
	~GuiModeController();
	void run();

    const int XY_MIN = -1000;
    const int XY_MAX = 1000;
    const int SCALE_MAX = 1000;
    const int SCALE_MIN = -1000;


    const int DEFAULT_WIDTH = 300;
    const int DEFAULT_HEIGHT = 300;
    const int DEFAULT_X = 0;
    const int DEFAULT_Y = 0;
    const int DEFAULT_SCALE = 0;
//    const Filter DEFAULT_FILTER = NEAREST;
    const Filter DEFAULT_FILTER = BILINEAR;
//    const QString DEFAULT_SOURCE = "Lenna.png";
    const QString DEFAULT_SOURCE = "earth.jpg";


private:
	saveAndLoadConfig::ConfigParser* parser;
	saveAndLoadConfig::Serializer* serializer;
	Configuration* config;

	MainWindow* mainWindow;
	DrawPanel* drawPanel;

    ControlPanel* xControl;
    ControlPanel* yControl;
    ControlPanel* scaleControl;
    QRadioButton* nearestRadioButton;
    QRadioButton* bilinearRadioButton;

	void initControllersPanel(QGroupBox*& controlsPanel);

public slots:
	void open(QString str);
	void save(QString str) const;
    void setXValue(int x);
    void setYValue(int y);
    void setScaleValue(int x);
    void setNearestFilter();
    void setBilinearFilter();

};

