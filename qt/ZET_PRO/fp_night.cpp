#include "fp_night.h"

FP_night::FP_night()
{

}

FP_night::~FP_night()
{
    delete &hr;
}

void FP_night::frameProcess(cv::Mat &src, cv::Mat &dest)
{
    hr.process(src);
    dest = hr.mDehazeImg;
}
