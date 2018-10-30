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


    clabel = new CQLabel(ui->centralWidget);
    //clabel->clear();
//    const QString filename = "E:/lcx/project/programpractice/qt/capture/img.PNG";
//    QPixmap img;
//    img.load(filename);
    clabel->setGeometry(tmpStore);

    clabel->setStyleSheet("QLabel{border:2px solid rgb(0, 255, 0);}");

//    clabel->setPixmap(img);

    clabel->show();

    connect(clabel->lie[0],SIGNAL(textChanged(QString)),ui->lineEdit,SLOT(setText(QString)));
    connect(clabel->lie[1],SIGNAL(textChanged(QString)),ui->lineEdit_2,SLOT(setText(QString)));
    connect(clabel->lie[2],SIGNAL(textChanged(QString)),ui->lineEdit_3,SLOT(setText(QString)));
    connect(clabel->lie[3],SIGNAL(textChanged(QString)),ui->lineEdit_4,SLOT(setText(QString)));

    connect(ui->lineEdit,SIGNAL(textEdited(QString)),clabel->lie[0],SLOT(setText(QString)));
    connect(ui->lineEdit_2,SIGNAL(textEdited(QString)),clabel->lie[1],SLOT(setText(QString)));
    connect(ui->lineEdit_3,SIGNAL(textEdited(QString)),clabel->lie[2],SLOT(setText(QString)));
    connect(ui->lineEdit_4,SIGNAL(textEdited(QString)),clabel->lie[3],SLOT(setText(QString)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWindow()
{

}

void MainWindow::initCamSDK()
{
    CameraParameter para;
    Camera camera(para);
    string path = "test_opencv.tiff";
    for (int i = 0; i < 5; i++) {
        camera.parameter.Width += 100;
        Mat CvImage;
        camera.CaptueCVImageRandom(CvImage);
        ostringstream os;
        os << "test_opencv" << i << ".tiff";
        imwrite(os.str(), CvImage);
        }
}


//void MainWindow::updateSelectRect(int index)
//{
//    ui->lineEdit->setText(QString::number(clabel->m_layout[index].x()));
//    ui->lineEdit_2->setText(QString::number(clabel->m_layout[index].y()));
//    ui->lineEdit_3->setText(QString::number(clabel->m_layout[index].height()));
//    ui->lineEdit_4->setText(QString::number(clabel->m_layout[index].width()));
//}


//void MainWindow::lineEditsChange()
//{
//    //qDebug() << "hello" << '\n';
//    int x = ui->lineEdit->text().toInt();
//    int y = ui->lineEdit_2->text().toInt();
//    int h = ui->lineEdit_3->text().toInt();
//    int w = ui->lineEdit_4->text().toInt();
//    QRect tmpRect(x,y,w,h);
//    emit lineEditChanged(tmpRect);
//}
