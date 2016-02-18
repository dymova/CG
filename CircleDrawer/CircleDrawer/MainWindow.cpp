#include "MainWindow.h"
#include <QVBoxLayout>
#include<QMenuBar>
#include <QFileDialog>
#include "ControlPanel.h"
#include "Configuration.h"
#include "Serializer.h"

void MainWindow::initControllersPanel(QGroupBox*& controlsPanel) //todo
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
	controlsPanel->setLayout(controlsLayout);

	connect(rControl, SIGNAL(valueChanged(int)), drawPanel, SLOT(setRValue(int)));
	connect(xControl, SIGNAL(valueChanged(int)), drawPanel, SLOT(setXPositionValue(int)));
	connect(yControl, SIGNAL(valueChanged(int)), drawPanel, SLOT(setYPositionValue(int)));
}

MainWindow::MainWindow(QString path)
{
	parser = new saveAndLoadConfig::ConfigParser();
	config = parser->parse(path);
	QWidget* mainWidget = new QWidget;
	setWindowTitle("CircleDrawer");

	QWidget* centralWidget = new QWidget;

	QGroupBox* drawPanelBox = new QGroupBox("Draw Panel");
	drawPanel = new DrawPanel(config);


	QHBoxLayout* drawPanelLayout = new QHBoxLayout;
	drawPanelLayout->setMargin(5);
	drawPanelLayout->addWidget(drawPanel);
	drawPanelBox->setLayout(drawPanelLayout);

	QGroupBox* controlsPanel;
	initControllersPanel(controlsPanel);

	QHBoxLayout* mainWidgetLayout = new QHBoxLayout;
	mainWidgetLayout->setMargin(5);
	mainWidgetLayout->addWidget(drawPanelBox);
	mainWidgetLayout->addWidget(controlsPanel);
	centralWidget->setLayout(mainWidgetLayout);

	QWidget* menuWidget = new QWidget;
	menuWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->setMargin(5);
	mainLayout->addWidget(menuWidget);
	mainLayout->addWidget(centralWidget);
	mainWidget->setLayout(mainLayout);

	createActions();
	createMenus();

	setCentralWidget(mainWidget);
	serializer = new saveAndLoadConfig::Serializer();
}

MainWindow::~MainWindow()
{
	delete config;
	delete serializer;
	delete parser;
}

void MainWindow::createActions()
{
	openAct = new QAction(tr("&Open"), this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip(tr("Open an existing configuration file."));
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	saveAct = new QAction(tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save a configuration file."));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
}

void MainWindow::open()
{
	QString str = QFileDialog::getOpenFileName(this, "Open Dialog", "", "*.json");
	if (!str.isEmpty())
	{
		delete config;
		config = parser->parse(str);
		drawPanel->setConfig(config);
		drawPanel->update();

		Circle* circle = config->getCircles().first();
		int sizeX = config->getPanel()->getSizeX();
		int sizeY = config->getPanel()->getSizeY();
		int r = circle->getR();
		int x = circle->getPositionX();
		int y = circle->getPositionY();

		rControl->setValue(r);
		xControl->setValue(x);
		yControl->setValue(y);
	}
}

void MainWindow::save()
{
	QString str = QFileDialog::getSaveFileName(this, "Save Dialog", "", "*.json");
	if (!str.isEmpty())
	{
		serializer->serialize(str, config);
	}
}

