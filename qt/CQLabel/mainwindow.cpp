#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CQLabel * label = new CQLabel(this);
    const QString filename = "E:/lcx/project/programpractice/qt/capture/img.PNG";
    QPixmap img;
    img.load(filename);
    label->setGeometry(QRect(40, 30, 701, 491));
    //label->setText("hello");
    label->setPixmap(img);
    label->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
