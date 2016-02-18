#pragma once
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
class ControlPanel : public QWidget
{
	Q_OBJECT

public:
	void connectElements();
	ControlPanel(QString label, int min, int max, int defaultValue);
	~ControlPanel();
signals:
	void valueChanged(int);
public slots:
void setValue(int);

private:
	QLabel* label;
	QSpinBox* spinBox;
	QSlider* slider;
};

