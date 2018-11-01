#ifndef ALGORITHMINSTANCE_H
#define ALGORITHMINSTANCE_H
//#include <QObject>
#include <opencv2/opencv.hpp>
typedef void (*frameProcessor)(cv::Mat & src, cv::Mat & dest);
using namespace std;
class AlgorithmInstance //场景匹配除外的5个算法
{
public:
    AlgorithmInstance() = default;
    virtual ~AlgorithmInstance() = default;
    virtual void frameProcess(cv::Mat & src, cv::Mat & dest) = 0;

    //算法处理fps ssim psnr 自行实现
};
typedef enum{
    //def = 0,
    FPt_gray = 0,
    FPt_rain,
    FPt_fog,
    FPt_night,
    FPt_lumen,
    FPt_noise,
    FPt_match
} FP_type;
//class ScenceMatch
//{
//public:
//    ScenceMatch() = default;
//    virtual ~ScenceMatch() = default;
//    virtual vector<FP_type> process(cv::Mat & ,cv::Mat & ,cv::Mat & ) = 0;
//};

#endif // ALGORITHMINSTANCE_H
