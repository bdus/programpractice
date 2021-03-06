#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRect>
#include <QList>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QPen>
#include <QMessageBox>

enum PainStatus{
    initPaint   = 0,
    beginPaint  = 1,
    endPaint    = 2,
    beginMove   = 3,
    endMove     = 4
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void initWindow();
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void keyPressEvent(QKeyEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void paintEvent(QPaintEvent* e);

    int getSelectRectIndex(QList<QRect> &mlayout,QPoint pos);

private:
    QList<QRect> m_layout;         //保存划分结果
    QRect * m_selectedRect;
    QPoint m_beginPoint, m_endPoint, m_nowPos;
    PainStatus m_CurrState;        //当前状态

    bool m_isMousePress;
    QPixmap m_loadPixmap, m_capturePixmap;
    int m_screenwidth;
    int m_screenheight;

    QPainter m_painter;

};

#endif // MAINWINDOW_H
