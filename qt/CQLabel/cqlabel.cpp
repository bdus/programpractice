#include "cqlabel.h"
#define DEBUG
#undef DEBUG
#define mmsg(X) QMessageBox::information(this,"message",X);
#define GOOD(X) QMessageBox::information(this,"GOOD",QString::number(X));

//inline void mmsg(QString str, int a) {  QMessageBox::information(this,"message",str + QString::number(a));}

CQLabel::CQLabel(QWidget *parent) : QLabel(parent)
{
    initWindow();
}

void CQLabel::setSelectedRect(QRect &value)
{
    //m_layout.replace(index,value);
    //m_layout.replace(m_selectedIndex,value);
    m_layout[m_selectedIndex] = value;
    update();
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


    //init label
//    const QString filename = "E:/lcx/project/programpractice/qt/capture/img.PNG";
//    m_loadPixmap.load(filename);
//    m_capturePixmap = m_loadPixmap;

    //init TopBar
    QHBoxLayout * hlayout = new QHBoxLayout;

    QString tmpn[] = {"x:","y:","w:","h:"};
    for(int i = 0; i < 4; i++)
    {
        tag[i] = new QLabel(this);
        lie[i] = new QLineEdit(this);
        hlayout->addWidget(lie[i]);
        hlayout->addWidget(tag[i]);
        tag[i]->setText(tmpn[i]);
        tag[i]->setGeometry(20+30*2*i,0,30,20);
        lie[i]->setGeometry(20+30*(2*i+1),0,30,20);
        tag[i]->show();
        lie[i]->show();
        //connect(lie[i],SIGNAL(textEdited(QString)),this,SLOT(editTopBar()));
        connect(lie[i],SIGNAL(textChanged(QString)),this,SLOT(editTopBar()));
    }

    tag[4] = new QLabel(this);
    hlayout->addWidget(lie[4]);
    tag[4]->setGeometry(0,0,20,20);
    tag[4]->show();

}

void CQLabel::updateTopBar()
{
    myEdit = true;
    QRect tmpre = m_MoveTo.translated(var_x,var_y);
    lie[0]->setText(QString::number(tmpre.x()));
    lie[1]->setText(QString::number(tmpre.y()));
    lie[2]->setText(QString::number(tmpre.width()));
    lie[3]->setText(QString::number(tmpre.height()));
    myEdit = false;
}

void CQLabel::editTopBar()
{
    if(m_selectedIndex != -1 && m_layout.empty() != true && myEdit == false)
    {
//        QRect *tmpre = new QRect(lie[0]->text().toInt(),lie[1]->text().toInt(),lie[2]->text().toInt(),lie[3]->text().toInt());
        m_selectedRect->setRect(lie[0]->text().toInt(),lie[1]->text().toInt(),lie[2]->text().toInt(),lie[3]->text().toInt());
//        QRect * old = m_selectedRect;
//        m_selectedRect = tmpre;
//        delete(old);
    }
    update();
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
        m_selectedIndex = getSelectRectIndex(m_layout,e->pos());
        if(m_selectedIndex == -1)
        {
            ;//QMessageBox::information(this,"error","OCCOR -1");
        }
        else if(m_selectedIndex >= 0)
        {
            m_selectedRect  = &m_layout[m_selectedIndex];
            if(m_selectedIndex_bk != m_selectedIndex)
            {
                qDebug() << m_selectedIndex_bk << '\n';
                m_selectedIndex_bk = m_selectedIndex;
                emit selectChanged(m_selectedIndex);
                tag[4]->setText(QString::number(m_selectedIndex));
            }
            m_CurrState     = beginMove;
            m_MoveTo = m_layout[m_selectedIndex].translated(0,0);
        }
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
        if(tmpRect.height()* tmpRect.width() > 60)
            m_layout.append(tmpRect);
        else
            mmsg("too small!")
        m_CurrState = endPaint;
        update();

    }else if(e->button() == Qt::RightButton && m_CurrState != initPaint)
    {
        m_endPoint = e->pos();
        //m_selectedRect->adjust(var_x,var_y,var_x,var_y);
        if(this->contentsRect().contains(m_endPoint))
            m_selectedRect->translate(var_x,var_y);
        else
            mmsg("out of bounds!")
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
        m_nowPos = e->pos();
        update();
        break;
    case beginMove:
        m_nowPos = e->pos();
        var_x = m_nowPos.x() - m_beginPoint.x();
        var_y = m_nowPos.y() - m_beginPoint.y();
        update();
        updateTopBar();
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
        var_x = var_y = 0;
        break;
    case beginMove:
        m_painter.drawRects(m_layout);
        m_painter.drawLine(m_beginPoint,m_nowPos);
        m_painter.drawRect(m_MoveTo.translated(var_x,var_y));

        break;
    default:
        break;
    }

    m_painter.end();

}

int CQLabel::getSelectRectIndex(QVector<QRect> &mlayout, QPoint pos)
{
    int ans = -1;
    int area = mlayout[0].height()*mlayout[0].width();
    #ifdef DEBUG
    mmsg("count" + QString::number(mlayout.count()));
    #endif

    for(int i = 0; i < mlayout.count(); i++)
    {
        if(mlayout[i].contains(pos))
        {
            if(area >= mlayout[i].height()*mlayout[i].width() )
            {
                ans = i;
                area = mlayout[i].height()*mlayout[i].width();
            }
        }
    }
#ifdef DEBUG
    mmsg("ans" + QString::number(ans));
#endif
    return ans;
}
