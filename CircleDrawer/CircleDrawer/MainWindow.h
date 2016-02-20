#pragma once
#include <QMainWindow>
#include <QGroupBox>
#include "DrawPanel.h"
#include "ConfigParser.h"
#include "ControlPanel.h"
#include "Serializer.h"

class Configuration;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(DrawPanel* panel, QGroupBox* controlsPanel);
	~MainWindow();

private:
	void createActions();
	void createMenus();

	QMenu *fileMenu;
	QAction *openAct;
	QAction *saveAct;


private slots:
	void open();
	void save();
signals:
	void open(QString);
	void save(QString);


};

