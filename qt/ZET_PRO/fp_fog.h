#ifndef FP_FOG_H
#define FP_FOG_H
#ifdef linux
#include <unistd.h>
#include <dirent.h>
#endif
#include "algorithminstance.h"
#include <opencv2/opencv.hpp>
#include <io.h>
#include "HazeRemover.h"

using namespace cv;
class FP_fog : public AlgorithmInstance
{
public:
    FP_fog();
    ~FP_fog();

    void frameProcess(cv::Mat & src, cv::Mat & dest);

private:
    HazeRemover hr;
};

#endif // FP_FOG_H
