#include "cqlabel.h"
#define DEBUG
#undef DEBUG
#define mmsg(X) QMessageBox::information(this,"message",X);
#define GOOD(X) QMessageBox::information(this,"GOOD",QString::number(X));

//inline void mmsg(QString str, int a) {  QMessageBox::information(this,"message",str + QString::number(a));}

CQLabel::CQLabel(QWidget *parent) : QLabel(parent)
{

}

void CQLabel::initWindow()
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
}

void CQLabel::mousePressEvent(QMouseEvent *e)
{
    m_isMousePress = true;

    if(e->button() == Qt::LeftButton)// && m_CurrState == initPaint)
    {
        m_beginPoint = e->pos();
        m_CurrState = beginPaint;
    }
    else if(e->button() == Qt::RightButton && m_CurrState != initPaint && m_layout.empty() != true)
    {
        m_beginPoint = e->pos();
        int index = getSelectRectIndex(m_layout,e->pos());
        if(index == -1)
            QMessageBox::information(this,"error","OCCOR -1");
        m_selectedRect  = &m_layout[index];
        m_CurrState     = beginMove;
    }
    else
        ;

    return QWidget::mousePressEvent(e);

}

void CQLabel::mouseReleaseEvent(QMouseEvent *e)
{
    m_isMousePress = false;

    if(e->button() == Qt::LeftButton)
    {
        m_endPoint = e->pos();
        QRect tmpRect(m_beginPoint,m_endPoint);
        m_layout.append(tmpRect);
        m_CurrState = endPaint;
        update();

    }else if(e->button() == Qt::RightButton && m_CurrState != initPaint)
    {
        m_endPoint = e->pos();

        m_selectedRect->adjust(var_x,var_y,var_x,var_y);

        //m_selectedRect->setBottom();
        m_CurrState = endMove;
        update();
    }
    else
        ;

    return QWidget::mouseMoveEvent(e);
}

void CQLabel::mouseMoveEvent(QMouseEvent *e)
{
    switch (m_CurrState) {
    case beginPaint:
    case beginMove:
        m_nowPos = e->pos();
        var_x = m_nowPos.x() - m_beginPoint.x();
        var_y = m_nowPos.y() - m_beginPoint.y();
        update();
        break;
    default:
        break;
    }

    return QWidget::mouseMoveEvent(e);
}

void CQLabel::paintEvent(QPaintEvent *e)
{
    m_painter.begin(this);


    switch (m_CurrState) {
    case initPaint:
        break;
    case beginPaint:
        m_painter.drawRects(m_layout);
        m_painter.drawRect(QRect(m_beginPoint,m_nowPos));
        break;
    case endPaint:
    case endMove:
        m_painter.drawRects(m_layout);
        break;
    case beginMove:
        m_painter.drawRects(m_layout);
        m_painter.drawRect(QRect(m_beginPoint,m_nowPos));

        //m_painter.drawRect(QRect(tmpo,tmpsize));

        break;
    default:
        break;
    }

    m_painter.end();



}

int CQLabel::getSelectRectIndex(QVector<QRect> &mlayout, QPoint pos)
{
    int ans = -1;
    int area = 0;
    #ifdef DEBUG
    mmsg("count" + QString::number(mlayout.count()));
    #endif

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
#ifdef DEBUG
    mmsg("ans" + QString::number(ans));
#endif
    return ans;
}
