#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cqlabel.h"
#include <QPixmap>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    //void lineEditChanged(QRect & value);

private slots:
    //void updateSelectRect(int index);
    //void lineEditsChange();

private:
    Ui::MainWindow *ui;

    CQLabel * clabel;

    void initWindow();
};

#endif // MAINWINDOW_H
