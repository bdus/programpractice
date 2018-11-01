#ifndef FP_NOISE_H
#define FP_NOISE_H
#include "algorithminstance.h"
#include <opencv2/opencv.hpp>
#include "guidedFilter.hpp"
#include <ctime>

class FP_noise : public AlgorithmInstance
{
public:
    FP_noise();
    ~FP_noise();

    void frameProcess(cv::Mat & src, cv::Mat & dest);

private:

    int para_r;
    double para_eps;
    size_t para_s;

};

#endif // FP_NOISE_H
