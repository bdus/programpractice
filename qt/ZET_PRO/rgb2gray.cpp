#include "rgb2gray.h"

rgb2gray::rgb2gray()
{
    //init
}

rgb2gray::~rgb2gray()
{

}

void rgb2gray::frameProcess(Mat &src, Mat &dest)
{
    //implemention
    cvtColor(src,dest,CV_RGB2GRAY);
}
