#ifndef CAMERA_H
#define CAMERA_H

#include <pylon/PylonIncludes.h>
#include "SampleImageCreator.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <iostream>

using namespace Pylon;
using namespace GenApi;
using namespace cv;
using namespace std;

struct CameraParameter {
    double ExposureTimeAbs = 0.01;
    double GainRaw = .0;
    uint32_t Width = 640;
    uint32_t Height = 480;
};

class Camera {

public:
    Camera() = default;
    Camera(const CameraParameter &para) : parameter(para) { }
    CameraParameter parameter; // camera parametr
    int CaptueCVImageRandom(Mat &CvImage) const; // capture image by random generated, return opencv mat form(depth=8)
    int CaptueCVImageBasler(Mat &CvImage) const; // capture image from basler, return opencv mat form(depth=8)

int CaptueCVImageRandom(Mat &CvImage);
int CaptueCVImageBasler(Mat &CvImage);

};


#endif // CAMERA_H
