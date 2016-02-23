#include "ControlPanel.h"
#include <QVBoxLayout>


ControlPanel::ControlPanel(QString name, int min, int max, int defaultValue)
{
	slider = new QSlider(Qt::Horizontal);
	label = new QLabel(name);
	spinBox = new QSpinBox();

	spinBox->setRange(min, max);
	spinBox->setValue(defaultValue);
	slider->setRange(min, max);
	slider->setValue(defaultValue);

	QVBoxLayout* vLayout = new QVBoxLayout;
	QHBoxLayout* hLayout = new QHBoxLayout;
	hLayout->setMargin(5);
	hLayout->setSpacing(15);
	hLayout->addWidget(label);
	hLayout->addWidget(spinBox);

	vLayout->setMargin(5);
	vLayout->setSpacing(15);
	vLayout->addLayout(hLayout);
	vLayout->addWidget(slider);

	setLayout(vLayout);

	connectElements();
}

void ControlPanel::connectElements() const
{
	connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
	connect(spinBox, SIGNAL(valueChanged(int)), SIGNAL(valueChanged(int)));


	connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
	connect(slider, SIGNAL(valueChanged(int)), SIGNAL(valueChanged(int)));
}

void ControlPanel::setValue(int value) const
{
	spinBox->setValue(value);
	slider->setValue(value);
}

ControlPanel::~ControlPanel()
{
}

