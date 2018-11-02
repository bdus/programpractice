#ifndef FP_RAIN_H
#define FP_RAIN_H

#include "algorithminstance.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

class FP_rain : public AlgorithmInstance
{
public:
    FP_rain();
    ~FP_rain();

    void frameProcess(cv::Mat & input, cv::Mat & dest);

};

#endif // FP_RAIN_H
