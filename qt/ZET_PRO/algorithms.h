#ifndef ALGORITHMS_H
#define ALGORITHMS_H
typedef void (*frameProcessor)(cv::Mat & src, cv::Mat & dest);
typedef enum{
    def = 0,
    FP_rain,
    FP_fog,
    FP_night,
    FP_lumen,
    FP_noise,
    FP_match,
    FP_gray
} FP_type;

#include "algorithminstance.h"
#include "rgb2gray.h"
#endif // ALGORITHMS_H
