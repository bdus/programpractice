#include "subform_one.h"
#include "ui_subform_one.h"

SubForm_one::SubForm_one(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubForm_one)
{
    ui->setupUi(this);
}

SubForm_one::~SubForm_one()
{
    delete ui;
}

void SubForm_one::InitVideo(String filename /*,FP_gray type*/)
{
    //capture = new VideoCapture(filename);
    capture.open(filename);
    if(!capture.isOpened())
        qDebug() << "load video error" << '\n';

    /*,FP_gray type*/
    //frameProcessor = new rgb2gray();
}
QImage SubForm_one::cvMatToQImage( const cv::Mat &inMat )
{
    switch ( inMat.type() )
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_ARGB32 );

        return image;
    }

    // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_RGB888 );

        return image.rgbSwapped();
    }

    // 8-bit, 1 channel
    case CV_8UC1:
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Grayscale8 );//Format_Alpha8 and Format_Grayscale8 were added in Qt 5.5
#else//这里还有一种写法
        static QVector<QRgb>  sColorTable;

        // only create our color table the first time
        if ( sColorTable.isEmpty() )
        {
            sColorTable.resize( 256 );

            for ( int i = 0; i < 256; ++i )
            {
                sColorTable[i] = qRgb( i, i, i );
            }
        }

        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Indexed8 );

        image.setColorTable( sColorTable );
#endif

        return image;
    }

    default:
        qWarning() << "CVS::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}

QPixmap SubForm_one::cvMatToQPixmap( const cv::Mat &inMat )
{
    return QPixmap::fromImage( cvMatToQImage( inMat ) );
}

void SubForm_one::play()
{
    Mat frame,dest,down;
    QPixmap tmp;

    cv::namedWindow("play");

    int i = 0;

    while(1)
    {
        capture >> frame;
        if(true == frame.empty()) break;


        ui->label->setText(QString("time : %1").arg(capture.get(CV_CAP_PROP_POS_AVI_RATIO)));
        qDebug() << i << '\n';
        i++;

        //FPptr(frame,dest);

        cv::resize(frame, down, Size(frame.cols/4, frame.rows/4), INTER_CUBIC);//下采样

        frameProcessor->frameProcess(down,dest);

        tmp = cvMatToQPixmap(down);
        tmp.scaled(ui->label_src->size(),Qt::KeepAspectRatio);
        ui->label_src->setPixmap(tmp);


        //cv::resize(dest, tmp, Size(frame.cols, frame.rows), INTER_CUBIC);//上采样
        tmp = cvMatToQPixmap(dest);
        tmp.scaled(ui->label_dest->size(),Qt::KeepAspectRatio);
        ui->label_dest->setPixmap(tmp);

        imshow("play",dest);
        cv::waitKey(20);
    }
}

void SubForm_one::on_pushButton_clicked()
{
    //    Page_one->InitVideo("./video/fog.mp4");
    //    Page_one->frameProcessor = new rgb2gray();
    ui->label->setText("");
    InitVideo("C:/Users/admin/Documents/qt/ZET_PRO/video/fog.mp4");
    frameProcessor = new rgb2gray();
    play();
}
