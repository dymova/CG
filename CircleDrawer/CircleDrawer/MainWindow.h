#pragma once
#include <QMainWindow>
#include <QGroupBox>
#include "DrawPanel.h"
#include "ConfigParser.h"
#include "ControlPanel.h"
#include "Serializer.h"
//#include "Controls.h"

class Configuration;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	void initControllersPanel(QGroupBox*& controlsPanel);
	explicit MainWindow(QString pathToConfig);
	~MainWindow();

private:
	void createActions();
	void createMenus();

	saveAndLoadConfig::ConfigParser* parser;
	saveAndLoadConfig::Serializer* serializer;
	Configuration* config;
	DrawPanel* drawPanel;
	QMenu *fileMenu;
	QAction *openAct;
	QAction *saveAct;
	ControlPanel* rControl;
	ControlPanel* xControl;
	ControlPanel* yControl;

	const int R_MIN = 0;
	const int R_MAX = 10000;
	const int POSITION_MIN = -10000;
	const int POSITION_MAX = 10000;

private slots:
	void open();
	void save();

//	void setDrawPanelSize(int x, int y);
	public slots:
		void setRValue(int r);
		void setXPositionValue(int x);
		void setYPositionValue(int y);
};

