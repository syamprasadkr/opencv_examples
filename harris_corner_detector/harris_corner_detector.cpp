#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <string>

void harris_corner(int thresh, void* userdata)
{
	cv::Mat	src, src_gray, harris_res, harris_norm, harris_norm_scaled, harris_display;
	// Convert userdata to cv::Mat object
	src = *((cv::Mat*)userdata);
	
	// Set parameters for Harris Corner Detector
	int block_size = 2;
	int aperture_size = 3;
	double k = 0.04;

	// Perform corner detection using Harris Algorithm
	src.copyTo(harris_display);
	harris_res = cv::Mat(src.size(), CV_32FC1);
	cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);
	cv::cornerHarris(src_gray, harris_res, block_size, aperture_size, k); 
	cv::normalize(harris_res, harris_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
	cv::convertScaleAbs(harris_norm, harris_norm_scaled);

	// Mark corners with circles
	for(int i = 0; i < harris_norm.rows; i++)
	{
		for(int j = 0; j < harris_norm.cols; j++)
		{
			if((int) harris_norm.at<float>(i, j) > thresh)
			{	
				cv::circle(harris_display, cv::Point(j, i), 5, cv::Scalar(0, 0, 255), 2, 8, 0);
			}
		}
	}

	//Display results
	const std::string win1 = "Harris Corner Detector";
	cv::namedWindow(win1);
	cv::imshow(win1, harris_display);
}
int main(int argc, char** argv)
{	
	// Obtain the source image
	cv::Mat src;
	const std::string win0 = "Source Image";
	cv::namedWindow(win0);
	src = cv::imread(argv[1]);
	if(src.empty())
	{
		std::cout << "Invalid Input\n";
	}

	// Set threshold values and create trackbar to change threshold values
	int thresh = 120;
	int max_thresh = 255;
	cv::createTrackbar("Threshold", win0, &thresh, max_thresh, harris_corner, &src);
	
	// Initial call for Harris Corner Detector 		
	harris_corner(thresh, &src);
	
	// Display source image
	cv::imshow(win0, src);
	cv::waitKey(0);
	return 0;
}

