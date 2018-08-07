#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Form1 * f1 = new Form1(this);
    f1->setWindowFlag(Qt::Window);
    f1->show();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    myApp * app = myApp::getInstance();
    ui->plainTextEdit->document()->setPlainText(app->str);
}
