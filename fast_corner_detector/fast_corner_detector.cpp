#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <iostream>
#include <string>

int main()
{
	cv::VideoCapture cap(0);
	if(!cap.isOpened())
	{	
		std::cout << "Invlaid Video Source\n";
	}
	cv::Mat frame;
	std::vector<cv::KeyPoint> corners;
	int thresh = 10;
	bool non_max_suppression = true;
	int type = cv::FastFeatureDetector::TYPE_9_16;
	auto fast_detector = cv::FastFeatureDetector::create(thresh, non_max_suppression, type);
	std::string win0 = "FAST Corner Detector";
	cv::namedWindow(win0, cv::WindowFlags::WINDOW_AUTOSIZE);
	while(1)
	{
		cap >> frame;
		fast_detector -> detect(frame, corners);
		cv::drawKeypoints(frame, corners, frame, cv::Scalar(0, 0, 255));
		cv::imshow(win0, frame);
		if(cv::waitKey(10) == 27)
		{
			break;
		}
	}
	return 0;
}

