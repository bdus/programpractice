#include "fp_noise.h"

FP_noise::FP_noise()
{
    para_r = 8;
    para_eps = 0.1 * 0.1;
    para_s = 4;
}

FP_noise::~FP_noise()
{

}

void FP_noise::frameProcess(cv::Mat &src, cv::Mat &dest)
{
    fgf::blur(src, dest, para_r, para_eps, para_s);
}
