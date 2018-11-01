#ifndef ALGORITHMS_H
#define ALGORITHMS_H
typedef enum{
    //def = 0,
    FPt_gray,
    FPt_rain,
    FPt_fog,
    FPt_night,
    FPt_lumen,
    FPt_noise,
    FPt_match
} FP_type;
typedef enum{
    //deff = 0,
    Video,
    Image
} Data_type;

#include "algorithminstance.h"
#include "rgb2gray.h"
#include "fp_noise.h"

#endif // ALGORITHMS_H
