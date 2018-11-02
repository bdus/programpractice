#ifndef FP_LUMEN_H
#define FP_LUMEN_H

#include "algorithminstance.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
class FP_lumen : public AlgorithmInstance
{
public:
    FP_lumen();
    ~FP_lumen();

    void frameProcess(cv::Mat & input, cv::Mat & dest);
private:

    Mat  Y, Cb, Cr;
    int r1, c1;
};

#endif // FP_LUMEN_H
