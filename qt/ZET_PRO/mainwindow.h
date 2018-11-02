#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMenu>
#include <QAction>
#include <QMessageBox>

#include "subform_one.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//private slots:
    //void PageShift();

private:

    void InitSubForms();

    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
