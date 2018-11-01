#include "subform_one.h"
#include "ui_subform_one.h"

//SubForm_one::SubForm_one(QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::SubForm_one)
//{
//    ui->setupUi(this);

//    ui->progressBar->setMinimum(0);
//    ui->progressBar->setValue(0);

//    video_file_path = "./video/fog.mp4";
//    ui->label_path->setText(video_file_path);
//}

SubForm_one::SubForm_one(QWidget *parent, FP_type fp_type, Data_type data_type) :
    QWidget(parent),
    ui(new Ui::SubForm_one),
    fp(fp_type),
    dp(data_type)
{
    ui->setupUi(this);

    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);

    //fp_type
    switch (fp_type) {
    case FPt_noise:
        frameProcessor = new FP_noise();
        break;
    case FPt_fog:
        frameProcessor = new FP_fog();
        break;
    case FPt_night:
        frameProcessor = new FP_night();
        break;
//    case FP_noise:
//        frameProcessor = new FP_noise();
//        break;
//    case FP_noise:
//        frameProcessor = new FP_noise();
//        break;
    case FPt_gray:
    default:
        frameProcessor = new rgb2gray();
        break;
    }

    //data_type
    if(dp == Video)
    {
        file_path = "./video/fog.mp4";
        ui->label_path->setText(file_path);
    }
    else /*if (dp == Image)*/
    {
        file_path = "./video/img.PNG";
        ui->label_path->setText(file_path);
        //ui->progressBar->setDisabled(true);
    }

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

    //long nFrame=static_cast<long>(capture.get(CV_CAP_PROP_FRAME_COUNT)); // 获取总帧数
    int nFrame =  capture.get(CV_CAP_PROP_FRAME_COUNT);
    //qDebug() << nFrame << '\n';
    ui->progressBar->setMaximum(nFrame);
    cv::namedWindow("play");

    int i = 0;

    while(1)
    {
        capture >> frame;
        if(true == frame.empty()) break;

        //long nowFrame=static_cast<long>();
        int nowFrame = capture.get(CV_CAP_PROP_POS_FRAMES) ;
        //double ratio =  static_cast<float>(nowFrame/(float)nFrame);
        //ui->label->setText("percent : " + QString::number(ratio*100));
        ui->progressBar->setValue(nowFrame);
        //qDebug() << capture.get(CV_CAP_PROP_POS_FRAMES) << '\n';

        cv::resize(frame, down, Size(frame.cols/4, frame.rows/4), INTER_CUBIC);//下采样

        tmp = cvMatToQPixmap(down);
        tmp.scaled(ui->label_src->size(),Qt::KeepAspectRatio);
        ui->label_src->setPixmap(tmp);

        frameProcessor->frameProcess(down,dest);

        //cv::resize(dest, tmp, Size(frame.cols, frame.rows), INTER_CUBIC);//上采样
        tmp = cvMatToQPixmap(dest);
        tmp.scaled(ui->label_dest->size(),Qt::KeepAspectRatio);
        ui->label_dest->setPixmap(tmp);

        imshow("play",dest);
        cv::waitKey(20);
    }

    cv::destroyWindow("play");
}

void SubForm_one::InitImage(String filename)
{
    frImage = cv::imread(filename);
//    if(true == frImage.empty()){
//        qDebug() << "image empty" << '\n';
//        return;
//    }

    ui->label_src->setScaledContents(true);
    ui->label_dest->setScaledContents(true);

}

void SubForm_one::run( )
{
    Mat dest;
    QPixmap tmp;

    if(true == frImage.empty()){
        qDebug() << "image empty" << '\n';
        return;
    }

    frameProcessor->frameProcess(frImage,dest);

    tmp = cvMatToQPixmap(frImage);
    tmp.scaled(ui->label_src->size(), Qt::KeepAspectRatio);
    ui->label_src->setPixmap(tmp);

    //cv::resize(dest, tmp, Size(frame.cols, frame.rows), INTER_CUBIC);//上采样
    tmp = cvMatToQPixmap(dest);
    tmp.scaled(ui->label_dest->size(),Qt::KeepAspectRatio);
    ui->label_dest->setPixmap(tmp);

}

void SubForm_one::on_pushButton_clicked()
{
    //    Page_one->InitVideo("./video/fog.mp4");
    //    Page_one->frameProcessor = new rgb2gray();

    ui->label->setText("");

    if(dp == Video)
    {
        InitVideo(file_path.toStdString());
        play();
    }
    else /*if (dp == Image)*/
    {
        InitImage(file_path.toStdString());
        run();
    }

}

void SubForm_one::on_pushButton_2_clicked()
{
//    if(dp == Video)
//    {
//        InitVideo(video_file_path.toStdString());
//        play();
//    }
//    else /*if (dp == Image)*/
//    {
//        //
//    }

    QString file_name = QFileDialog::getOpenFileName(this,"open file",".","*.*");
     if( false == file_name.isEmpty() )
         file_path = file_name;
    ui->label_path->setText(file_path);


}
