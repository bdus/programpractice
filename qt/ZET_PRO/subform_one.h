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


#include "algorithms.h"

using namespace cv;

namespace Ui {
class SubForm_one;
}

class SubForm_one : public QWidget
{
    Q_OBJECT

public:
    explicit SubForm_one(QWidget *parent = 0);
    ~SubForm_one();

    void InitVideo(String filename);
    void play();

    AlgorithmInstance * frameProcessor;

private slots:
    void on_pushButton_clicked();

private:

    QImage  cvMatToQImage( const cv::Mat &inMat );
    QPixmap cvMatToQPixmap( const cv::Mat &inMat );

    Ui::SubForm_one *ui;

    VideoCapture capture;


};

#endif // SUBFORM_ONE_H
