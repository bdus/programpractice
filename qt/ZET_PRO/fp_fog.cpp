#include "fp_fog.h"

FP_fog::FP_fog()
{

}

FP_fog::~FP_fog()
{
    delete &hr;
}

void FP_fog::frameProcess(Mat &src, Mat &dest)
{
    hr.enhancement(src);
    dest = hr.mDehazeImg;
}
