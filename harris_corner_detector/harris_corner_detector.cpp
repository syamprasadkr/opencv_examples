#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <string>

int main(int argc, char** argv)
{	
	cv::Mat src, src_gray, harris_res, harris_norm, harris_norm_scaled, harris_display;
	const std::string win0 = "Source Image";
	const std::string win1 = "Harris Corner Detector";
	int thresh = 120;
	int block_size = 2;
	int aperture_size = 3;
	double k = 0.04;
	src = cv::imread(argv[1]);
	src.copyTo(harris_display);
	harris_res = cv::Mat(src.size(), CV_32FC1);
	cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);
	cv::cornerHarris(src_gray, harris_res, block_size, aperture_size, k); 
	cv::normalize(harris_res, harris_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
	cv::convertScaleAbs(harris_norm, harris_norm_scaled);

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
	cv::imshow(win0, src);
	cv::imshow(win1, harris_display);
	cv::waitKey(0);
	return 0;
}

