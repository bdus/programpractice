#include "mainwindow.h"
#include "ui_mainwindow.h"

/***
 *  bdus@2018-8-8 15:51:36
 *  鼠标左键绘制新图像
 *  鼠标右键移动选中的图像
 *  ESC键销毁m_layout队列尾部的一个layout 加提示
 *  Enter键完成绘制
 *
 *  Clear Button 重新绘制
 *
 * *
 ***/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)//, m_CurrState(initPaint)
{
    ui->setupUi(this);

    initWindow();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWindow()
{
    //init State
    m_layout.clear();
    m_selectedRect = NULL;

    m_CurrState = initPaint;
    m_isMousePress = false;
    //ui->label->adjustSize();

    //init pen
    //m_painter->
    //m_painter.setPen(QPen(Qt::yellow, 1, Qt::SolidLine, Qt::FlatCap));

    //init label
    const QString filename = "E:/lcx/project/programpractice/qt/capture/img.PNG";
    m_loadPixmap.load(filename);
    m_capturePixmap = m_loadPixmap;

    ui->label->setPixmap(m_capturePixmap);
}


void MainWindow::mousePressEvent(QMouseEvent *e)
{
    m_isMousePress = true;

    if(e->button() == Qt::LeftButton)// && m_CurrState == initPaint)
    {
        m_beginPoint = e->pos();
        m_CurrState = beginPaint;
    }
    else if(e->button() == Qt::RightButton && m_layout.empty() != true)
    {
        int index = getSelectRectIndex(m_layout,e->pos());
        m_selectedRect  = &m_layout[index];
        m_CurrState     = beginMove;
    }
    else
        ;

    return QWidget::mousePressEvent(e);

}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    m_isMousePress = false;

    if(e->button() == Qt::LeftButton)
    {
        m_endPoint = e->pos();
        QRect tmpRect(m_beginPoint,m_endPoint);
        m_layout.append(tmpRect);
        m_CurrState = endPaint;
        update();

    }
    if(e->button() == Qt::RightButton)
    {
        m_selectedRect->setBottomLeft(e->pos());
        update();
    }

    return QWidget::mouseMoveEvent(e);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{

}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    //m_nowPos = e->pos();
    switch (m_CurrState) {
    case beginPaint:
    case beginMove:
        m_nowPos = e->pos();
        update();
        break;
    default:
        break;
    }

    return QWidget::mouseMoveEvent(e);
}

void MainWindow::paintEvent(QPaintEvent *e)
{

    m_painter.begin(&m_loadPixmap);



    switch (m_CurrState) {
    case initPaint:
        break;
    case beginPaint:
    case beginMove:
        //QMessageBox::information(this,"xx","m_beginPoint" + m_beginPoint.x());
        m_painter.drawRect(QRect(m_beginPoint,m_nowPos));
        break;


    default:
        break;
    }

    m_painter.end();

    ui->label->setPixmap(m_loadPixmap);
}

int MainWindow::getSelectRectIndex(QList<QRect> &mlayout, QPoint pos)
{
    int ans = -1;
    int area = 0;
    for(int i = 0; i < mlayout.count(); i++)
    {
        if(mlayout[i].contains(pos))
        {
            if(area < mlayout[i].height()*mlayout[i].width() )
            {
                ans = i;
            }
        }
    }
    return ans;
}


