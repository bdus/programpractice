#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto tmpStore = ui->label->geometry();
    ui->label->hide();
    ui->label->setParent(0);
    ui->label->deleteLater();


    CQLabel * clabel = new CQLabel(this);
    //clabel->clear();
    const QString filename = "E:/lcx/project/programpractice/qt/capture/img.PNG";
    QPixmap img;
    img.load(filename);
    clabel->setGeometry(tmpStore);

    clabel->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 0);}");

    clabel->setPixmap(img);

    clabel->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
