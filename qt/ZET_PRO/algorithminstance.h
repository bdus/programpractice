#ifndef ALGORITHMINSTANCE_H
#define ALGORITHMINSTANCE_H

//#include <QObject>
#include <opencv2/opencv.hpp>


using namespace std;
class AlgorithmInstance
{
public:
    AlgorithmInstance() = default;
    virtual ~AlgorithmInstance() = default;
    virtual void frameProcess(cv::Mat & src, cv::Mat & dest) = 0;

    //算法处理fps ssim psnr

};

#endif // ALGORITHMINSTANCE_H
