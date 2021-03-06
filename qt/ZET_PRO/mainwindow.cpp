#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitSubForms();
}

MainWindow::~MainWindow()
{
    delete ui;

    cv::destroyAllWindows();
}

void MainWindow::InitSubForms()
{
    //load forms
    ui->listWidget->clear();

    QStringList btn_name = {
        "video_gray",
        "video_noise",
        "video_fog",
        "video_night",
        "video_lumen",
        "video_rain",
        "image_gray"
    };
    ui->listWidget->addItems(btn_name);
    QListWidgetItem * item_p;
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        item_p = ui->listWidget->item(i);
        item_p->setSizeHint(QSize(50,50));
        //待实现 调整items样式  https://blog.csdn.net/u011125673/article/details/51753997
            //            QTableWidgetItem *item = new QTableWidgetItem("Apple");
            //            item->setBackgroundColor(QColor(0,60,10));
            //            item->setTextColor(QColor(200,111,100));
            //            item->setFont(QFont("Helvetica"));
            //            table_widget->setItem(0,3,item);
    }

    //装载页面
    SubForm_one * Page_one = new SubForm_one(this);
    ui->stackedWidget->addWidget(Page_one);

    ui->stackedWidget->addWidget(new SubForm_one(this,FPt_noise));
    ui->stackedWidget->addWidget(new SubForm_one(this,FPt_fog));
    ui->stackedWidget->addWidget(new SubForm_one(this,FPt_night));
    ui->stackedWidget->addWidget(new SubForm_one(this,FPt_lumen));
    ui->stackedWidget->addWidget(new SubForm_one(this,FPt_rain));

    ui->stackedWidget->addWidget(new SubForm_one(this,FPt_gray,Image));

    //ui->stackedWidget->addWidget(Page_two);

    ui->stackedWidget->setCurrentWidget(Page_one);
    Page_one->show();

    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));

}
