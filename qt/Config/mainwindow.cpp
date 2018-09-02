#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings setting("config.ini",QSettings::IniFormat);
    setting.beginGroup("config");
    setting.setValue("page",QVariant("string"));
    setting.setValue("site",QVariant("www.1.com"));
    setting.setValue("maker",QVariant("Gai"));
    setting.endGroup();

}

MainWindow::~MainWindow()
{
    delete ui;
}
