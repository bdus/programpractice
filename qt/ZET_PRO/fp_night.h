#ifndef FP_NIGHT_H
#define FP_NIGHT_H

#ifdef linux
#include <unistd.h>
#include <dirent.h>
#endif
#include "algorithminstance.h"
#include <opencv2/opencv.hpp>
#include <io.h>
#include "HazeRemover.h"

class FP_night : public AlgorithmInstance
{
public:
    FP_night();
    ~FP_night();
    void frameProcess(cv::Mat & src, cv::Mat & dest);

private:
    HazeRemover hr;
};

#endif // FP_NIGHT_H
