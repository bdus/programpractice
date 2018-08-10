#ifndef CQLABEL_H
#define CQLABEL_H
#include <QLineEdit>
#include <QDebug>
#include <QLabel>
#include <QRect>
#include <QVector>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QPen>
#include <QMessageBox>
#include <QHBoxLayout>

enum PainStatus{
    initPaint   = 0,
    beginPaint  = 1,
    endPaint    = 2,
    beginMove   = 3,
    endMove     = 4
};


class CQLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CQLabel(QWidget *parent = nullptr);


    QLineEdit *lie[4];
    QLabel * tag[5];


    QVector<QRect> m_layout;         //保存划分结果
    int m_selectedIndex;
    int m_selectedIndex_bk;
    PainStatus m_CurrState;        //当前状态
    QRect m_MoveTo;

signals:
    void selectChanged(int index);

public slots:
    void setSelectedRect(QRect & value);

private:
    QRect * m_selectedRect;
    QPoint m_beginPoint, m_endPoint, m_nowPos;
    int var_x,var_y;

    bool m_isMousePress;
    QPixmap m_loadPixmap, m_capturePixmap;
//    int m_screenwidth;
//    int m_screenheight;
    bool myEdit;
    QPainter m_painter;

private slots:
    void editTopBar();
private:
    void initWindow();
    void updateTopBar();

    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    //void keyPressEvent(QKeyEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void paintEvent(QPaintEvent* e);

    int getSelectRectIndex(QVector<QRect> &mlayout,QPoint pos);

};

#endif // CQLABEL_H
