#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <iostream>
#include <string>

int main()
{
	// Video input
	cv::VideoCapture cap(0);
	if(!cap.isOpened())
	{	
		std::cout << "Invlaid Video Source\n";
	}
	
	// Variables for video capture/ display and FAST algorithm
	cv::Mat frame;
	std::vector<cv::KeyPoint> corners;
	int thresh = 35;
	bool non_max_suppression = true;
	auto type = cv::FastFeatureDetector::TYPE_9_16;
	// Create FAST Feature Detector
	auto fast_detector = cv::FastFeatureDetector::create(thresh, non_max_suppression, type);
	std::string win0 = "FAST Corner Detector";
	cv::namedWindow(win0, cv::WindowFlags::WINDOW_AUTOSIZE);
	while(1)
	{
		cap >> frame;
		// Perform detection of corner or keypoints
		fast_detector -> detect(frame, corners);
		// Draw the keypoints onto the frame and display
		cv::drawKeypoints(frame, corners, frame, cv::Scalar(0, 0, 255));
		cv::imshow(win0, frame);
		// End the video and code when 'ESC' is pressed
		if(cv::waitKey(10) == 27)
		{
			break;
		}
	}
	return 0;
}

