//#include <pylon/PylonIncludes.h>
//#include "SampleImageCreator.h"
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/video/video.hpp>
//#include <iostream>

//using namespace Pylon;
//using namespace GenApi;
//using namespace cv;
//using namespace std;

//struct CameraParameter {
//	double ExposureTimeAbs = 0.01;
//	double GainRaw = .0;
//	uint32_t Width = 640;
//	uint32_t Height = 480;
//};

//class Camera {

//public:
//	Camera() = default;
//	Camera(const CameraParameter &para) : parameter(para) { }
//	CameraParameter parameter; // camera parametr
//	int CaptueCVImageRandom(Mat &CvImage) const; // capture image by random generated, return opencv mat form(depth=8)
//	int CaptueCVImageBasler(Mat &CvImage) const; // capture image from basler, return opencv mat form(depth=8)


//};

#include "camera.h"

int Camera::CaptueCVImageRandom(Mat &CvImage) const {
	PylonInitialize(); // initilize runtime for use pylon method
	CPylonImage imageBGR8packed = SampleImageCreator::CreateMandelbrotFractal(PixelType_BGR8packed, parameter.Width, parameter.Height);

	Mat openCvImage;
	openCvImage = cv::Mat(parameter.Height, parameter.Width, CV_8UC3, (uint8_t *)imageBGR8packed.GetBuffer());
	openCvImage.copyTo(CvImage);

	return 0;
}

int Camera::CaptueCVImageBasler(Mat &CvImage) const {

	PylonAutoInitTerm autoInitTerm;  //auto initilize pylon lib
	try {
		
		CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice()); //  instant a camera object
		
		INodeMap& nodemap = camera.GetNodeMap(); // camera parameter node
		camera.Open(); // open  camera
		CIntegerPtr width = nodemap.GetNode("Width"); // get camera width and height 
		CIntegerPtr height = nodemap.GetNode("Height");
		camera.MaxNumBuffer = 5; // set camera buffer, default is 10
		CImageFormatConverter formatConverter;
		formatConverter.OutputPixelFormat = PixelType_BGR12packed; 
		CPylonImage pylonImage;
		Mat openCvImage;
		const uint32_t c_countOfImagesToGrab = 10; //image nums of need to grab

		camera.StartGrabbing(c_countOfImagesToGrab, GrabStrategy_LatestImageOnly); 
		CGrabResultPtr ptrGrabResult;


		while (camera.IsGrabbing())
		{
			
			camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);// wait for 5000 ms.

			// if grab succeed
			if (ptrGrabResult->GrabSucceeded()){
				formatConverter.Convert(pylonImage, ptrGrabResult); //convert buffer data to pylon image.
				// convert pylon image to OpenCV image.
				openCvImage = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *)pylonImage.GetBuffer());
				openCvImage.copyTo(CvImage);
			}
		}

	}

	catch (GenICam::GenericException &e) {
		// Error handling.
		cerr << "An exception occurred." << endl
			<< e.GetDescription() << endl;
	}
	return 0;
}

//int main() {
//	CameraParameter para;
//	Camera camera(para);
//	string path = "test_opencv.tiff";
//	for (int i = 0; i < 5; i++) {
//		camera.parameter.Width += 100;
//		Mat CvImage;
//		camera.CaptueCVImageRandom(CvImage);
//		ostringstream os;
//		os << "test_opencv" << i << ".tiff";
//		imwrite(os.str(), CvImage);

//	}

//	return 0;
//}
