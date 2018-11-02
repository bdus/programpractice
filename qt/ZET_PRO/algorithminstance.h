#ifndef ALGORITHMINSTANCE_H
#define ALGORITHMINSTANCE_H
//#include <QObject>
#include <opencv2/opencv.hpp>
typedef void (*frameProcessor)(cv::Mat & src, cv::Mat & dest);
using namespace std;
class AlgorithmInstance //场景匹配除外的4个算法
{
public:
    AlgorithmInstance() = default;
    virtual ~AlgorithmInstance() = default;
    virtual void frameProcess(cv::Mat & src, cv::Mat & dest) = 0;

    //算法处理fps ssim psnr 自行实现
    //virtual double _fps_(String video_filepath);
    //virtual double _your_metrics_(String video_filepath);
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

class ScenceMatch
{
public:
    ScenceMatch() = default;
    virtual ~ScenceMatch() = default;
    virtual vector<FP_type> process(cv::Mat & f1, cv::Mat &f2, cv::Mat & f3) = 0;
};

#endif // ALGORITHMINSTANCE_H
