#include "MainWindow.h"
#include <QVBoxLayout>
#include<QMenuBar>
#include <QFileDialog>



MainWindow::MainWindow(DrawPanel* drawPanel, QGroupBox* controlsPanel)
{
	QWidget* mainWidget = new QWidget;
	setWindowTitle("CircleDrawer");

	QWidget* centralWidget = new QWidget;

	QGroupBox* drawPanelBox = new QGroupBox("Draw Panel");
	QHBoxLayout* drawPanelLayout = new QHBoxLayout;
	drawPanelLayout->setMargin(5);
	drawPanelLayout->addWidget(drawPanel);
	drawPanelBox->setLayout(drawPanelLayout);

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
}

MainWindow::~MainWindow()
{
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
	emit open(str);


}

void MainWindow::save()
{
	QString str = QFileDialog::getSaveFileName(this, "Save Dialog", "", "*.json");
	emit save(str);
}


