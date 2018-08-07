#include "form1.h"
#include "ui_form1.h"

Form1::Form1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form1)
{
    ui->setupUi(this);
}

Form1::~Form1()
{
    delete ui;
}

void Form1::on_lineEdit_textChanged(const QString &arg1)
{
    myApp * app = myApp::getInstance();
    app->str = arg1;
}
