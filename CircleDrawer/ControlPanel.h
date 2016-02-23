#pragma once
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
class Circle;

class ControlPanel : public QWidget
{
	Q_OBJECT

public:
	void connectElements() const;
	ControlPanel(QString label, int min, int max, int defaultValue);
	~ControlPanel();
signals:
	void valueChanged(int);
public slots:
void setValue(int) const;

private:
	QLabel* label;
	QSpinBox* spinBox;
	QSlider* slider;
};

