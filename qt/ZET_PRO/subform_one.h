#ifndef SUBFORM_ONE_H
#define SUBFORM_ONE_H

#include <QObject>
#include <QWidget>
#include <opencv2/opencv.hpp>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QFileDialog>
#include <QString>

#include "algorithms.h"

using namespace cv;

namespace Ui {
class SubForm_one;
}

class SubForm_one : public QWidget
{
    Q_OBJECT

public:
    //explicit SubForm_one(QWidget *parent = 0);
    explicit SubForm_one(QWidget *parent = 0 , FP_type fp_type = FPt_gray, Data_type data_type = Video);

    ~SubForm_one();

    void InitVideo(String filename);
    void play();

    AlgorithmInstance * frameProcessor;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:

    QImage  cvMatToQImage( const cv::Mat &inMat );
    QPixmap cvMatToQPixmap( const cv::Mat &inMat );

    Ui::SubForm_one *ui;
    FP_type fp;
    Data_type dp;
    VideoCapture capture;
    QString file_path;
};

#endif // SUBFORM_ONE_H
