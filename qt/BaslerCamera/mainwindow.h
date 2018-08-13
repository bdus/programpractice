#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BaslerCamera/sbaslercameracontrol.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_getExTime_clicked();
    void on_pushButton_SetExTime_clicked();
    void on_pushButton_SetMode_clicked();
    void on_pushButton_GetMode_clicked();
    void on_pushButton_CFMode_clicked();
    void on_comboBox_CFMode_activated(int index);
    void on_pushButton_Start_clicked();
    void on_pushButtonRotate_clicked();
private:
    Ui::MainWindow *ui;
    SBaslerCameraControl* m_control = Q_NULLPTR;
    QMatrix m_matrix;
};

#endif // MAINWINDOW_H
