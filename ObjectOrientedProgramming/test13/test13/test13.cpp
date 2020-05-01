#include "test13.h"

test13::test13(Controller c,QWidget *parent)
	: QMainWindow(parent),ctrl(c)
{
	this->datas = this->ctrl.get_repo().get_all();
	ui.setupUi(this);
	this->populate();

	QObject::connect(this->ui.filterInput, &QLineEdit::textChanged, this, &test13::filter);
	QObject::connect(this->ui.totalButton, &QPushButton::clicked, this, &test13::total);

}

void test13::populate()
{
	if (this->ui.weatherListWidget->count() != 0)
		this->ui.weatherListWidget->clear();

	for (auto i : this->datas)
	{
		QString listItem = QString::fromStdString(i.toString());
		QListWidgetItem* listItemWidget = new QListWidgetItem(listItem);
		this->ui.weatherListWidget->addItem(listItemWidget);
	}

}

void test13::total()
{
	std::string s = this->ui.descInput->text().toStdString();
	int total = this->ctrl.get_total(s);
	QString qtotal = QString::fromStdString("Total:\n"+std::to_string(total));
	this->ui.totalLabel->setText(qtotal);
}

void test13::filter()
{
	std::string s = this->ui.filterInput->text().toStdString();
	this->datas = this->ctrl.get_filtered(s);
	this->populate();
}
