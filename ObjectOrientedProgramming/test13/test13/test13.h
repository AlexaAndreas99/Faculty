#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_test13.h"
#include "Controller.h"
#include <vector>
#include "Weather.h"
class test13 : public QMainWindow
{
	Q_OBJECT

public:
	test13(Controller c,QWidget *parent = Q_NULLPTR);

private:
	Ui::test13Class ui;
	std::vector<Weather> datas;
	Controller ctrl;
	void populate();
private slots:
	void filter();
	void total();
};
