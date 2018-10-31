#ifndef RGB2GRAY_H
#define RGB2GRAY_H

#include "algorithminstance.h"
#include <opencv2/opencv.hpp>

using namespace cv;

class rgb2gray : public AlgorithmInstance
{
public:
    rgb2gray();
    ~rgb2gray();

    void frameProcess(Mat & src, Mat & dest);

};

#endif // RGB2GRAY_H
